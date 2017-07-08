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
    
    
    for (int i=0;i<swarmSize;i++)
    {
        cout<<"Particle "<<i<<endl;
        swarm.push_back(new WeightVectorParticle(7));
        swarm.at(i)->initialiseParticle();
        swarm.at(i)->printSelf();
        
    }
}

void WeightVectorSwarm::initialiseSwarm()
{
    
}

void WeightVectorSwarm::resetSwarm()
{

}
