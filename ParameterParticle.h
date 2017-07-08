/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ParameterParticle.h
 * Author: Warmaster
 *
 * Created on 07 July 2017, 3:12 PM
 */
#include "Particle.h"
#ifndef PARAMETERPARTICLE_H
#define PARAMETERPARTICLE_H

class ParameterParticle:public Particle{
public:
    ParameterParticle();
    ParameterParticle(int s);
    void printSelf() override;

    void initialiseParticle() override;
private:
    
};

#endif /* PARAMETERPARTICLE_H */

