/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Warmaster
 *
 * Created on 27 June 2017, 12:00 PM
 */

#include <vector>
#include <iostream>
#include "DataStore.h"
#include "WeightVectorSwarm.h"

#include "ExperimentFramework.h"
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    
    /*
    std::random_device rd;
    std::mt19937 e2(rd());
    std::uniform_real_distribution<> dist(0, 2+1);


    vector<TradingAgent *> traders;
    DataStore * a=new DataStore(7);


    traders.push_back(new TradingAgent("USD","ZAR",1000,0));
    cout<<"Hello World"<<endl;
    vector<double> wv;

    vector<int> ab;

    ab.push_back(0);
    ab.push_back(1);
    ab.push_back(2);
    ab.push_back(3);
    ab.push_back(4);
    ab.push_back(5);
    ab.push_back(6);
    
    wv.push_back(0.1);
    wv.push_back(0.1);
    wv.push_back(0.1);
    wv.push_back(0.1);
    wv.push_back(0.1);
    wv.push_back(0.1);
    wv.push_back(0.1);

    a->readInOLHCFromFile("DAT_ASCII_USDZAR_M1_2016.csv",20,0);
    a->readInTicksFromFile("DAT_ASCII_USDZAR_T_201601.csv",100,0);
    a->refreshBuyIndicators();
    a->refreshSellIndicators();
    a->printListOfOHLC();
    cout<<to_string(a->priceLookUpBuy("20160103 173900"))<<endl;
    cout<<to_string(a->priceLookUpSell("20160103 173900"))<<endl;


    cout<<"Buy Decision: "<<to_string(a->determineIfBuy(ab,wv))<<endl;
    cout<<"Sell Decision: "<<to_string(a->determineIfSell(ab,wv))<<endl;
    a->readInOLHCFromFile("DAT_ASCII_USDZAR_M1_2016.csv",20,20);
    a->readInTicksFromFile("DAT_ASCII_USDZAR_T_201601.csv",100,100);
    a->refreshBuyIndicators();
    a->refreshSellIndicators();
    cout<<"Buy Decision: "<<to_string(a->determineIfBuy(ab,wv))<<endl;
    cout<<"Sell Decision: "<<to_string(a->determineIfSell(ab,wv))<<endl;




    cout<<"+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
    cout<<"+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
    WeightVectorSwarm * swarm1;
    ParameterSwarm * swarm2;
    StrategySwarm * swarm3;
    cout<<"Swarm 1"<<endl;
    swarm1=new WeightVectorSwarm(3);
    swarm1->initialiseSwarm();
    cout<<"Swarm 2"<<endl;
    swarm2=new ParameterSwarm(3);
    swarm2->initialiseSwarm();
    cout<<"Swarm 3"<<endl;
    swarm3=new StrategySwarm(3);
    swarm3->initialiseSwarm();

    a->readInOLHCFromFile("DAT_ASCII_USDZAR_M1_2016.csv",100,0);
    a->readInTicksFromFile("DAT_ASCII_USDZAR_T_201601.csv",500,0);
    a->refreshBuyIndicators();
    a->refreshSellIndicators();
    traders.at(0)->conductTransaction(a->determineIfBuy(ab,swarm1->swarm.at(0)->parameters),
                                      a->determineIfSell(ab,swarm1->swarm.at(0)->parameters),
                                      swarm3->swarm.at(0)->parameters,a->latestPriceSell(),a->latestPriceBuy());


    a->readInOLHCFromFile("DAT_ASCII_USDZAR_M1_2016.csv",100,100);
    a->readInTicksFromFile("DAT_ASCII_USDZAR_T_201601.csv",500,500);
    a->refreshBuyIndicators();
    a->refreshSellIndicators();
    traders.at(0)->conductTransaction(a->determineIfBuy(ab,swarm1->swarm.at(0)->parameters),
                                      a->determineIfSell(ab,swarm1->swarm.at(0)->parameters),
                                      swarm3->swarm.at(0)->parameters,a->latestPriceSell(),a->latestPriceBuy());

    a->readInOLHCFromFile("DAT_ASCII_USDZAR_M1_2016.csv",100,200);
    a->readInTicksFromFile("DAT_ASCII_USDZAR_T_201601.csv",500,1000);
    a->refreshBuyIndicators();
    a->refreshSellIndicators();
    traders.at(0)->conductTransaction(a->determineIfBuy(ab,swarm1->swarm.at(0)->parameters),
                                      a->determineIfSell(ab,swarm1->swarm.at(0)->parameters),
                                      swarm3->swarm.at(0)->parameters,a->latestPriceSell(),a->latestPriceBuy());

    a->readInOLHCFromFile("DAT_ASCII_USDZAR_M1_2016.csv",100,300);
    a->readInTicksFromFile("DAT_ASCII_USDZAR_T_201601.csv",500,1500);
    a->refreshBuyIndicators();
    a->refreshSellIndicators();
    traders.at(0)->conductTransaction(a->determineIfBuy(ab,swarm1->swarm.at(0)->parameters),
                                      a->determineIfSell(ab,swarm1->swarm.at(0)->parameters),
                                      swarm3->swarm.at(0)->parameters,a->latestPriceSell(),a->latestPriceBuy());

    a->readInOLHCFromFile("DAT_ASCII_USDZAR_M1_2016.csv",100,400);
    a->readInTicksFromFile("DAT_ASCII_USDZAR_T_201601.csv",500,2000);
    a->refreshBuyIndicators();
    a->refreshSellIndicators();
    traders.at(0)->conductTransaction(a->determineIfBuy(ab,swarm1->swarm.at(0)->parameters),
                                      a->determineIfSell(ab,swarm1->swarm.at(0)->parameters),
                                      swarm3->swarm.at(0)->parameters,a->latestPriceSell(),a->latestPriceBuy());

    swarm1->printParticles();
    swarm2->printParticles();
    swarm3->printParticles();

    a->readInOLHCFromFile("DAT_ASCII_USDZAR_M1_2016.csv",50,0);
    a->readInTicksFromFile("DAT_ASCII_USDZAR_T_201601.csv");

    a->refreshBuyIndicators();
    a->refreshSellIndicators();
    for(int i=1;i<50;i++)
    {
        a->readInOLHCFromFile("DAT_ASCII_USDZAR_M1_2016.csv",50,i*50);
        a->readInTicksFromFile("DAT_ASCII_USDZAR_T_201601.csv");
        a->refreshBuyIndicators();
        a->refreshSellIndicators();
        traders.at(0)->conductTransaction(a->determineIfBuy(ab,swarm1->swarm.at(0)->parameters),
                                          a->determineIfSell(ab,swarm1->swarm.at(0)->parameters),
                                          swarm3->swarm.at(0)->parameters,a->latestPriceSell(),a->latestPriceBuy());

    }
    traders.at(0)->calculatePerformanceMetrics();
    cout<<"Profit from trading period: "<<traders.at(0)->profit<<endl;

    swarm1->resetSwarm();]
    swarm2->resetSwarm();
    swarm3->resetSwarm();

    swarm1->initialiseSwarm();
    swarm2->initialiseSwarm();
    swarm3->initialiseSwarm();

    swarm1->printParticles();
    swarm2->printParticles();
    swarm3->printParticles();

    swarm1->setProblemType(true);
    swarm1->updatePSOSwarm(2.0,2.0,0.1);

    swarm2->setProblemType(true);
    swarm2->updatePSOSwarm(2.0,2.0,0.1);

    swarm3->setProblemType(true);
    swarm3->updatePSOSwarm(2.0,2.0,0.);

    swarm1->printParticles();
    swarm2->printParticles();
    swarm3->printParticles();

    delete swarm1;
    delete swarm2;
    delete swarm3;

    delete traders.at(0);

    */

    ExperimentFramework * a=new ExperimentFramework(5,5,0,"USD","ZAR",1000,"DAT_ASCII_USDZAR_M1_2016.csv","DAT_ASCII_USDZAR_T_201601.csv",10);

    a->doExperiment();
    cout<<"Finished!"<<endl;
    return 0;
}

