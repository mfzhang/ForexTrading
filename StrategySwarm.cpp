/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StrategySwarm.cpp
 * Author: Warmaster
 * 
 * Created on 07 July 2017, 3:07 PM
 */

#include "StrategySwarm.h"
#include "StrategyParticle.h"


StrategySwarm::StrategySwarm(int s)
{   
    swarmSize=s;
    
    swarm.resize(s);

    swarmType=1;

}

void StrategySwarm::initialiseSwarm()
{

    for (int i=0;i<swarmSize;i++)
    {
        swarm.at(i)=new StrategyParticle(2);
        swarm.at(i)->initialiseParticle();
    }
}

void StrategySwarm::resetSwarm()
{
    int s=swarm.at(0)->parameters.size();
    for(int i=0;i<swarm.size();i++)
    {
        swarm.at(i)->clearParameters();
    }
    for(int i=0;i<swarm.size();i++)
    {
        swarm.at(i)->parameters.resize(s);
    }
}
