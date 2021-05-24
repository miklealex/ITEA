#ifndef _DATABASE_H_
#define _DATABASE_H_

#include "HistoryManager.h"
#include "Client.h"
#include <map>

class DataBase
{
public:
    DataBase()
    {
        loadDataBase();
    }

    ~DataBase()
    {
        updateDataBase();
    }

    bool addCostsForClient(std::string clientId, uint64_t amount)
    {
        //TODO: increase amount of money for specific client by specified amount (if exists)
        // Create Transaction if possible and call HistoryManager::saveTransaction(clientId);
        return true;
    }

    bool removeCostsFromClient(std::string clientId, uint64_t amount)
    {
        //TODO: decrease amount of money for specific client (if possible)
        return true;
    }

    void outputTheRichestClients()
    {
        //TODO: look for the richest client. If there are several clients with biggest amount of money - output all of them.
    }

    bool outputClientInfo(std::string clientId)
    {
        //TODO: look for specified client. If found - output all relevant info about it.
        return true;
    }

    void outputCLientsOlderThen(uint8_t age)
    {
        //TODO: output all clients which are older then specified age
    }

    void outputAllClientsWithSpecifiedSex(std::string sex)
    {
        //TODO: output all clients with specified sex
    }

    void averageTransactionsPerDay()
    {
        //TODO: output average transactions amount per day
    }

    void transactionWithTheBiggestAmountOfMoney()
    {
        //TODO: look for transaction with the biggest amount of money (output all of them if several)
    }

    bool outputTransactionHistoryForClient(std::string clientId)//Tymoshenko Viktor
    {
        auto history = HistoryManager::loadHistoryForClient(clientId);
        //TODO: output transaction for client if possible here
        return true;
    }

    bool outputTransactionsForSpecifiedDateForClient(std::string clientId, std::string date)//Tymoshenko Viktor
    {
        //TODO: output all transactions of client for specified date
        return true;
    }

    void outputTotalAmountOfMoneyInBank()
    {
        //TODO: output total amount of money in bank here
    }

    void outputTotalAmountOfClientsInBank()
    {
        //TODO: output total amount of clients in bank
    }

    void outputTheOldestTransaction()
    {
        //TODO: output the oldest transaction
    }

    void outputClientsWithTheBiggestAmountOfTransactionsPerDay()
    {
        //TODO: output clients with the biggest amount of transactions per day
    }

private:

    void loadDataBase()
    {
        //TODO: load info about clients from file here
    }

    void updateDataBase()
    {
        //TODO: save info about clients to file here
    }

private:
    std::map<std::string, Client> clients;
};

#endif
