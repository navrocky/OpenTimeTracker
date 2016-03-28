#pragma once

#include <cassert>
#include <cstddef>

template <typename T>
class Optional
{
public:
    Optional()
        : _valid(false)
    {}

    Optional(std::nullptr_t v)
        : _valid(false)
    {}

    Optional(const T& value)
        : _valid(true)
        , _value(value)
    {}

    operator bool() const
    {
        return _valid;
    }

    const T& operator*() const
    {
        assert(_valid);
        return _value;
    }

    T& operator*()
    {
        assert(_valid);
        return _value;
    }

    void operator=(const T& v)
    {
        _value = v;
        _valid = true;
    }

    void clear()
    {
        _valid = false;
    }

private:
    bool _valid;
    T _value;
};
