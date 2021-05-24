#ifndef _HISTORY_MANAGER_H_
#define _HISTORY_MANAGER_H_

#include "Transaction.h"
#include <list>

class HistoryManager
{
public:
    static bool saveTransaction(std::string clientId, Transaction transaction)
    {
        //TODO: save transaction to the correspondent file
        return true;
    }

    static std::list<Transaction> loadHistoryForClient(std::string clientId)
    {
        //TODO: load transactions history from the corresponding file
        return std::list<Transaction>{};
    }
};

#endif