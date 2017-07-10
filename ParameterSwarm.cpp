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
    swarmType=0;
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
    }
}

void ParameterSwarm::updatePSOSwarm(vector<Particle *> swarmParams) {
    double X=0.0;
    double omega1=0.0,omega2=0.0,omega=0.0;
    vector<double> r1;
    vector<double> r2;
    double tmpParameter=0.0;

    if (minimisationProblem==true)
    {
        setBestParticleMin();
    }else
    {
        setBestParticleMax();
    }

    std::random_device rd;
    std::mt19937 e2(rd());
    std::uniform_real_distribution<> dist(0, 1);

    r1.resize(swarm.at(0)->parameters.size());
    r2.resize(swarm.at(0)->parameters.size());

    for(int i=0;i<swarmSize;i++)
    {
        for(int v=0;v<r1.size();v++)
        {
            r1.at(v)=dist(e2);
            r2.at(v)=dist(e2);
        }

        for(int j=0;j<swarm.at(0)->parameters.size();j++)
        {
            ////Update Velocity
            omega1=swarmParams.at(i)->parameters.at(6)*r1.at(j);
            omega2=swarmParams.at(i)->parameters.at(7)*r2.at(j);
            omega=omega1+omega2;

            X=2*(swarmParams.at(i)->parameters.at(8)/(2-(omega)-(sqrt(abs(omega*(omega-4))))));

            swarm.at(i)->velocity.at(j)=X*(swarm.at(i)->velocity.at(j)+
                                           omega1*(swarm.at(i)->personalBest.at(j)-swarm.at(i)->parameters.at(j))+
                                           omega2*(getGlobalBestAtIndex(j)-swarm.at(i)->parameters.at(j)));
        }
        ////Update Positions
        for(int j=0;j<swarm.at(0)->parameters.size();j++)
        {
            ////Update Velocity
            tmpParameter=swarm.at(i)->parameters.at(j)+swarm.at(i)->velocity.at(j);
            if (checkIfInRange(tmpParameter,swarmType)==true)
            {
                swarm.at(i)->parameters.at(j)=tmpParameter;
            }

        }
    }
}
