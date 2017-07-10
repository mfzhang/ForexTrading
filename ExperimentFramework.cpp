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
            for(int y=0;y<traderPool.size();y++)
            {
                dataStore->readInOLHCFromFile(dataStore->getOLHCfn(),numberOfItemsInPeriod,j*numberOfItemsInPeriod);
                dataStore->readInTicksFromFile(dataStore->getTickfn());
                dataStore->refreshBuyIndicators();
                dataStore->refreshSellIndicators();
                traderPool.at(y)->conductTransaction(dataStore->determineIfBuy(ab,weightVectorSwarm->swarm.at(y)->parameters),
                                                     dataStore->determineIfSell(ab,weightVectorSwarm->swarm.at(y)->parameters),
                                                     strategySwarm->swarm.at(y)->parameters,
                                                     dataStore->latestPriceSell(),
                                                     dataStore->latestPriceBuy());
            }

        }
        double tmpFit=0.0;
        for(int h=0;h<traderPool.size();h++)
        {
            traderPool.at(h)->calculatePerformanceMetrics();

            switch (this->objChoice)
            {
                case 0: tmpFit=traderPool.at(h)->profit;
                    break;
                case 1: tmpFit=traderPool.at(h)->profitRatio;
                    break;
                case 2: tmpFit=traderPool.at(h)->loss;
                    break;
                case 3:tmpFit=traderPool.at(h)->lossRatio;
                    break;
            }
            weightVectorSwarm->swarm.at(h)->setFitness(tmpFit);
            strategySwarm->swarm.at(h)->setFitness(tmpFit);
            parameterSwarm->swarm.at(h)->setFitness(tmpFit);

            switch (this->objChoice)
            {
                case 0:
                    if (tmpFit>weightVectorSwarm->swarm.at(h)->personalBestFitness)
                    {
                        weightVectorSwarm->swarm.at(h)->personalBestFitness=tmpFit;
                        weightVectorSwarm->swarm.at(h)->copyIntoPersonalBest(weightVectorSwarm->swarm.at(h)->parameters);
                    }
                    if (tmpFit>parameterSwarm->swarm.at(h)->personalBestFitness)
                    {
                        parameterSwarm->swarm.at(h)->personalBestFitness=tmpFit;
                        parameterSwarm->swarm.at(h)->copyIntoPersonalBest(parameterSwarm->swarm.at(h)->parameters);
                    }
                    if (tmpFit>strategySwarm->swarm.at(h)->personalBestFitness)
                    {
                        strategySwarm->swarm.at(h)->personalBestFitness=tmpFit;
                        strategySwarm->swarm.at(h)->copyIntoPersonalBest(strategySwarm->swarm.at(h)->parameters);
                    }
                    weightVectorSwarm->setBestParticleMax();
                    parameterSwarm->setBestParticleMax();
                    strategySwarm->setBestParticleMax();
                    break;
                case 1:
                    if (tmpFit>weightVectorSwarm->swarm.at(h)->personalBestFitness)
                    {
                        weightVectorSwarm->swarm.at(h)->personalBestFitness=tmpFit;
                        weightVectorSwarm->swarm.at(h)->copyIntoPersonalBest(weightVectorSwarm->swarm.at(h)->parameters);
                    }
                    if (tmpFit>parameterSwarm->swarm.at(h)->personalBestFitness)
                    {
                        parameterSwarm->swarm.at(h)->personalBestFitness=tmpFit;
                        parameterSwarm->swarm.at(h)->copyIntoPersonalBest(parameterSwarm->swarm.at(h)->parameters);
                    }
                    if (tmpFit>strategySwarm->swarm.at(h)->personalBestFitness)
                    {
                        strategySwarm->swarm.at(h)->personalBestFitness=tmpFit;
                        strategySwarm->swarm.at(h)->copyIntoPersonalBest(strategySwarm->swarm.at(h)->parameters);
                    }
                    weightVectorSwarm->setBestParticleMax();
                    parameterSwarm->setBestParticleMax();
                    strategySwarm->setBestParticleMax();
                    break;
                case 2:
                    if (tmpFit<weightVectorSwarm->swarm.at(h)->personalBestFitness)
                    {
                        weightVectorSwarm->swarm.at(h)->personalBestFitness=tmpFit;
                        weightVectorSwarm->swarm.at(h)->copyIntoPersonalBest(weightVectorSwarm->swarm.at(h)->parameters);
                    }
                    if (tmpFit<parameterSwarm->swarm.at(h)->personalBestFitness)
                    {
                        parameterSwarm->swarm.at(h)->personalBestFitness=tmpFit;
                        parameterSwarm->swarm.at(h)->copyIntoPersonalBest(parameterSwarm->swarm.at(h)->parameters);
                    }
                    if (tmpFit<strategySwarm->swarm.at(h)->personalBestFitness)
                    {
                        strategySwarm->swarm.at(h)->personalBestFitness=tmpFit;
                        strategySwarm->swarm.at(h)->copyIntoPersonalBest(strategySwarm->swarm.at(h)->parameters);
                    }
                    weightVectorSwarm->setBestParticleMin();
                    parameterSwarm->setBestParticleMin();
                    strategySwarm->setBestParticleMin();
                    break;

                case 3:
                    if (tmpFit<weightVectorSwarm->swarm.at(h)->fitness)
                    {
                        weightVectorSwarm->swarm.at(h)->personalBestFitness=tmpFit;
                        weightVectorSwarm->swarm.at(h)->copyIntoPersonalBest(weightVectorSwarm->swarm.at(h)->parameters);
                    }
                    if (tmpFit<parameterSwarm->swarm.at(h)->fitness)
                    {
                        parameterSwarm->swarm.at(h)->personalBestFitness=tmpFit;
                        parameterSwarm->swarm.at(h)->copyIntoPersonalBest(parameterSwarm->swarm.at(h)->parameters);
                    }
                    if (tmpFit<strategySwarm->swarm.at(h)->fitness)
                    {
                        strategySwarm->swarm.at(h)->personalBestFitness=tmpFit;
                        strategySwarm->swarm.at(h)->copyIntoPersonalBest(strategySwarm->swarm.at(h)->parameters);
                    }
                    weightVectorSwarm->setBestParticleMin();
                    parameterSwarm->setBestParticleMin();
                    strategySwarm->setBestParticleMin();
                    break;
            }

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
