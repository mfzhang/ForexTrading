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
#include <limits>
#ifndef SWARM_H
#define SWARM_H
using namespace std;
class Swarm {
public:
    bool minimisationProblem;

    Swarm();
    vector<Particle *> swarm;
    int swarmSize;
    int indexOfBestParticle;
    int swarmType;

    virtual void resetSwarm();
    virtual void initialiseSwarm();
    ~Swarm();
    void printParticles();
    void setProblemType(bool status);
    void updatePSOSwarm(double c1,double c2,double w);

    void setBestParticleMin();
    void setBestParticleMax();

    double getGlobalBestAtIndex(int index);
    bool checkIfInRange(double value,int type);
private:

};

#endif /* SWARM_H */

