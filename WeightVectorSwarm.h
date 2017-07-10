/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   WeightVectorSwarm.h
 * Author: Warmaster
 *
 * Created on 07 July 2017, 3:07 PM
 */
#include "Swarm.h"
#ifndef WEIGHTVECTORSWARM_H
#define WEIGHTVECTORSWARM_H

class WeightVectorSwarm:public Swarm {
public:
    WeightVectorSwarm(int s);
    void resetSwarm() override;
    void initialiseSwarm() override;

    void updatePSOSwarm(vector<Particle *> swarmParams) override;

private:

};

#endif /* WEIGHTVECTORSWARM_H */

