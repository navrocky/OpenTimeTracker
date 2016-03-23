#include "QDjangoScopedTransaction.h"

int QDjangoScopedTransaction::m_spinlock = 0;

QDjangoScopedTransaction::QDjangoScopedTransaction()
    : m_committed(false)
{
    if (m_spinlock == 0)
        QDjango::beginTransaction();
    m_spinlock++;
}

QDjangoScopedTransaction::~QDjangoScopedTransaction()
{
    m_spinlock--;
    if (m_spinlock == 0)
    {
        if (!m_committed)
            QDjango::rollbackTransaction();
    }
}

void QDjangoScopedTransaction::commit()
{
    m_committed = true;
    if (m_spinlock == 1)
        QDjango::commitTransaction();
}
