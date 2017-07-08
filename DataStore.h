/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DataStore.h
 * Author: Warmaster
 *
 * Created on 27 June 2017, 12:05 PM
 */
#include <string>
#include <vector>
#include <iostream>
#include <queue>
#include "Tick.h"
#include <fstream>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <stdlib.h>
#include "OHLC.h"
#include "IndicatorManager.h"
#ifndef DATASTORE_H
#define DATASTORE_H

using namespace std;

class DataStore
{
private:
    string fileName;
    vector<Tick> priceVector;
    vector<OHLC> ohlcVector;
    IndicatorManager * indicators;
public:
    DataStore();

    DataStore(int a);
    ~DataStore();
    void setFileName(string a);

    string getFileName();

    void addToPriceVector(string date, double bid, double ask, int vol);
    void printList();
    void printListOfOHLC();
    void addToOHLCVector(string a, double b, double c, double d, double e, int f);
    void readInTicksFromFile(string fn, int numberOfTicks, int startingIndex);
    void readInOLHCFromFile(string fn, int numberOfEntries, int startingIndex);

    double priceLookUpBuy(string date);
    double priceLookUpSell(string date);
    //int determineDecision(vector<int> indicator, int decision,vector<double> weightVector);
    
    
    //Returns the value of the indicators * weight vector
    double determineIfBuy(vector<int> indicatorList,vector<double> weightVector);
    double determineIfSell(vector<int> indicatorList,vector<double> weightVector);
    
    void refreshBuyIndicators();
    void refreshSellIndicators();
};

#endif /* DATASTORE_H */

