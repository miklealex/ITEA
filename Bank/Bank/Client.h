#ifndef _CLIENT_H_
#define _CLIENT_H_

#include <string>
#include <time.h>

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

const std::string alphabet{ "0123456789abcdefghijklmnopqrstuvwxyz" };

std::string generateID()
{
    static bool firstCall = true;
    if (firstCall)
    {
        srand(time(NULL));
        firstCall = false;
    }
    
    std::string result{ "" };
    for(uint8_t i = 0U; i < 10; ++i)
    {
        auto index = rand() % (alphabet.size() - 1);
        result += alphabet[index];
    }

    return result;
}

#endif
