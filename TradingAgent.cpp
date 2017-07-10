//
// Created by Warmaster on 2017/07/10.
//

#include "TradingAgent.h"

string TradingAgent::getBuyingCurrency() {
    return currencyUsedForBuying;
}

string TradingAgent::getBoughtCurrency() {
    return currencyThatIsBought;
}

void TradingAgent::setBuyingCurrency(string a) {
    this->currencyUsedForBuying=a;
}

void TradingAgent::setBoughtCurrency(string a) {
    this->currencyThatIsBought=a;
}

TradingAgent::TradingAgent(string buyCurrency,string boughtTCurrency, double buyCurr, double boughtCurr) {
    currencyUsedForBuying=buyCurrency;
    currencyThatIsBought=boughtTCurrency;

    boughtCurrency=boughtCurr;
    buyingCurrency=buyCurr;
    profit=0;
    initialStartingCapital=buyCurr;
}

void TradingAgent::recordTransaction(string curr, double price, int volume, int type) {
    this->transactionList.push_back(new TransactionHistory(curr,price,volume,type));
}

TradingAgent::~TradingAgent() {
    cout<<"Deleted Trader"<<endl;
    for(int i=0;i<transactionList.size();i++)
    {
        delete transactionList.at(i);
    }
}

void TradingAgent::conductTransaction(double buySignal, double sellSignal, vector<double> stratParameters,double bid,double ask) {
    if (buySignal>sellSignal && buyingCurrency>0)
    {
        cout<<"BOUGHT"<<endl;
        double vol=floor((stratParameters.at(0)*buyingCurrency)/ask);
        boughtCurrency=boughtCurrency+vol;
        buyingCurrency=buyingCurrency-floor((stratParameters.at(0)*buyingCurrency));
        cout<<"Current Buying Currency: "<<buyingCurrency<<endl;
        cout<<"Current Bought Currency: "<<boughtCurrency<<endl;
        recordTransaction(currencyUsedForBuying,ask,vol,1);
    }else if (sellSignal>buySignal  && boughtCurrency>0)
        {
            cout<<"SOLD"<<endl;

            double vol=floor(boughtCurrency*stratParameters.at(1));

            boughtCurrency=boughtCurrency-vol;

            buyingCurrency=buyingCurrency+floor(bid*vol);

            cout<<"Current Buying Currency: "<<buyingCurrency<<endl;
            cout<<"Current Bought Currency: "<<boughtCurrency<<endl;
            recordTransaction(currencyThatIsBought,bid,vol,-1);

        }
}

void TradingAgent::calculatePerformanceMetrics() {
    double p=0.0;

    p=buyingCurrency-initialStartingCapital;
    if (p>0)
    {
        profit=p;
        profitRatio=profit/transactionList.size();
    } else
        {
            loss=p;
            lossRatio=loss/transactionList.size();
        }
    //cout<<"Buying Currency: "<<to_string(buyingCurrency)<<endl;
    //cout<<"Bought Currency:"<<to_string(boughtCurrency)<<endl;

    transactionList.clear();
}
