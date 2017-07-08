/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Swarm.h
 * Author: Warmaster
 *
 * Created on 07 July 2017, 2:52 PM
 */
#include "Particle.h"
#ifndef SWARM_H
#define SWARM_H

class Swarm {
public:
    Swarm();
    vector<Particle *> swarm;
    int swarmSize;
    virtual void resetSwarm();
    virtual void initialiseSwarm();
    ~Swarm();

private:

};

#endif /* SWARM_H */

