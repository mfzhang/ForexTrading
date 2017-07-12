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
    profit=0.0;
    profitRatio=0.0;
    loss=0.0;
    lossRatio=0.0;
    initialStartingCapital=buyCurr;
}

void TradingAgent::recordTransaction(string curr, double price, int traded, int volume, int type) {
    this->transactionList.push_back(new TransactionHistory(curr, price, traded, volume, type));
}

TradingAgent::~TradingAgent() {
    cout<<"Deleted Trader"<<endl;
    for(int i=0;i<transactionList.size();i++)
    {
        delete transactionList.at(i);
    }
}

void TradingAgent::conductTransaction(double buySignal, double sellSignal, vector<double> stratParameters,double bid,double ask) {
    if (buySignal > sellSignal && buyingCurrency > 0)
    {
        double vol = ((stratParameters.at(0) * buyingCurrency) / ask);
        buyingCurrency=buyingCurrency-vol;

        boughtCurrency=boughtCurrency+(vol*ask);
        recordTransaction(currencyUsedForBuying, ask, vol * ask, vol, 1);
    }else if (sellSignal>buySignal  && boughtCurrency>0)
        {

            double vol = (boughtCurrency * stratParameters.at(1));

            boughtCurrency=boughtCurrency-vol;

            buyingCurrency = buyingCurrency + vol / bid;

            recordTransaction(currencyThatIsBought, bid, (vol / bid), vol, -1);

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
            loss = abs(p);
            lossRatio=loss/transactionList.size();
        }
    //cout<<"Buying Currency: "<<to_string(buyingCurrency)<<endl;
    //cout<<"Bought Currency:"<<to_string(boughtCurrency)<<endl;

    //transactionList.clear();
}

void TradingAgent::resetTradingAgent() {
    profit=0.0;
    profitRatio=0.0;
    loss=0.0;
    lossRatio=0.0;

    transactionList.clear();

    boughtCurrency=0;
    buyingCurrency=initialStartingCapital;
}
