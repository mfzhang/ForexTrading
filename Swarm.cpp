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

void Swarm::updatePSOSwarm(vector<Particle *> swarm) {
}

void Swarm::updatePSOSwarm(double c1, double c2, double k) {
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
            omega1=c1*r1.at(j);
            omega2=c2*r2.at(j);
            omega=omega1+omega2;

            X=2*(k)/(2-(omega)-(sqrt(abs(omega*(omega-4)))));

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



void Swarm::setProblemType(bool status) {
    this->minimisationProblem=status;
}

void Swarm::setBestParticleMin() {
    double min=numeric_limits<double>::max();

    for(int i=0;i<swarm.size();i++)
    {
        if (swarm.at(i)->getFitness()<min)
        {
            min=swarm.at(i)->getFitness();
            indexOfBestParticle=i;
        }
    }
}

void Swarm::setBestParticleMax() {
    double max=numeric_limits<double>::min();

    for(int i=0;i<swarm.size();i++)
    {
        if (swarm.at(i)->getFitness()>max)
        {
            max=swarm.at(i)->getFitness();
            indexOfBestParticle=i;
        }
    }
}

double Swarm::getGlobalBestAtIndex(int index) {
    return swarm.at(indexOfBestParticle)->parameters.at(index);
}

bool Swarm::checkIfInRange(double value, int type) {

    bool result=true;
    switch(type)
    {
        ///Parameter Swarm
        case 0: if (value<0 || value>2) result=false;
            break;
        ///Strategy Swarm
        case 1:if (value<0 || value>1) result=false;
            break;
        ///Weight Vector Swarm
        case 2:if (value<0 || value>10) result=false;
            break;
    }
    return result;
}
