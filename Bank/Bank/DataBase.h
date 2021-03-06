#define _CRT_SECURE_NO_WARNINGS
#include <iomanip>
#ifndef _DATABASE_H_
#define _DATABASE_H_

#include "HistoryManager.h"
#include "Client.h"
#include <string>
#include <fstream>
#include <map>
#include <iostream>
#include <chrono>
#include <sstream>

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
        const auto existingClient = clients.find(clientId);
        if (existingClient == clients.end())
        {
            std::cout << "There is no client with such id. Please, try again.\n";
            return false;
        }

        existingClient->second.balance += amount;
        auto now = std::chrono::system_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(now);

        std::stringstream ss;
        ss << std::put_time(std::localtime(&in_time_t), "%Y%m%d:%X");
        HistoryManager::saveTransaction(clientId, Transaction{ TransactionType::REFILL, ss.str(), amount });
        // Create Transaction if possible and call HistoryManager::saveTransaction(clientId);
        return true;
    }

    void listAllClients()
    {
        if(clients.empty())
        {
            std::cout << "There are no clients records yet. Please, add one.\n";
            return;
        }

        for(auto& item : clients)
        {
            outputClientInfo(item.first);
        }
    }

    bool removeCostsFromClient(std::string clientId, uint64_t amount)
    {
        const auto existingClient = clients.find(clientId);
        if (existingClient == clients.end())
        {
            std::cout << "There is no client with such id. Please, try again.\n";
            return false;
        }

        if(existingClient->second.balance < amount)
        {
            std::cout << "Not enough funds.\n";
            return false;
        }

        existingClient->second.balance -= amount;
        auto now = std::chrono::system_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(now);

        std::stringstream ss;
        ss << std::put_time(std::localtime(&in_time_t), "%Y%m%d:%X");
        HistoryManager::saveTransaction(clientId, Transaction{ TransactionType::EXPENSE, ss.str(), amount });
        return true;
    }

    void outputTheRichestClients()
    {
        //TODO: look for the richest client. If there are several clients with biggest amount of money - output all of them.
    }

    bool outputClientInfo(std::string clientId)
    {
        const auto existingClient = clients.find(clientId);
        if (existingClient == clients.end())
        {
            std::cout << "There is no client with such id. Please, try again.\n";
            return false;
        }

        auto& client = existingClient->second;
        std::cout << "Id:" << client.id << "\n"
            << client.name << "\n"
            << client.surname << "\n"
            << client.sex << "\n"
            << "Age: " << client.age << "\n"
            << "Balance: " << client.balance << "\n";
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
        if (clients.empty() == 0)
        {
            float totalRefill = 0;
            float totalExpence = 0;
            int countRefill = 0;
            int countExpence = 0;
            for (const auto& client : clients)
            {
                auto history = HistoryManager::loadHistoryForClient(client.second.id);
                for (const auto& it : history)
                {
                        if (it.type == TransactionType::REFILL)
                        {
                            countRefill++;
                            totalRefill += it.amount;
                        }
                        else
                        {
                            countExpence++;
                            totalExpence += it.amount;
                        }
                }
            }
            if (countRefill != 0)
                std::cout << "Average refill transaction per day is: " << totalRefill / countRefill << std::endl;
            else
                std::cout << "There is no refill transactions!" << std::endl;
            if (countExpence != 0)
                std::cout << "Average expence transaction per day is: " << totalExpence / countExpence << std::endl;
            else
                std::cout << "There is no expence transactions!" << std::endl;
        }
        else 
            std::cout << "Database is empty" << std::endl;
    }

    void transactionWithTheBiggestAmountOfMoney()
    {
        //TODO: look for transaction with the biggest amount of money (output all of them if several)
        if (clients.empty() == 0)
        {
            std::list<Transaction> biggest;
            float maxAmount = 0;
            for (const auto& client : clients)
            {
                auto history = HistoryManager::loadHistoryForClient(client.second.id);
                for (const auto& it : history)
                {
                    if (maxAmount < it.amount)
                    {
                        maxAmount = it.amount;
                        biggest.clear();
                    }
                    if (maxAmount == it.amount)
                    {
                        biggest.push_back(it);
                    }
                }
            }
            if (maxAmount != 0)
            {
                std::cout << "Transactions with the biggest amount of money: " << std::endl;
                for (const auto& it : biggest)
                {
                    std::cout << it.date << " " << it.type << " " << it.amount << std::endl;
                }
            }
            else
                std::cout << "There is no transactions in database!" << std::endl;
        } else
            std::cout << "Database is empty" << std::endl;
    }

    bool outputTransactionHistoryForClient(std::string clientId)//Tymoshenko Viktor
    {
        auto history = HistoryManager::loadHistoryForClient(clientId);

        if (history.empty())//checking the history of transactions for fullness
        {
            std::cout << "Sorry for the transactions history is empty " << std::endl;
            return false;
        }
       
        for (const auto &it : history)
        {
            if (it.type == TransactionType::REFILL)
            {
                std::cout << "Type of operation: Refill" << std::endl;
            }
            else
            {
                std::cout << "Type of operation: Expense" << std::endl;
            }
            std::cout << "Date of operation: " << it.date << std::endl;
            std::cout << "Amount: " << it.amount << std::endl;
        }
        return true;
        
    }

    bool outputTransactionsForSpecifiedDateForClient(std::string clientId, std::string date)//Tymoshenko Viktor
    {   
        bool checkSpecDataOutput = false;
        auto history = HistoryManager::loadHistoryForClient(clientId);

        if (history.empty())//checking the history of transactions for fullness
        {
            std::cout << "Sorry for the transactions history is empty " << std::endl;
            return false;
        }

        for (const auto &it : history)
        {
            
            if (!it.date.compare(0,8,date))//checking the first eight characters from the date string
            {
                if (it.type == TransactionType::REFILL)
                {
                    std::cout << "Type of operation: Refill" << std::endl;
                }
                else
                {
                    std::cout << "Type of operation: Expense" << std::endl;
                }
                std::cout << "Date of operation: " << it.date << std::endl;
                std::cout << "Amount: " << it.amount << std::endl;
                checkSpecDataOutput = true;
            }         
        }
        if (checkSpecDataOutput)
        {
            return true;
        }
        else
        {
            std::cout << "Sorry for the specified date no transactions" << std::endl;
            return false;
        }
       
       
    }

    void addNewClient()
    {
        auto newId = generateID();
        std::string name;
        std::string surname;
        std::string sex;
        uint16_t     age;
        std::cout << "Please, enter client's name\n";
        std::cin >> name;
        std::cout << "Please, enter client's surname\n";
        std::cin >> surname;
        std::cout << "Please, enter client's sex (male/female):\n";
        std::cin >> sex;
        if(sex != "male" && sex != "female")
        {
            sex = "male";
        }
        std::cout << "Please, enter client's age\n";
        std::cin >> age;

        clients.emplace(newId, Client{ newId, name, surname, sex, 0, age });
    }

    bool removeClient(std::string clientId)
    {
        const auto existingClient = clients.find(clientId);
        if(existingClient == clients.end())
        {
            std::cout << "There is no client with such id. Please, try again.\n";
            return false;
        }

        clients.erase(clientId);
        return true;
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
        std::ifstream loadData;
        loadData.open("Customer_data.txt", std::ios_base::in);

        std::string tempStringVar;      //for storing strings
        std::string checkID = "[id]";
        std::string tempIntegerVar;     //for storing a string with an integer value
        uint64_t temp_balance_age;      //for storing balance and age values

        if (loadData.is_open()) {
            while (getline(loadData, tempStringVar)) {                  //iterate over all lines in the file
                std::size_t client_ID = tempStringVar.find(checkID);    //search for a string with an ID
                if (client_ID != std::string::npos) {                   //if found

                    std::string ID_key = tempStringVar.substr(12);      //saving the ID in variable and map
                    clients[ID_key].id = ID_key;
                    getline(loadData, tempStringVar);                   //line skip (for personal comfort)

                    getline(loadData, tempStringVar);                   //reading and saving the client's name
                    clients[ID_key].name = tempStringVar.substr(12);

                    getline(loadData, tempStringVar);                   //reading and saving the client's surname
                    clients[ID_key].surname = tempStringVar.substr(12);

                    getline(loadData, tempStringVar);                   //reading and saving the client's sex
                    clients[ID_key].sex = tempStringVar.substr(12);

                    getline(loadData, tempStringVar);                   //reading and saving the client's balance
                    tempIntegerVar = tempStringVar.substr(12);
                    temp_balance_age = stoll(tempIntegerVar);
                    clients[ID_key].balance = temp_balance_age;

                    getline(loadData, tempStringVar);                   //reading and saving the client's age
                    tempIntegerVar = tempStringVar.substr(12);
                    temp_balance_age = stoi(tempIntegerVar);
                    clients[ID_key].age = temp_balance_age;

                    getline(loadData, tempStringVar);                   //line skip ('-' x75)
                }
            }
        }
        loadData.close();
    }

    void updateDataBase()
    {
        //TODO: save info about clients to file here
        std::ofstream updateData;
        updateData.open("Customer_data.txt", std::ios_base::out);

        if (updateData.is_open()) {
            for (const auto& pair : clients) {  //iterate over of all keys and their values
                updateData << "[id]        " << pair.first << std::endl << std::endl;
                updateData << "[name]      " << pair.second.name << std::endl;
                updateData << "[surname]   " << pair.second.surname << std::endl;
                updateData << "[sex]       " << pair.second.sex << std::endl;
                updateData << "[balance]   " << pair.second.balance << std::endl;
                updateData << "[age]       " << pair.second.age << std::endl;
                updateData << "---------------------------------------------------------------------------" << std::endl;
            }
        }
        updateData.close();
    }

private:
    std::map<std::string, Client> clients;
};

#endif
