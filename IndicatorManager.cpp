/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   IndicatorManager.cpp
 * Author: Warmaster
 * 
 * Created on 28 June 2017, 1:17 PM
 */


#include <algorithm>
#include <cmath>

#include "IndicatorManager.h"
bool IndicatorManager::firstRun = true;

void IndicatorManager::setFirstRunToFalse()
{
    firstRun = false;
}

void IndicatorManager::setFirstRunToTrue()
{
    firstRun = true;
}

IndicatorManager::IndicatorManager(int size)
{

    priorADX = 0;
}

void IndicatorManager::populateBuyIndicatorVariables(vector<OHLC> ohlcList, vector<Tick> priceList)
{
    averageDirectionalMovement(ohlcList);
    bandWidthBoundingScoreAsk(priceList);
    commodityChannelIndex(ohlcList);
    directionalIndexPlus(ohlcList);
    directionalIndexMinus(ohlcList);
    momentumIndicatorAsk(priceList);
    relativeStrengthIndicator(ohlcList);
    simpleMovingAverageAsk(priceList);
    simpleMovingAverageOHLC(ohlcList);
}

void IndicatorManager::populateSellIndicatorVariables(vector<OHLC> ohlcList, vector<Tick> priceList)
{
    bandWidthBoundingScoreBid(priceList);
    momentumIndicatorBid(priceList);
    simpleMovingAverageBid(priceList);
}    

vector<int> IndicatorManager::calculateBuyIndicatorVector(vector<int> indicatorList)
{
    priorBuy.resize(indicatorList.size());
    currBuy.resize(priorBuy.size());
    vector<int> indicatorResults;

    double mp = 0.0;
    for (int i = 0; i < indicatorList.size(); i++) {
        mp = requestIndicatorReadingBuy(indicatorList.at(i));
        if (this->firstRun == true) {
            priorBuy.at(i) = mp;
        }
        else {
            priorBuy.at(i) = currBuy.at(i);
        }
        currBuy.at(i) = mp;
    }
    indicatorResults.clear();
    indicatorResults.resize(indicatorList.size());

    for (int i = 0; i < currBuy.size(); i++) {
        indicatorResults.at(i) = transformFunctionBuy(indicatorList.at(i));
    }
    firstRun = false;

    return indicatorResults;
}

vector<int> IndicatorManager::calculateSellIndicatorVector(vector<int> indicatorList)
{
    priorSell.resize(indicatorList.size());
    currSell.resize(priorSell.size());
    vector<int> indicatorResults;

    double mp = 0.0;
    for (int i = 0; i < indicatorList.size(); i++) {
        mp = requestIndicatorReadingSell(indicatorList.at(i));
        if (this->firstRun == true) {
            priorSell.at(i) = mp;

        }
        else {
            priorSell.at(i) = currSell.at(i);
        }
        currSell.at(i) = mp;
    }
    indicatorResults.clear();
    indicatorResults.resize(indicatorList.size());

    for (int i = 0; i < currSell.size(); i++) {
        indicatorResults.at(i) = transformFunctionSell(indicatorList.at(i));
    }
    firstRun = false;

    return indicatorResults;
}

double IndicatorManager::requestIndicatorReadingBuy(int choiceOfIndicator)
{

    switch (choiceOfIndicator) {
    case 0: return currOHLC;
        break;
    case 1: return currAsk;
        break;
    case 2: return currADX;
        break;
    case 3: return currBandWidthAsk;
        break;
    case 4: return currCCI;
        break;
    case 5: return currMomentumAsk;
        break;
    case 6: return currRSI;
        break;
    }

    return 0.0;

}

double IndicatorManager::requestIndicatorReadingSell(int choiceOfIndicator)
{

    switch (choiceOfIndicator) {
    case 0: return currOHLC;
        break;
    case 1: return currBid;
        break;
    case 2: return currADX;
        break;
    case 3: return currBandWidthBid;
        break;
    case 4: return currCCI;
        break;
    case 5: return currMomentumBid;
        break;
    case 6: return currRSI;
        break;
    }

    return 0.0;

}

int IndicatorManager::transformFunctionBuy(int indicator)
{
    int decision = -1;
    ///Implement Transformation Function
    /*
     Decide how each of the values is going to be interpreted
     */
    switch (indicator) {
    case 0: if (currOHLC < priorOHLC) {
        decision=1;
        } 
        break;
    case 1: if (currAsk<priorAsk){
        decision=1;
        } 
        break;
    case 2: if (currADX>20 && currDIplus>currDIminus){
        decision=1;
    }
    if (currADX<10) decision=-1;
        break;
    case 3: if (currBandWidthAsk<=priorBandWidthAsk && currDIplus>currDIminus){
        decision=1;} 
        break;
    case 4: if (currCCI>100){decision=1;}
        break;
    case 5: if (currMomentumAsk<currMomentumAsk){decision=1;}
        break;
    case 6: if (currRSI>priorRSI && priorRSI>=30){decision=1;}
        break;
    }


    return decision;
}

int IndicatorManager::transformFunctionSell(int indicator)
{
    int decision = -1;
    ///Implement Transformation Function
    /*
     Decide how each of the values is going to be interpreted
     */
switch (indicator) {
    case 0: if (currOHLC > priorOHLC) {
        decision=1;
        } 
        break;
    case 1: if (currBid>priorBid){
        decision=1;
        } 
        break;
    case 2: if (currADX<20 && currDIminus>currDIplus){
        decision=1;
    }
        break;
    case 3: if (currBandWidthBid<=priorBandWidthBid && currDIminus>currDIplus){
        decision=1;} 
        break;
    case 4: if (currCCI<-100){decision=1;}
        break;
    case 5: if (currMomentumBid>currMomentumBid){decision=1;}
        break;
    case 6: if (currRSI<priorRSI && priorRSI>=70){decision=1;}
        break;
    }

    return decision;
}

/**
 * Indicators  
 */

double IndicatorManager::simpleMovingAverageOHLC(vector<OHLC> eventList)
{
    double a = 0;

    for (int i = 0; i < eventList.size(); i++) {
        a = a + (eventList.at(i).getClose());
    }
    if (firstRun == true) {
        priorOHLC = (double) a / eventList.size();
    }
    else {
        priorOHLC = currOHLC;
    }
    currOHLC = (double) a / eventList.size();
    return (double) a / eventList.size();
}

double IndicatorManager::averageDirectionalMovement(vector<OHLC> eventList)
{
    double currHigh, currLow, priorHigh, priorLow, priorClose;
    double DMplus, DMminus;


    double TR = 0.0;
    double smma1 = 0.0, smma2 = 0.0;
    priorClose = eventList.at(0).getClose();
    priorHigh = eventList.at(0).getHigh();
    priorLow = eventList.at(0).getLow();
    priorClose = eventList.at(0).getClose();
    for (int i = 1; i < eventList.size(); i++) {
        currHigh = eventList.at(i).getHigh();
        currLow = eventList.at(i).getLow();


        if (currHigh - priorHigh > currLow - priorLow && currHigh - priorHigh > 0) {
            DMplus = currHigh - priorHigh;
        }
        else {
            DMplus = 0;
        }

        if (priorLow - currLow > currHigh - priorHigh && priorLow - currLow > 0) {
            DMminus = priorLow - currLow;
        }
        else {
            DMminus = 0;
        }
        priorHigh = eventList.at(i - 1).getHigh();
        priorLow = eventList.at(i - 1).getLow();
        priorClose = eventList.at(i - 1).getClose();


        smma1 = smma1 + DMplus;
        smma2 = smma2 + DMminus;
        //TR=TR+max(max(abs(currHigh-currLow),abs(currHigh-priorClose)),abs(currLow-priorClose));
        TR = TR + max(max(abs(eventList.at(i).getHigh() - eventList.at(i).getLow()),
                          abs(eventList.at(i).getHigh() - priorClose)),
                      abs(eventList.at(i).getHigh() - priorClose));
        priorClose = eventList.at(i).getClose();
    }
    TR = TR / eventList.size();
    smma1 = (double) smma1 / eventList.size();
    smma2 = (double) smma2 / eventList.size();
    double posDI, negDI;

    posDI = (100 * smma1) / TR;
    negDI = (100 * smma2) / TR;

    double DirDiff, DiSum, DX;
    DirDiff = abs(posDI - negDI);

    DiSum = posDI + negDI;
    DX = (DirDiff / DiSum)*100;

    if (firstRun == true) {
        priorADX = DX;
    }
    else {
        priorADX = currADX;
    }
    currADX = DX;
    return DX;
}

double IndicatorManager::simpleMovingAverageBid(vector<Tick> eventList)
{
    double a = 0;

    for (int i = 0; i < eventList.size(); i++) {
        a = a + (eventList.at(i).getBidQuote());
    }
    if (firstRun == true) {
        priorBid = (double) a / eventList.size();
    }
    else {
        priorBid = currBid;
    }
    currBid = (double) a / eventList.size();
    return (double) a / eventList.size();

}

double IndicatorManager::simpleMovingAverageAsk(vector<Tick> eventList)
{
    double a = 0;

    for (int i = 0; i < eventList.size(); i++) {
        a = a + (eventList.at(i).getAskQuote());
    }
    if (firstRun == true) {
        priorAsk = (double) a / eventList.size();
    }
    else {
        priorAsk = currAsk;
    }
    currAsk = (double) a / eventList.size();
    return (double) a / eventList.size();

}

double IndicatorManager::bandWidthBoundingScoreBid(vector<Tick> eventList)
{
    int y = 2;

    double movingAverageMid = simpleMovingAverageAsk(eventList);
    double movingAverageUpper, movingAverageLower;

    double stdDev = 0.0, sum = 0.0;

    for (int i = 0; i < eventList.size(); i++) {
        sum = sum + pow(eventList.at(0).getBidQuote() - movingAverageMid, 2);
    }
    stdDev = sqrt((double) sum / eventList.size());
    movingAverageLower = movingAverageMid - y*stdDev;
    movingAverageUpper = movingAverageMid + y*stdDev;

    //Logic to transform value based on bound width/
    int outlierCount = 0;

    for (int i = 0; i < eventList.size(); i++) {
        if (eventList.at(i).getBidQuote() < movingAverageLower ||
            eventList.at(i).getBidQuote() > movingAverageUpper) {
            outlierCount++;
        }
    }
    if (firstRun == true) {
        priorBandWidthBid = (eventList.size() - outlierCount);
    }
    else {
        priorBandWidthBid = currBandWidthBid;
    }
    currBandWidthBid = (eventList.size() - outlierCount);

    return (eventList.size() - outlierCount);
}

double IndicatorManager::bandWidthBoundingScoreAsk(vector<Tick> eventList)
{
    int y = 2;

    double movingAverageMid = simpleMovingAverageAsk(eventList);
    double movingAverageUpper, movingAverageLower;

    double stdDev = 0.0, sum = 0.0;

    for (int i = 0; i < eventList.size(); i++) {
        sum = sum + pow(eventList.at(0).getAskQuote() - movingAverageMid, 2);
    }
    stdDev = sqrt((double) sum / eventList.size());
    movingAverageLower = movingAverageMid - y*stdDev;
    movingAverageUpper = movingAverageMid + y*stdDev;

    //Logic to transform value based on bound width/
    /*
     Look at if the last value is outside the bands
     */
    int outlierCount = 0;

    for (int i = 0; i < eventList.size(); i++) {
        if (eventList.at(i).getAskQuote() < movingAverageLower ||
            eventList.at(i).getAskQuote() > movingAverageUpper) {
            outlierCount++;
        }
    }
    if (firstRun == true) {
        priorBandWidthAsk = (eventList.size() - outlierCount);
    }
    else {
        priorBandWidthAsk = currBandWidthAsk;
    }
    currBandWidthAsk = (eventList.size() - outlierCount);

    return (eventList.size() - outlierCount);

}

double IndicatorManager::commodityChannelIndex(vector<OHLC> eventList)
{
    double cci = 0;
    double dAvg = 0, closeAvg = 0;
    double a = 0, m = 0;

    for (int i = 0; i < eventList.size(); i++) {
        a = a + (eventList.at(i).getHigh() + eventList.at(i).getLow() + eventList.at(i).getClose()) / 3.0;
        closeAvg = closeAvg + eventList.at(i).getClose();
    }

    closeAvg = (double) closeAvg / eventList.size();

    m = (eventList.back().getHigh() + eventList.back().getLow() + eventList.back().getClose()) / 3.0;

    for (int i = 0; i < eventList.size(); i++) {
        dAvg = dAvg + abs(eventList.at(i).getClose() - closeAvg);
    }
    dAvg = dAvg / eventList.size();

    cci = (m - a) / (0.015 * dAvg);

    if (firstRun == true) {
        priorCCI = cci;
    }
    else {
        priorCCI = currCCI;
    }
    currCCI = cci;

    return cci;
}

double IndicatorManager::momentumIndicatorAsk(vector<Tick> eventList)
{
    double priceAvg = 0.0;

    for (int i = eventList.size() - 1; i >= 1; i--) {
        priceAvg = priceAvg + (eventList.at(i).getAskQuote() - eventList.at(i - 1).getAskQuote());
    }
    priceAvg = (double) priceAvg / eventList.size();

    if (firstRun == true) {
        priorMomentumAsk = priceAvg;
    }
    else {
        currMomentumAsk = priorMomentumAsk;
    }
    currMomentumAsk = priceAvg;

    return priceAvg;
}

double IndicatorManager::momentumIndicatorBid(vector<Tick> eventList)
{
    double priceAvg = 0.0;

    for (int i = eventList.size() - 1; i >= 1; i--) {
        priceAvg = priceAvg + (eventList.at(i).getBidQuote() - eventList.at(i - 1).getBidQuote());
    }
    priceAvg = (double) priceAvg / eventList.size();

    if (firstRun == true) {
        priorMomentumBid = priceAvg;
    }
    else {
        currMomentumBid = priorMomentumBid;
    }
    currMomentumBid = priceAvg;

    return priceAvg;
}

double IndicatorManager::relativeStrengthIndicator(vector<OHLC> eventList)
{
    double rsi = 0.0;

    double u = 0.0, d = 0.0;

    for (int i = eventList.size() - 2; i >= 1; i--) {
        if (eventList.at(i).getClose() > eventList.at(i - 1).getClose()) {
            //up period
            u = u + eventList.at(i).getClose() - eventList.at(i - 1).getClose();
            d = d + 0;
        }
        else {
            //down period
            d = d + eventList.at(i - 1).getClose() - eventList.at(i).getClose();
            u = u + 0;
        }
    }
    u = u / eventList.size();
    d = d / eventList.size();

    rsi = 100 - (100 / (1 + (u / d)));

    if (firstRun == true) {
        priorRSI = rsi;
    }
    else {
        currRSI = priorRSI;
    }
    currRSI = rsi;

    return rsi;
}

double IndicatorManager::directionalIndexMinus(vector<OHLC> eventList)
{
    double currHigh, currLow, priorHigh, priorLow, priorClose;
    double DMminus;


    double TR = 0.0;
    double smma2 = 0.0;
    priorClose = eventList.at(0).getClose();
    priorHigh = eventList.at(0).getHigh();
    priorLow = eventList.at(0).getLow();
    priorClose = eventList.at(0).getClose();
    for (int i = 1; i < eventList.size(); i++) {
        currHigh = eventList.at(i).getHigh();
        currLow = eventList.at(i).getLow();

        if (priorLow - currLow > currHigh - priorHigh && priorLow - currLow > 0) {
            DMminus = priorLow - currLow;
        }
        else {
            DMminus = 0;
        }
        priorHigh = eventList.at(i - 1).getHigh();
        priorLow = eventList.at(i - 1).getLow();
        priorClose = eventList.at(i - 1).getClose();

        smma2 = smma2 + DMminus;
        //TR=TR+max(max(abs(currHigh-currLow),abs(currHigh-priorClose)),abs(currLow-priorClose));
        TR = TR + max(max(abs(eventList.at(i).getHigh() - eventList.at(i).getLow()),
                          abs(eventList.at(i).getHigh() - priorClose)),
                      abs(eventList.at(i).getHigh() - priorClose));
        priorClose = eventList.at(i).getClose();
    }
    TR = TR / eventList.size();

    smma2 = (double) smma2 / eventList.size();
    double negDI;

    negDI = (100 * smma2) / TR;

    if (firstRun == true) {
        priorDIminus = negDI;
    }
    else {
        priorDIminus = currDIminus;
    }
    currDIminus = negDI;
    return negDI;
}

double IndicatorManager::directionalIndexPlus(vector<OHLC> eventList)
{
    double currHigh, currLow, priorHigh, priorLow, priorClose;
    double DMplus;


    double TR = 0.0;
    double smma2 = 0.0;
    priorClose = eventList.at(0).getClose();
    priorHigh = eventList.at(0).getHigh();
    priorLow = eventList.at(0).getLow();
    priorClose = eventList.at(0).getClose();
    for (int i = 1; i < eventList.size(); i++) {
        currHigh = eventList.at(i).getHigh();
        currLow = eventList.at(i).getLow();

        if (currHigh - priorHigh > currLow - priorLow && currHigh - priorHigh > 0) {
            DMplus = currHigh - priorHigh;
        }
        else {
            DMplus = 0;
        }
        priorHigh = eventList.at(i - 1).getHigh();
        priorLow = eventList.at(i - 1).getLow();
        priorClose = eventList.at(i - 1).getClose();

        smma2 = smma2 + DMplus;
        //TR=TR+max(max(abs(currHigh-currLow),abs(currHigh-priorClose)),abs(currLow-priorClose));
        TR = TR + max(max(abs(eventList.at(i).getHigh() - eventList.at(i).getLow()),
                          abs(eventList.at(i).getHigh() - priorClose)),
                      abs(eventList.at(i).getHigh() - priorClose));
        priorClose = eventList.at(i).getClose();
    }
    TR = TR / eventList.size();

    smma2 = (double) smma2 / eventList.size();
    double posDI;

    posDI = (100 * smma2) / TR;

    if (firstRun == true) {
        priorDIplus = posDI;
    }
    else {
        priorDIplus = currDIplus;
    }
    currDIplus = posDI;
    return posDI;
}
