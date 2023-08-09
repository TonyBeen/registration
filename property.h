/*************************************************************************
    > File Name: property.h
    > Author: hsz
    > Brief:
    > Created Time: Sat 05 Aug 2023 01:07:40 PM CST
 ************************************************************************/

#ifndef __PROPERTY_H__
#define __PROPERTY_H__

#include <string>
#include <memory>
#include <iostream>
#include "any.h"
#include "property_impl.h"

class property
{
public:
    property() {}

    ~property() {}

    property(const property &other) :
        m_name(other.m_name),
        m_property_wrapper(other.m_property_wrapper)
    {
    }

    template<typename ACC>
    bool bind(const std::string &name, ACC acc)
    {
        static_assert(std::is_member_object_pointer<ACC>::value, "No valid property accessor provided!");
        m_name = name;
        m_property_wrapper = std::make_shared<detail::property_wrapper<ACC>>(name, acc);
        return true;
    }

    property &operator=(const property &other)
    {
        if (std::addressof(other) != this)
        {
            m_name = other.m_name;
            m_property_wrapper = other.m_property_wrapper;
        }
    }

    template<typename T>
    bool setValue(any &instance, const T &value) const
    {
        if (nullptr == m_property_wrapper)
        {
            return false;
        }

        return m_property_wrapper->setValue(instance, any(value));
    }

    any getValue(any &instance) const
    {
        if (nullptr == m_property_wrapper)
        {
            return any();
        }

        return m_property_wrapper->getValue(instance);
    }

private:
    std::string m_name;
    std::shared_ptr<detail::property_wrapper_base> m_property_wrapper;
};

#endif
