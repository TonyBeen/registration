/*************************************************************************
    > File Name: registration.h
    > Author: hsz
    > Brief:
    > Created Time: Sat 05 Aug 2023 11:43:45 AM CST
 ************************************************************************/

#ifndef __REGISTER_H__
#define __REGISTER_H__

#include <string>
#include <unordered_map>
#include <type_traits>
#include "type.h"
#include "property.h"

template<typename T>
struct GetType{};

template<typename C, typename M>
struct GetType<M C::*>
{
    using ClassType = C;
    using MemberType = M;
};

class registration
{
public:
    registration(const std::string &strClassName) :
        m_className(strClassName)
    {
    }

    registration(const registration &other) :
        m_className(other.m_className),
        m_propertyMap(other.m_propertyMap)
    {
    }

    // 注册类的成员变量
    template<typename MemberType>
    registration &bindProperty(const std::string &name, MemberType member)
    {
        property prop;
        prop.bind(name, member);
        m_propertyMap.insert(std::make_pair(name, prop));

        return *this;
    }

    template<typename T>
    bool setValue(any &instacne, const std::string &name, const T &value)
    {
        auto regPtr = type::GetInstance()->getRegistration(m_className);
        if (regPtr == nullptr)
        {
            return false;
        }

        auto it = regPtr->m_propertyMap.find(name);
        if (it == regPtr->m_propertyMap.end())
        {
            return false;
        }

        return it->second.setValue(instacne, value);
    }

    any getValue(any &instacne, const std::string &name)
    {
        auto regPtr = type::GetInstance()->getRegistration(m_className);
        if (regPtr == nullptr)
        {
            return any();
        }

        auto it = regPtr->m_propertyMap.find(name);
        if (it == regPtr->m_propertyMap.end())
        {
            return any();
        }

        return it->second.getValue(instacne);
    }

private:
    std::string m_className;
    std::unordered_map<std::string, property> m_propertyMap;
};

#endif