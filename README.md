# registration
    仿照rttr实现的一种简单的运行时反射示例
    目前只支持成员变量注册, 成员函数, 普通函数, 普通全局变量均不支持.
    由于any的功能相比variant比较简单, 所以此项目只用做示例以便于学习c++是如何做到反射的.

`g++ main.cpp type.cpp -o main -g`