/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ParameterParticle.cpp
 * Author: Warmaster
 * 
 * Created on 07 July 2017, 3:12 PM
 */

#include "ParameterParticle.h"

ParameterParticle::ParameterParticle()
{
    
}

ParameterParticle::ParameterParticle(int s)
{
    parameters.resize(s);
}

void ParameterParticle::printSelf()
{
    cout<<"Parameter Particle Printing"<<endl;
    cout<<"============================================================="<<endl;
    for (int i=0;i<parameters.size();i++)
    {
        cout<<"Parameter "<<i<<": "<<to_string(parameters.at(i))<<endl;
    }
    cout<<"============================================================="<<endl;
}


void ParameterParticle::initialiseParticle()
{
    double lower_bound = 0;
    double upper_bound = 2;


    for (int i = 0; i < parameters.size(); i++) {

        if (i == 2 || i == 5 || i == 8) {
            lower_bound = 0.8;
            upper_bound = 1.2;

            std::random_device rd;
            std::mt19937 e2(rd());
            std::uniform_real_distribution<> dist(lower_bound, upper_bound);

            parameters.at(i) = dist(e2);
        }
        else {
            std::random_device rd;
            std::mt19937 e2(rd());
            std::uniform_real_distribution<> dist(lower_bound, upper_bound);

            parameters.at(i) = dist(e2);
        }
    }
}
