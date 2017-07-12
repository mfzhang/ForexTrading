//
// Created by Warmaster on 2017/07/10.
//

#include "TransactionHistory.h"

TransactionHistory::TransactionHistory(string c, double tp, int td, int v, int t) {
    this->currency=c;
    this->tradingPrice=tp;
    this->type=t;
    this->bought = td;
    this->sold = v;

}
