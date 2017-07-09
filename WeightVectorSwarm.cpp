/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   WeightVectorSwarm.cpp
 * Author: Warmaster
 * 
 * Created on 07 July 2017, 3:07 PM
 */

#include "WeightVectorSwarm.h"
#include "WeightVectorParticle.h"

WeightVectorSwarm::WeightVectorSwarm(int s) {
    swarmSize=s;
    swarm.resize(s);
    swarmType=2;
}

void WeightVectorSwarm::initialiseSwarm()
{

    for (int i=0;i<swarmSize;i++)
    {
        swarm.at(i)=new WeightVectorParticle(7);
        swarm.at(i)->initialiseParticle();
    }
}

void WeightVectorSwarm::resetSwarm()
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
