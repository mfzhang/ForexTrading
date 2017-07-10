//
// Created by Warmaster on 2017/07/10.
//

#ifndef EXPERIMENTFRAMEWORK_H
#define EXPERIMENTFRAMEWORK_H

#include "DataStore.h"
#include "WeightVectorSwarm.h"
#include "StrategySwarm.h"
#include "ParameterSwarm.h"
#include "TradingAgent.h"


#include <iostream>
#include <vector>
#include <string>

using namespace std;

class ExperimentFramework {

private:
    DataStore * dataStore;
    WeightVectorSwarm * weightVectorSwarm;
    StrategySwarm * strategySwarm;
    ParameterSwarm * parameterSwarm;
    vector<TradingAgent *> traderPool;
    int numberOfTradingPeriods;
    int objChoice;
    int swarmSize;

public:
    ExperimentFramework();
    ExperimentFramework(int swarmSize,int numberOfTraders,int objectiveChoice,string buyingC,string boughtC,
                        double initialTradingCapital,string OLHCfn,string tickfn,int numTradingPeriods);
    ~ExperimentFramework();

    void doExperiment();
    void recordRunData();
};


#endif //EXPERIMENTFRAMEWORK_H
