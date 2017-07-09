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

#include <cstdlib>
#include <iostream>
#include "DataStore.h"
#include "WeightVectorSwarm.h"
#include "StrategySwarm.h"
#include "ParameterSwarm.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    
    
    std::random_device rd;
    std::mt19937 e2(rd());
    std::uniform_real_distribution<> dist(0, 2+1);



    DataStore * a=new DataStore(6);
   
    cout<<"Hello World"<<endl;
    vector<int> ab;
    vector<double> wv;
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

    a->printList();
    a->printListOfOHLC();

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


    swarm1->printParticles();
    swarm2->printParticles();
    swarm3->printParticles();

    swarm1->resetSwarm();
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
    return 0;
}

