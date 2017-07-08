/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ParameterSwarm.cpp
 * Author: Warmaster
 * 
 * Created on 07 July 2017, 3:12 PM
 */

#include "ParameterSwarm.h"
#include "ParameterParticle.h"

ParameterSwarm::ParameterSwarm(int s) {
    swarmSize=s;
    
    swarm.resize(s);
    
}

void ParameterSwarm::resetSwarm() {
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

void ParameterSwarm::initialiseSwarm() {

    for (int i=0;i<swarmSize;i++)
    {
        swarm.at(i)=new ParameterParticle(9);
        swarm.at(i)->initialiseParticle();
        swarm.at(i)->printSelf();
    }
}
