#ifndef QDJANGOSCOPEDTRANSACTION_H
#define QDJANGOSCOPEDTRANSACTION_H

#include "QDjango.h"

class QDJANGO_EXPORT QDjangoScopedTransaction
{
public:
    QDjangoScopedTransaction();
    ~QDjangoScopedTransaction();

    void commit();

private:
    bool m_committed;
    static int m_spinlock;
};

#endif
