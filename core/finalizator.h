#pragma once

#include <functional>

/*
 * Short example
 *
 *{
 *  int fd = ::open("aaa.txt");
 *  Finalizator fdFinalize([&](){
 *    ::close(fd);
 *  });
 *
 *  throw std::runtime_exception("something goes wrong");
 *}
 *
 *  or with macro:
 *
 *  int fd = ::open("aaa.txt");
 *  FINALLY { ::close(fd); };
 *
 *  NAMED_FINALLY(closeFinalizator) { ... };
 *
 *  if (success)
 *      closeFinalizator.cancel();
 *
 */

class Finalizator
{
public:
    Finalizator() : canceled_(false) {}
    Finalizator(std::function<void()> func) : func_(func), canceled_(false) {}
    ~Finalizator();

    void setFunc(std::function<void()> func) { func_ = func; }
    void cancel() const { canceled_ = true; }

    Finalizator(const Finalizator&); // disable finalization in source copy
    void operator=(const Finalizator&); // disable finalization in source copy

private:

    std::function<void()> func_;
    mutable bool canceled_;
};

inline Finalizator& operator << (Finalizator& f, std::function<void()> func)
{
    f.setFunc(func);
    return f;
}

#define __CAT2(X,Y) X##Y
#define __CAT(X,Y) __CAT2(X,Y)

#define FINALLY \
    Finalizator __CAT(finalizator,__LINE__); \
    __CAT(finalizator,__LINE__) << [&]()

#define NAMED_FINALLY(name) \
    Finalizator name; \
    name << [&]()
