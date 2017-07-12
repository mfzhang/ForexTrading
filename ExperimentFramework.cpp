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

void ExperimentFramework::doExperimentalTrial() {
    int runList[] = {50, 100, 150, 200, 250, 300, 400, 500, 600, 700, 800, 900, 1000};

    for (int i = 0; i < 1; i++) {
        doExperiment(runList[i]);
    }
}

void ExperimentFramework::doExperiment(int scope) {

    int bestTraderIndex = 0;
    int runNumber=1;

    int numberOfItemsInPeriod = scope;
    //initialise everything
    weightVectorSwarm->initialiseSwarm();
    parameterSwarm->initialiseSwarm();
    strategySwarm->initialiseSwarm();

    vector<double> traderD;
    vector<double> weightVectorD;
    vector<double> paramD;
    vector<double> strategyD;

    vector<int> ab;

    ab.push_back(0);
    ab.push_back(1);
    ab.push_back(2);
    ab.push_back(3);
    ab.push_back(4);
    ab.push_back(5);
    ab.push_back(6);

    switch (this->objChoice) {
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

    for (int i = 0; i < runNumber; i++) {
        ///Reset Swarms and Agents
        //Swarms
        weightVectorSwarm->resetSwarm();
        parameterSwarm->resetSwarm();
        strategySwarm->resetSwarm();

        weightVectorSwarm->initialiseSwarm();
        parameterSwarm->initialiseSwarm();
        strategySwarm->initialiseSwarm();

        //Traders
        for (int j = 0; j < traderPool.size(); j++) {
            traderPool.at(j)->resetTradingAgent();
        }

        ///Loading Trading Data
        dataStore->resetFirstRun();
        dataStore->readInOLHCFromFile(dataStore->getOLHCfn(),numberOfItemsInPeriod,0);
        dataStore->readInTicksFromFile(dataStore->getTickfn());

        dataStore->refreshBuyIndicators();
        dataStore->refreshSellIndicators();
        dataStore->setFirstRunToFalse();
        ////Fitness Evaluation of PSO Algorithm
        for (int j = 1; j < numberOfTradingPeriods; j++) {
            for (int y = 0; y < traderPool.size(); y++) {
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
            double tmpFit = 0.0;
            for (int h = 0; h < traderPool.size(); h++) {
                traderPool.at(h)->calculatePerformanceMetrics();

                switch (this->objChoice) {
                    case 0:
                        tmpFit = traderPool.at(h)->profit;
                        break;
                    case 1:
                        tmpFit = traderPool.at(h)->profitRatio;
                        break;
                    case 2:
                        tmpFit = traderPool.at(h)->loss;
                        break;
                    case 3:
                        tmpFit = traderPool.at(h)->lossRatio;
                        break;
                }
                weightVectorSwarm->swarm.at(h)->setFitness(tmpFit);
                strategySwarm->swarm.at(h)->setFitness(tmpFit);
                parameterSwarm->swarm.at(h)->setFitness(tmpFit);

                double valCom;

                switch (this->objChoice) {
                    case 0:
                        if (tmpFit > weightVectorSwarm->swarm.at(h)->personalBestFitness) {
                            weightVectorSwarm->swarm.at(h)->personalBestFitness = tmpFit;
                            weightVectorSwarm->swarm.at(h)->copyIntoPersonalBest(
                                    weightVectorSwarm->swarm.at(h)->parameters);
                        }
                        if (tmpFit > parameterSwarm->swarm.at(h)->personalBestFitness) {
                            parameterSwarm->swarm.at(h)->personalBestFitness = tmpFit;
                            parameterSwarm->swarm.at(h)->copyIntoPersonalBest(parameterSwarm->swarm.at(h)->parameters);
                        }
                        if (tmpFit > strategySwarm->swarm.at(h)->personalBestFitness) {
                            strategySwarm->swarm.at(h)->personalBestFitness = tmpFit;
                            strategySwarm->swarm.at(h)->copyIntoPersonalBest(strategySwarm->swarm.at(h)->parameters);
                        }
                        weightVectorSwarm->setBestParticleMax();
                        parameterSwarm->setBestParticleMax();
                        strategySwarm->setBestParticleMax();

                        valCom = traderPool.at(0)->profit;
                        for (int hh = 0; hh < traderPool.size(); hh++) {
                            if (traderPool.at(hh)->profit > valCom) {
                                valCom = traderPool.at(hh)->profit;
                                bestTraderIndex = hh;
                            }
                        }
                        break;
                    case 1:
                        if (tmpFit > weightVectorSwarm->swarm.at(h)->personalBestFitness) {
                            weightVectorSwarm->swarm.at(h)->personalBestFitness = tmpFit;
                            weightVectorSwarm->swarm.at(h)->copyIntoPersonalBest(
                                    weightVectorSwarm->swarm.at(h)->parameters);
                        }
                        if (tmpFit > parameterSwarm->swarm.at(h)->personalBestFitness) {
                            parameterSwarm->swarm.at(h)->personalBestFitness = tmpFit;
                            parameterSwarm->swarm.at(h)->copyIntoPersonalBest(parameterSwarm->swarm.at(h)->parameters);
                        }
                        if (tmpFit > strategySwarm->swarm.at(h)->personalBestFitness) {
                            strategySwarm->swarm.at(h)->personalBestFitness = tmpFit;
                            strategySwarm->swarm.at(h)->copyIntoPersonalBest(strategySwarm->swarm.at(h)->parameters);
                        }
                        weightVectorSwarm->setBestParticleMax();
                        parameterSwarm->setBestParticleMax();
                        strategySwarm->setBestParticleMax();

                        valCom = traderPool.at(0)->profitRatio;
                        for (int hh = 0; hh < traderPool.size(); hh++) {
                            if (traderPool.at(hh)->profitRatio > valCom) {
                                valCom = traderPool.at(hh)->profitRatio;
                                bestTraderIndex = hh;
                            }
                        }
                        break;
                    case 2:
                        if (tmpFit < weightVectorSwarm->swarm.at(h)->personalBestFitness) {
                            weightVectorSwarm->swarm.at(h)->personalBestFitness = tmpFit;
                            weightVectorSwarm->swarm.at(h)->copyIntoPersonalBest(
                                    weightVectorSwarm->swarm.at(h)->parameters);
                        }
                        if (tmpFit < parameterSwarm->swarm.at(h)->personalBestFitness) {
                            parameterSwarm->swarm.at(h)->personalBestFitness = tmpFit;
                            parameterSwarm->swarm.at(h)->copyIntoPersonalBest(parameterSwarm->swarm.at(h)->parameters);
                        }
                        if (tmpFit < strategySwarm->swarm.at(h)->personalBestFitness) {
                            strategySwarm->swarm.at(h)->personalBestFitness = tmpFit;
                            strategySwarm->swarm.at(h)->copyIntoPersonalBest(strategySwarm->swarm.at(h)->parameters);
                        }
                        weightVectorSwarm->setBestParticleMin();
                        parameterSwarm->setBestParticleMin();
                        strategySwarm->setBestParticleMin();

                        valCom = traderPool.at(0)->loss;
                        for (int hh = 0; hh < traderPool.size(); hh++) {
                            if (traderPool.at(hh)->loss < valCom) {
                                valCom = traderPool.at(hh)->loss;
                                bestTraderIndex = hh;
                            }
                        }
                        break;

                    case 3:
                        if (tmpFit < weightVectorSwarm->swarm.at(h)->fitness) {
                            weightVectorSwarm->swarm.at(h)->personalBestFitness = tmpFit;
                            weightVectorSwarm->swarm.at(h)->copyIntoPersonalBest(
                                    weightVectorSwarm->swarm.at(h)->parameters);
                        }
                        if (tmpFit < parameterSwarm->swarm.at(h)->fitness) {
                            parameterSwarm->swarm.at(h)->personalBestFitness = tmpFit;
                            parameterSwarm->swarm.at(h)->copyIntoPersonalBest(parameterSwarm->swarm.at(h)->parameters);
                        }
                        if (tmpFit < strategySwarm->swarm.at(h)->fitness) {
                            strategySwarm->swarm.at(h)->personalBestFitness = tmpFit;
                            strategySwarm->swarm.at(h)->copyIntoPersonalBest(strategySwarm->swarm.at(h)->parameters);
                        }
                        weightVectorSwarm->setBestParticleMin();
                        parameterSwarm->setBestParticleMin();
                        strategySwarm->setBestParticleMin();

                        valCom = traderPool.at(0)->lossRatio;
                        for (int hh = 0; hh < traderPool.size(); hh++) {
                            if (traderPool.at(hh)->lossRatio < valCom) {
                                valCom = traderPool.at(hh)->lossRatio;
                                bestTraderIndex = hh;
                            }
                        }
                        break;
                }
            }
            //PSO Updates
            for (int k = 0; k < swarmSize; k++) {
                weightVectorSwarm->updatePSOSwarm(parameterSwarm->swarm);
                strategySwarm->updatePSOSwarm(parameterSwarm->swarm);
                parameterSwarm->updatePSOSwarm(parameterSwarm->swarm);
            }

        }

        ///Record Run Data
        switch (objChoice) {
            case 0:
                traderD.push_back(traderPool.at(bestTraderIndex)->profit);
                weightVectorD.push_back(weightVectorSwarm->swarm.at(weightVectorSwarm->indexOfBestParticle)->fitness);
                paramD.push_back(parameterSwarm->swarm.at(parameterSwarm->indexOfBestParticle)->fitness);
                strategyD.push_back(strategySwarm->swarm.at(strategySwarm->indexOfBestParticle)->fitness);
                break;
            case 1:
                traderD.push_back(traderPool.at(bestTraderIndex)->profitRatio);
                weightVectorD.push_back(weightVectorSwarm->swarm.at(weightVectorSwarm->indexOfBestParticle)->fitness);
                paramD.push_back(parameterSwarm->swarm.at(parameterSwarm->indexOfBestParticle)->fitness);
                strategyD.push_back(strategySwarm->swarm.at(strategySwarm->indexOfBestParticle)->fitness);
                break;
            case 2:
                traderD.push_back(traderPool.at(bestTraderIndex)->loss);
                weightVectorD.push_back(weightVectorSwarm->swarm.at(weightVectorSwarm->indexOfBestParticle)->fitness);
                paramD.push_back(parameterSwarm->swarm.at(parameterSwarm->indexOfBestParticle)->fitness);
                strategyD.push_back(strategySwarm->swarm.at(strategySwarm->indexOfBestParticle)->fitness);
                break;
            case 3:
                traderD.push_back(traderPool.at(bestTraderIndex)->lossRatio);
                weightVectorD.push_back(weightVectorSwarm->swarm.at(weightVectorSwarm->indexOfBestParticle)->fitness);
                weightVectorD.push_back(weightVectorSwarm->swarm.at(weightVectorSwarm->indexOfBestParticle)->fitness);
                paramD.push_back(parameterSwarm->swarm.at(parameterSwarm->indexOfBestParticle)->fitness);
                strategyD.push_back(strategySwarm->swarm.at(strategySwarm->indexOfBestParticle)->fitness);
                break;
        }


    }
    recordRunData(traderPool.at(0)->currencyUsedForBuying, traderPool.at(0)->currencyThatIsBought,
                  traderD, weightVectorD, paramD, strategyD, to_string(scope));
    traderD.clear();
    weightVectorD.clear();
    paramD.clear();
    strategyD.clear();
}

void
ExperimentFramework::recordRunData(string a, string b, vector<double> traderData, vector<double> weightVectorSwarmData,
                                   vector<double> parameterSwarmData,
                                   vector<double> strategySwarmData, string span) {
    /*
     * The recording strategy will record data based 3 things: time delay scope, number of iterations(trading periods)
     * and each run of x(generally 30)
     *
     *
     * The process of recording the run data is therefore to record for:
     *  1) each time delay scope
     *  2) number of iterations
     *  3) and each run( generally 30)
     *
     *  Record:
     *  1) the best performing trader
     *  2) the best performing weight vector swarm
     *  3) the best performing parameter swarm
     *  4) the best performing strategy swarm
     *
     *  optionally(consider whether to record the parameter positions themselves?)
     * */

    string filename = "FOREX_TRADING_DATA_" + a + "-" + b + "30_Runs_Scope_" + span + ".csv";

    ofstream myfile;

    myfile.open(filename);


    for (int i = 0; i < parameterSwarmData.size(); i++) {
        myfile << to_string(traderData.at(i)) << "," << to_string(weightVectorSwarmData.at(i)) << ","
               << to_string(parameterSwarmData.at(i))
               << "," << to_string(strategySwarmData.at(i)) << endl;
    }

    myfile.close();
}
