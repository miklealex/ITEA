#ifndef _TRANSACTION_H_
#define _TRANSACTION_H_

#include <cstdint>
#include <string>

enum TransactionType
{
    REFILL,
    EXPENSE
};

struct Transaction
{
    TransactionType type;
    std::string     date;
    uint64_t        amount;
};

#endif
