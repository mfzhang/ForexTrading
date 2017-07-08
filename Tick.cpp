/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Tick.h"

double Tick::getAskQuote() {
    return this->askQuote;
}

double Tick::getBidQuote() {
    return this->bidQuote;
}

string Tick::getDateTime() {
    return this->datetime;
}

double Tick::getVolume() {
    return this->volume;
}

void Tick::setAskQuote(double a) {
    this->askQuote=a;
}

void Tick::setBidQuote(double a) {
    this->bidQuote=a;
}

void Tick::setDateTime(string a) {
    this->datetime=a;
}

void Tick::setVolume(int a) {
    this->volume=a;

}

Tick::Tick() {

}

Tick::Tick(string date, double bid, double ask, int vol) {
    setAskQuote(ask);
    setBidQuote(bid);
    setDateTime(date);
    setVolume(vol);
}
