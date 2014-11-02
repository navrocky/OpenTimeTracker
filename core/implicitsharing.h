#pragma once

#include <memory>

template <class Body>
class ImplicitSharing
{
public:
    ImplicitSharing()
    : body_(std::make_shared<Body>())
    {
    }

    /*! Call this from all non const methods. */
    void detach()
    {
        if (body_.unique())
            return;
        body_ = std::make_shared<Body>(*(body_.get()));
    }

    /*! Access to shared body. */
    inline Body* operator->() const
    {
        return body_.get();
    }

    inline Body* operator->()
    {
        detach();
        return body_.get();
    }

private:
    std::shared_ptr<Body> body_;
};
