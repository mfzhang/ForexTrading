/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   OHLC.h
 * Author: Warmaster
 *
 * Created on 28 June 2017, 3:13 PM
 */
#include<string>

#ifndef OHLC_H
#define OHLC_H

using namespace std;

class OHLC
{
public:
    OHLC();
    OHLC(string a, double b, double c, double d, double e, int f);


    void setDate(string a);
    void setOpen(double a);
    void setHigh(double a);
    void setLow(double a);
    void setClose(double a);
    void setVolume(int a);

    string getDate();
    double getOpen();
    double getHigh();
    double getLow();
    double getClose();
    int getVolume();
private:
    string datetime;
    double open;
    double close;
    double high;
    double low;
    int volume;

};

#endif /* OHLC_H */

