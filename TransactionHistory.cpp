//
// Created by Warmaster on 2017/07/10.
//

#include "TransactionHistory.h"

TransactionHistory::TransactionHistory(string c, double tp, int v, int t) {
    this->currency=c;
    this->tradingPrice=tp;
    this->type=t;
    this->volume=v;
}
