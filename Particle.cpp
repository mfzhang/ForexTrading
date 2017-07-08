/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Particle.cpp
 * Author: Warmaster
 * 
 * Created on 07 July 2017, 1:55 PM
 */

#include "Particle.h"

Particle::Particle()
{

}

Particle::Particle(int s) {

    parameters.resize(s);
    fitness=0;
}

void Particle::clearParameters()
{
    parameters.clear();
}

void Particle::copyNewVectorIntoVector(vector<double> newVector)
{
    clearParameters();
    
    for(int i=0;i<newVector.size();i++)
    {
        parameters.at(i)=newVector.at(i);
    }
}

double Particle::getValueAtIndex(int index)
{
    return this->parameters.at(index);
}


void Particle::setValueAtIndex(double value, int index)
{
    this->parameters.at(index)=value;
}

double Particle::getFitness()
{
    return this->fitness;
}

void Particle::setFitness(double f)
{
    this->fitness=f;
}

void Particle::initialiseParticle()
{

}

void Particle::printSelf()
{   
    cout<<"============================================================="<<endl;
    for (int i=0;i<parameters.size();i++)
    {
        cout<<"Parameter "<<i<<": "<<to_string(parameters.at(i))<<endl;
    }
    cout<<"============================================================="<<endl;
}
