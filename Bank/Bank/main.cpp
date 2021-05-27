#include "DataBase.h"
#include <iostream>

void print_massage()
{
    std::cout << "Hello ...\nBank Db greeting you\nPlease, choose one option from below:\n";
    std::cout << "1 - Add client\n";
    std::cout << "2 - Remove client\n";
    std::cout << "3 - Increase amount of money for clien\n";
    std::cout << "4 - Decrease amount of money for specific client\n";
    std::cout << "5 - Look for the richest clients\n";
    std::cout << "6 - Get client info\n";
    std::cout << "7 - Output all clients which are older then specified age\n";
    std::cout << "8 - Output all clients with specified sex\n";
    std::cout << "9 - Get average transaction amount per day\n";
    std::cout << "10 - Look for transaction with the biggest amount of money\n";
    std::cout << "11 - Get transaction for client\n";
    std::cout << "12 - Get all transactions of client for specified date\n";
    std::cout << "13 - Get the oldest transaction\n";
    std::cout << "14 - Get clients with the biggest amount of transactions per day\n";
    std::cout << "q - for exit\n";
}
int main()
{
    DataBase db;
    bool is_worked = true;
    while (is_worked)
    {
        print_massage();
        char option;
        std::string clientid, sex, date;
        uint64_t amount;
        uint8_t age;
        std::cin >> option;
        

        switch (option)
        {
        case '1':
            db.addNewClient();
            break;
        case '2':
            std::cout << "Input client ID end press Enter..\n";
            std::cin >> clientid;

            if (!db.removeClient(clientid))
            {
                std::cout << "Client does not exist\n";
                break;
            }
            std::cout << "Client deleted\n";
            break;
        case '3':
            std::cout << "Input client ID and amount\n";
            std::cin >> clientid;
            std::cin >> amount;
            if (!db.addCostsForClient(clientid, amount))
            {
                std::cout << "Check data and try again\n";
                break;
            }
            std::cout << "Balance replenished\n";
            break;
        case '4':
            std::cout << "For decrease amount of money for specific client. Enter client id and amount\n";
            std::cin >> clientid;
            std::cin >> amount;
            if (!db.removeCostsFromClient(clientid, amount))
            {
                std::cout << "Check data and try again\n";
                break;
            }
            std::cout << "Decrease amount of money\n";
            break;
        case '5':
            db.outputTheRichestClients();
            break;
        case '6':
            std::cout << "Enter clientid\n";
            std::cin >> clientid;
            db.outputClientInfo(clientid);
            break;
        case 7:
            std::cout << "Enter age\n";
            std::cin >> age;
            db.outputCLientsOlderThen(age);
            break;
        case '8':
            std::cout << "Enter clients specific sex\nmale/female\n";
            std::cin >> sex;
            db.outputAllClientsWithSpecifiedSex(sex);
            break;
        case '9':
            db.averageTransactionsPerDay();
            break;
        case '10':
            db.transactionWithTheBiggestAmountOfMoney();
            break;
        case '11':
            std::cout << "Enter clientid\n";
            std::cin >> clientid;
            db.outputTransactionHistoryForClient(clientid);
            break;
        case '12':
            std::cout << "Enter clientid and date(format: YYYYMMDD:HH:MM:SS)\n";
            std::cin >> clientid >> date;
            db.outputTransactionsForSpecifiedDateForClient(clientid, date);
            break;
        case '13':
            db.outputTheOldestTransaction();
            break;
        case '14':
            db.outputClientsWithTheBiggestAmountOfTransactionsPerDay();
            break;
        case 'q':
            is_worked = false;
            break;
        default:
            std::cout << "Please enter correct option\n";
            break;
        }
    }
    return 0;
}