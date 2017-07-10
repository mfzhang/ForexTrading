cmake_minimum_required(VERSION 3.6)
project(ForexTrading)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES DataStore.cpp  IndicatorManager.cpp main.cpp OHLC.cpp ParameterParticle.cpp ParameterSwarm.cpp
        Particle.cpp StrategyParticle.cpp StrategySwarm.cpp Swarm.cpp Tick.cpp WeightVectorParticle.cpp WeightVectorSwarm.cpp TradingAgent.cpp TradingAgent.h TransactionHistory.cpp TransactionHistory.h)
add_executable(ForexTrading ${SOURCE_FILES})