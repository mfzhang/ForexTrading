/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   IndicatorManager.h
 * Author: Warmaster
 *
 * Created on 28 June 2017, 1:17 PM
 */

#ifndef INDICATORMANAGER_H
#define INDICATORMANAGER_H

#include "OHLC.h"
#include "Tick.h"
#include <vector>
#include <cstring>
#include <stdlib.h>
#include <string>
#include <iostream>

using namespace std;
class IndicatorManager
{
public:
    IndicatorManager(int size);

    
    ///Helper Functions
    //Produce transformed vectors with indicators giving signals either to act 1, or do nothing, -1
    vector<int> calculateBuyIndicatorVector(vector<int> indicatorList);
    vector<int> calculateSellIndicatorVector(vector<int> indicatorList);
    
    ///Will return values pre-computed to the caller for each indicator requested
    double requestIndicatorReadingBuy(int choiceOfIndicator);
    double requestIndicatorReadingSell(int choiceOfIndicator);
    int transformFunctionBuy(int indicator);
    int transformFunctionSell(int indicator);

    
    /**
     *  function is called before populating vector of indicators for each trading agent
     *  Call first, then populate the decision vector by accessing the values for each thing
     */
    void populateBuyIndicatorVariables(vector<OHLC> ohlcList, vector<Tick> priceList);
    void populateSellIndicatorVariables(vector<OHLC> ohlcList, vector<Tick> priceList);
    ///Indicators
    /*
     * Functions that use Ticks instead of OHLC must always be sent the index up to the last 
     * OHLC value.
     */
    double averageDirectionalMovement(vector<OHLC> eventList);
    
    double commodityChannelIndex(vector<OHLC> eventList);
    
    double bandWidthBoundingScoreAsk(vector<Tick> eventList);
    double bandWidthBoundingScoreBid(vector<Tick> eventList);
    
    double directionalIndexPlus(vector<OHLC> eventList);
    double directionalIndexMinus(vector<OHLC> eventList);
    
    double momentumIndicatorBid(vector<Tick> eventList);
    double momentumIndicatorAsk(vector<Tick> eventList);
    
    double relativeStrengthIndicator(vector<OHLC> eventList);
    
    double simpleMovingAverageAsk(vector<Tick> eventList);
    double simpleMovingAverageBid(vector<Tick> eventList);
    double simpleMovingAverageOHLC(vector<OHLC> eventList);

    static void setFirstRunToFalse();

    static void setFirstRunToTrue();
private:
    /**
     * Each of the vectors below contain all of the prior and current decisions
     * made by all indicators
     */
    vector<double> priorBuy;
    vector<double> priorSell;
    vector<double> currBuy;
    vector<double> currSell;


    static bool firstRun;


    //OHLC
    double priorOHLC;
    double currOHLC;
    ///AXD
    double priorADX;
    double priorAsk;
    double priorBid;
    
    double currADX;
    double currAsk;
    double currBid;
    
    ///CCI
    double priorCCI;
    double currCCI;
    
    //Band Witdh
    double currBandWidthAsk;
    double currBandWidthBid;
    double priorBandWidthAsk;
    double priorBandWidthBid;
    
    //Momentum
    double currMomentumAsk;
    double currMomentumBid;
    double priorMomentumAsk;
    double priorMomentumBid;
    
    //Relative Strength Indicator
    double priorRSI;
    double currRSI;
    
    //Directional Movement
    double priorDIplus;
    double priorDIminus;
    double currDIplus;
    double currDIminus;
    
};

#endif /* INDICATORMANAGER_H */

