//
// Created by Warmaster on 2017/07/10.
//

#ifndef TRANSACTIONHISTORY_H
#define TRANSACTIONHISTORY_H

#include <string>
using namespace std;

class TransactionHistory {
public:
    string currency;
    double tradingPrice;
    int bought;
    int sold;
    int type;

    TransactionHistory(string c, double tp, int td, int v, int t);
};


#endif //TRANSACTIONHISTORY_H
