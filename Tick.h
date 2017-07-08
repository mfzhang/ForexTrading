/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Ticks.h
 * Author: Warmaster
 *
 * Created on 27 June 2017, 12:30 PM
 */
#include<string>

#ifndef TICK_H
#define TICK_H

using namespace std;

class Tick
{
private:
    string datetime;
    double bidQuote;
    double askQuote;
    int volume;
    
public:
   Tick();
   
   Tick(string date,double bid,double ask,int vol);
   void setDateTime(string a);
   void setBidQuote(double a);
   void setAskQuote(double a);
   void setVolume(int a);
   
   string getDateTime();
   double getBidQuote();
   double getAskQuote();
   double getVolume();
   
};

#endif /* TICK_H */

