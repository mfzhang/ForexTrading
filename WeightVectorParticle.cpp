/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   WeightVectorParticle.cpp
 * Author: Warmaster
 * 
 * Created on 07 July 2017, 1:55 PM
 */

#include "WeightVectorParticle.h"

WeightVectorParticle::WeightVectorParticle(int s)
{
    numIndicators = s;
    parameters.resize(s);

    for(int i=0;i<numIndicators;i++)
    {
        parameters.at(i)=0.0;
    }
}

void WeightVectorParticle::initialiseParticle()
{
    double lower_bound = 0;
    double upper_bound = 10;
    
    std::random_device rd;
    std::mt19937 e2(rd());
    std::uniform_real_distribution<> dist(lower_bound, upper_bound);

    
    for (int i = 0; i < numIndicators; i++) {
       
        parameters.at(i) =dist(e2);
    }
}

void WeightVectorParticle::printSelf()
{
    cout<<"Weight Vector Particle"<<endl;
    cout<<"============================================================="<<endl;
    for (int i=0;i<parameters.size();i++)
    {
        cout<<"Parameter "<<i<<": "<<to_string(parameters.at(i))<<endl;
    }
    cout<<"============================================================="<<endl;
}
