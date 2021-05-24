#ifndef _CLIENT_H_
#define _CLIENT_H_

#include <string>

class Client
{
public:
    std::string id;
    std::string name;
    std::string surname;
    std::string sex;
    uint64_t    balance;
    uint8_t     age;
};

#endif
