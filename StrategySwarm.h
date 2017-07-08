/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StrategySwarm.h
 * Author: Warmaster
 *
 * Created on 07 July 2017, 3:07 PM
 */
#include "Swarm.h"
#ifndef STRATEGYSWARM_H
#define STRATEGYSWARM_H

class StrategySwarm: public Swarm {
public:
    StrategySwarm(int s);
    void initialiseSwarm() override;
    void resetSwarm() override;

private:

};

#endif /* STRATEGYSWARM_H */

