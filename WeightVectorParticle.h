/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   WeightVectorParticle.h
 * Author: Warmaster
 *
 * Created on 07 July 2017, 1:55 PM
 */
#include "Particle.h"
#ifndef WEIGHTVECTORPARTICLE_H
#define WEIGHTVECTORPARTICLE_H

class WeightVectorParticle : public Particle
{
public:
    WeightVectorParticle(int s);
    void initialiseParticle() override;
    void printSelf() override;

private:
    int numIndicators;
};

#endif /* WEIGHTVECTORPARTICLE_H */

