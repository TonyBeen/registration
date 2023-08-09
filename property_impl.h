/*************************************************************************
    > File Name: property_impl.h
    > Author: hsz
    > Brief:
    > Created Time: Tue 08 Aug 2023 06:53:00 PM CST
 ************************************************************************/

#ifndef __PROPERTY_IMPL_H__
#define __PROPERTY_IMPL_H__

#include <memory>

namespace detail {

template<typename T>
struct property_accessor
{
    static bool set_value(T& prop, const T& arg)
    {
        prop = arg;
        return true;
    }
};

class property_wrapper_base
{
public:
    virtual bool setValue(any &entity, const any &arg) const
    {
        return false;
    }

    virtual any getValue(any &entity) const
    {
        return any();
    }
};

template<typename T>
class property_wrapper;

template<typename C, typename M>
class property_wrapper<M (C::*)> : public property_wrapper_base
{
public:
    using accessor = M (C::*);

    property_wrapper(const std::string &name, accessor acc) :
        m_acc(acc)
    {
        static_assert(!std::is_pointer<M>::value, "The data type of the property is already a pointer type! The given policy cannot be used for this property.");
    }

    ~property_wrapper() { }

    bool setValue(any &entity, const any &arg) const
    {
        C *ptr = any_cast<C>(&entity);
        const M *memberPtr = any_cast<M>(&arg);
        if (ptr && memberPtr)
        {
            return property_accessor<M>::set_value((ptr->*m_acc), *memberPtr);
        }

        return false;
    }

    any getValue(any &entity) const
    {
        C *ptr = any_cast<C>(&entity);
        if (nullptr != ptr)
        {
            return any((ptr->*m_acc));
        }

        return any();
    }

private:
    accessor m_acc;
};

}

#endif