/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Swarm.cpp
 * Author: Warmaster
 * 
 * Created on 07 July 2017, 2:52 PM
 */

#include "Swarm.h"

Swarm::Swarm() {
}

void Swarm::initialiseSwarm()
{
 
}

void Swarm::resetSwarm()
{
    swarm.clear();
}

Swarm::~Swarm()
{
    for(int i=0;i<swarmSize;i++)
    {
        delete swarm.at(i);
        cout<<"Deleted particle: "<<i<<endl;
    }
}

void Swarm::printParticles() {
    cout<<"################################################"<<endl;
    for(int i=0;i<swarm.size();i++)
    {
        swarm.at(i)->printSelf();
    }
    cout<<"################################################"<<endl;
}

void Swarm::updatePSOSwarm(double c1, double c2, double w) {

}
