//
// Created by Warmaster on 2017/07/10.
//

#include "ExperimentFramework.h"

ExperimentFramework::ExperimentFramework()
{

}

ExperimentFramework::ExperimentFramework(int swarmSize,int numberOfTraders,int objectiveChoice,
                                         string buyingC,string boughtC,
                                         double initialTradingCapital,string OLHCfn,string tickfn)
{
    dataStore=new DataStore(7);
    weightVectorSwarm=new WeightVectorSwarm(swarmSize);
    parameterSwarm=new ParameterSwarm(swarmSize);
    strategySwarm=new StrategySwarm(swarmSize);


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

}

void ExperimentFramework::recordRunData() {

}
