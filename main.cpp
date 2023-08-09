/*************************************************************************
    > File Name: main.cpp
    > Author: hsz
    > Brief:
    > Created Time: Wed 09 Aug 2023 08:55:37 AM CST
 ************************************************************************/

#include <iostream>
#include "type.h"
#include "registration.h"

#define CLASS_NAME          "MyStruct"
#define CLASS_MEMBER_ID     "ID"
#define CLASS_MEMBER_NAME   "Name"

struct MyStruct
{
    int32_t id = 0;
    std::string name;
};

int main(int argc, char **argv)
{
    registration temp(CLASS_NAME);
    temp.bindProperty(CLASS_MEMBER_ID, &MyStruct::id)
        .bindProperty(CLASS_MEMBER_NAME, &MyStruct::name);

    type::GetInstance()->addRegistration(CLASS_NAME, temp);

    MyStruct object;
    any anyInstance(object);

    std::shared_ptr<registration> regPtr = type::GetInstance()->getRegistration(CLASS_NAME);
    regPtr->setValue(anyInstance, CLASS_MEMBER_ID, 10);
    object.id = any_cast<int32_t>(regPtr->getValue(anyInstance, CLASS_MEMBER_ID));

    // any暂时不支持指针类型
    regPtr->setValue(anyInstance, CLASS_MEMBER_NAME, std::string("Hello,World"));
    object.name = any_cast<std::string>(regPtr->getValue(anyInstance, CLASS_MEMBER_NAME));

    std::cout << "'" << object.id << ", " << object.name << "'" << std::endl;
    return 0;
}