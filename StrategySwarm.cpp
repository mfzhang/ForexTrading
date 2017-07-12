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
        swarm.at(i)->copyIntoPersonalBest(swarm.at(i)->parameters);
        if (minimisationProblem == true) {
            swarm.at(i)->personalBestFitness = numeric_limits<double>::max();
        } else {
            swarm.at(i)->personalBestFitness = numeric_limits<double>::min();
        }
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

void StrategySwarm::updatePSOSwarm(vector<Particle *> swarmParams) {
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
            omega1=swarmParams.at(i)->parameters.at(3)*r1.at(j);
            omega2=swarmParams.at(i)->parameters.at(4)*r2.at(j);
            omega=omega1+omega2;

            X=2*(swarmParams.at(i)->parameters.at(5))/(2-(omega)-(sqrt(abs(omega*(omega-4)))));

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
