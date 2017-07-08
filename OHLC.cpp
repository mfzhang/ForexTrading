/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   OHLC.cpp
 * Author: Warmaster
 * 
 * Created on 28 June 2017, 3:13 PM
 */

#include "OHLC.h"

OHLC::OHLC() {
}

OHLC::OHLC(string a, double b, double c, double d, double e, int f) {
    setDate(a);
    setOpen(b);
    setHigh(c);
    setLow(d);
    setClose(e);
    setVolume(f);
}

void OHLC::setVolume(int a) {
    this->volume=a;
}

void OHLC::setOpen(double a) {
    this->open=a;
}

void OHLC::setLow(double a) {
    this->low=a;
}

void OHLC::setHigh(double a) {
    this->high=a;
}

void OHLC::setDate(string a) {
    this->datetime=a;
}

void OHLC::setClose(double a) {
    this->close=a;
}

int OHLC::getVolume() {
    return this->volume;
}

double OHLC::getOpen() {
    return this->open;
}

double OHLC::getLow() {
    return this->low;
}

double OHLC::getHigh() {
    return this->high;
}

string OHLC::getDate() {
    return this->datetime;
}

double OHLC::getClose() {
    return this->close;
}
