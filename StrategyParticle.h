/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StrategyParticle.h
 * Author: Warmaster
 *
 * Created on 07 July 2017, 1:56 PM
 */
#include "Particle.h"
#ifndef STRATEGYPARTICLE_H
#define STRATEGYPARTICLE_H

class StrategyParticle: public Particle{
public:
    StrategyParticle(int s);
    void initialiseParticle() override;
    void printSelf() override;

private:
};

#endif /* STRATEGYPARTICLE_H */

