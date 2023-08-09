/*************************************************************************
    > File Name: type.h
    > Author: hsz
    > Brief:
    > Created Time: Sat 05 Aug 2023 11:43:57 AM CST
 ************************************************************************/

#ifndef __TYPE_H__
#define __TYPE_H__

#include <unordered_map>
#include <memory>

class registration;

class type
{
public:
    type() {}
    ~type() {}

    static type *GetInstance();

    bool addRegistration(const std::string &name, const registration &reg);
    bool delRegistration(const std::string &name);
    std::shared_ptr<registration> getRegistration(const std::string &name);

private:
    std::unordered_map<std::string, std::shared_ptr<registration>> m_typeMap;
};

#endif