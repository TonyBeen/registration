/*************************************************************************
    > File Name: type.cpp
    > Author: hsz
    > Brief:
    > Created Time: Sat 05 Aug 2023 11:44:03 AM CST
 ************************************************************************/

#include "type.h"
#include "registration.h"
#include <mutex>

template <typename Type>
struct FreeType
{
    FreeType() :
        m_type(nullptr)
    {
    }

    ~FreeType()
    {
        if (m_type != nullptr)
        {
            delete m_type;
        }
    }

    std::mutex m_mutex;
    Type *m_type;
};


type *type::GetInstance()
{
    static FreeType<type> freeType;
    std::lock_guard<std::mutex> lock(freeType.m_mutex);
    if (freeType.m_type == nullptr)
    {
        freeType.m_type = new type;
    }

    return freeType.m_type;
}

bool type::addRegistration(const std::string &name, const registration &reg)
{
    std::shared_ptr<registration> regPtr = std::make_shared<registration>(reg);
    auto it = m_typeMap.insert(std::make_pair(name, regPtr));
    return it.second;
}

bool type::delRegistration(const std::string &name)
{
    auto it = m_typeMap.find(name);
    if (it != m_typeMap.end())
    {
        m_typeMap.erase(it);
    }

    return true;
}

std::shared_ptr<registration> type::getRegistration(const std::string &name)
{
    auto it = m_typeMap.find(name);
    if (it != m_typeMap.end())
    {
        return it->second;
    }

    return nullptr;
}
