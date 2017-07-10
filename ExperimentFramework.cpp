//
// Created by Warmaster on 2017/07/10.
//

#include "ExperimentFramework.h"

ExperimentFramework::ExperimentFramework()
{

}

ExperimentFramework::ExperimentFramework(int swarmSize,int numberOfTraders,int objectiveChoice,
                                         string buyingC,string boughtC,
                                         double initialTradingCapital,string OLHCfn,string tickfn,int numTradingPeriods)
{
    this->swarmSize=swarmSize;
    numberOfTradingPeriods=numTradingPeriods;
    dataStore=new DataStore(7);
    weightVectorSwarm=new WeightVectorSwarm(swarmSize);
    parameterSwarm=new ParameterSwarm(swarmSize);
    strategySwarm=new StrategySwarm(swarmSize);
    objChoice=objectiveChoice;

    dataStore->setOLHCfn(OLHCfn);
    dataStore->setTickfn(tickfn);

    for(int i=0;i<numberOfTraders;i++)
    {
        traderPool.push_back(new TradingAgent(buyingC,boughtC,initialTradingCapital,0));
    }
}

ExperimentFramework::~ExperimentFramework()
{
    delete weightVectorSwarm;
    delete parameterSwarm;
    delete strategySwarm;

    for(int i=0;i<traderPool.size();i++)
    {
        delete traderPool.at(i);
    }
}

void ExperimentFramework::doExperiment() {
    int runNumber=1;
    int numberOfItemsInPeriod=50;
    //initialise everything
    weightVectorSwarm->initialiseSwarm();
    parameterSwarm->initialiseSwarm();
    strategySwarm->initialiseSwarm();

    vector<int> ab;

    ab.push_back(0);
    ab.push_back(1);
    ab.push_back(2);
    ab.push_back(3);
    ab.push_back(4);
    ab.push_back(5);
    ab.push_back(6);

    switch (this->objChoice)
    {
        case 0: weightVectorSwarm->setProblemType(false);
                parameterSwarm->setProblemType(false);
                strategySwarm->setProblemType(false);
            break;
        case 1: weightVectorSwarm->setProblemType(false);
            parameterSwarm->setProblemType(false);
            strategySwarm->setProblemType(false);
            break;
        case 2: weightVectorSwarm->setProblemType(true);
            parameterSwarm->setProblemType(true);
            strategySwarm->setProblemType(true);
            break;
        case 3:weightVectorSwarm->setProblemType(true);
            parameterSwarm->setProblemType(true);
            strategySwarm->setProblemType(true);
            break;
    }

    for(int i=0;i<runNumber;i++)
    {
        ///Reset Swarms and Agents
        //Swarms
        weightVectorSwarm->resetSwarm();
        parameterSwarm->resetSwarm();
        strategySwarm->resetSwarm();

        weightVectorSwarm->initialiseSwarm();
        parameterSwarm->initialiseSwarm();
        strategySwarm->initialiseSwarm();

        //Traders
        for(int j=0;j<traderPool.size();j++)
        {
            traderPool.at(j)->resetTradingAgent();
        }

        ///Loading Trading Data
        dataStore->readInOLHCFromFile(dataStore->getOLHCfn(),numberOfItemsInPeriod,0);
        dataStore->readInTicksFromFile(dataStore->getTickfn());

        dataStore->refreshBuyIndicators();
        dataStore->refreshSellIndicators();

        ////Fitness Evaluation of PSO Algorithm
        for(int j=1;j<numberOfTradingPeriods;j++)
        {
            dataStore->readInOLHCFromFile(dataStore->getOLHCfn(),numberOfItemsInPeriod,0);
            dataStore->readInTicksFromFile(dataStore->getTickfn());
            dataStore->refreshBuyIndicators();
            dataStore->refreshSellIndicators();
            traderPool.at(j)->conductTransaction(dataStore->determineIfBuy(ab,weightVectorSwarm->swarm.at(0)->parameters),
                                              dataStore->determineIfSell(ab,weightVectorSwarm->swarm.at(0)->parameters),
                                              strategySwarm->swarm.at(0)->parameters,
                                                 dataStore->latestPriceSell(),
                                                 dataStore->latestPriceBuy());

        }
        //PSO Updates
        for (int k=0;k<swarmSize;k++)
        {
            weightVectorSwarm->updatePSOSwarm(parameterSwarm->swarm);
            strategySwarm->updatePSOSwarm(parameterSwarm->swarm);
            parameterSwarm->updatePSOSwarm(parameterSwarm->swarm);
        }

        ///Record Run Data
        recordRunData();
    }
}

void ExperimentFramework::recordRunData() {

}
