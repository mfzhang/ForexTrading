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
        cout<<"Deleted particle"<<endl;
    }
}
