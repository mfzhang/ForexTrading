/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "DataStore.h"

DataStore::~DataStore()
{
    delete indicators;
}

DataStore::DataStore()
{

}

DataStore::DataStore(int a)
{
    //Number of indicators
    indicators = new IndicatorManager(7);
}

std::string DataStore::getFileName()
{
    return this->fileName;
}

void DataStore::setFileName(std::string a)
{
    this->fileName = a;
}

void DataStore::addToOHLCVector(string a, double b, double c, double d, double e, int f)
{
    OHLC * tmp = new OHLC(a, b, c, d, e, f);
    ohlcVector.push_back(*tmp);
    delete tmp;
    //cout << "Queue Size" << ohlcVector.size() << endl;
}

void DataStore::addToPriceVector(string date, double bid, double ask, int vol)
{

    Tick * tmp = new Tick(date, bid, ask, vol);
    priceVector.push_back(*tmp);
    delete tmp;
    //cout << "Queue Size" << priceVector.size() << endl;
}

void DataStore::printListOfOHLC()
{
    int c = 0;
    while (c != ohlcVector.size()) {
        cout << ohlcVector.at(c).getDate() << "|" << to_string(ohlcVector.at(c).getOpen()) << "|" << to_string(ohlcVector.at(c).getHigh()) << "|" << to_string(ohlcVector.at(c).getLow()) << "|" << to_string(ohlcVector.at(c).getClose()) << "|" << to_string(ohlcVector.at(c).getVolume()) << endl;
        c++;
    }

}

void DataStore::printList()
{
    int c = 0;
    while (c != priceVector.size()) {
        cout << priceVector.at(c).getDateTime() << "|" << to_string(priceVector.at(c).getBidQuote()) << "|" << to_string(priceVector.at(c).getAskQuote()) << "|" << to_string(priceVector.at(c).getVolume()) << endl;

        c++;
    }

}

void DataStore::readInOLHCFromFile(string fn, int numberOfEntries, int startingIndex)
{

    if (ohlcVector.empty() == false) {
        ohlcVector.clear();
    }
    ifstream myfile;
    int lineCount = 0;

    myfile.open(fn);
    string sline;

    int count = 0;
    while (count < startingIndex - 1) {
        getline(myfile, sline);
        count++;
    }
    count = numberOfEntries;
    char *c;
    stringstream stream;
    string ss;

    while (count > 0) {
        getline(myfile, sline);

        string j = "";
        double k = 0.0, l = 0.0, m = 0.0, n = 0.0;
        int nn = 0;

        j = sline.substr(0, sline.find(";"));
        sline = sline.substr(sline.find(";") + 1);
        stream << fixed << setprecision(6) << sline.substr(0, sline.find(";") - 1);
        ss = stream.str();
        stream.str(string());
        k = atof(ss.c_str());

        sline = sline.substr(sline.find(";") + 1);

        stream << fixed << setprecision(6) << sline.substr(0, sline.find(";") - 1);
        ss = stream.str();
        stream.str(string());

        l = atof(ss.c_str());
        sline = sline.substr(sline.find(";") + 1);

        stream << fixed << setprecision(6) << sline.substr(0, sline.find(";") - 1);
        ss = stream.str();
        stream.str(string());

        m = atof(ss.c_str());

        sline = sline.substr(sline.find(";") + 1);

        stream << fixed << setprecision(6) << sline.substr(0, sline.find(";") - 1);
        ss = stream.str();
        stream.str(string());

        n = atof(ss.c_str());

        sline = sline.substr(sline.find(";") + 1);
        nn = stoi(sline);
        addToOHLCVector(j, k, l, m, n, nn);
        count--;

    }

    myfile.close();
    ///cout << "Done Loading OHLC" << endl;
}

void DataStore::readInTicksFromFile(string fn) {

    if (priceVector.empty() == false) {
        priceVector.clear();
    }
    ifstream myfile;
    int lineCount = 0;


    myfile.open(fn);
    string sline;

    char *c;
    stringstream stream;
    string ss;
    string tmpDate=ohlcVector.back().getDate();
    bool co=true;
    while (co==true) {
        getline(myfile, sline);


        string a;
        double b, g;
        int d;

        a = sline.substr(0, sline.find(","));
        sline = sline.substr(sline.find(",") + 1);

        stream << fixed << setprecision(6) << sline.substr(0, sline.find(",") - 1);
        ss = stream.str();
        stream.str(string());

        b = atof(ss.c_str());
        sline = sline.substr(sline.find(",") + 1);

        stream << fixed << setprecision(6) << sline.substr(0, sline.find(",") - 1);
        ss = stream.str();
        stream.str(string());

        g = atof(ss.c_str());
        sline = sline.substr(sline.find(",") + 1);
        d = stoi(sline);
        addToPriceVector(a, b, g, d);

        if (a>tmpDate)
        {
            co=false;
        }
    }

    string gg=priceVector.back().getDateTime();
    int s=priceVector.size();
    myfile.close();
    //cout << "Done Loading Ticks" << endl;
}

void DataStore::readInTicksFromFile(string fn, int numberOfTicks, int startingIndex)
{

    if (priceVector.empty() == false) {
        priceVector.clear();
    }
    ifstream myfile;
    int lineCount = 0;


    myfile.open(fn);
    string sline;
    /*
    while (myfile.eof() == false) {
        getline(myfile, sline);
        lineCount++;
    }
    myfile.close();

    myfile.open(fn);

    
    if ((lineCount - 1) - startingIndex < numberOfTicks) {
        numberOfTicks = (lineCount) - startingIndex;
    } else if (numberOfTicks == 0) {
        numberOfTicks = lineCount;
    } else if (startingIndex < 0) {
        startingIndex = 0;
    }
     */
    int count = 0;

    while (count < startingIndex - 1) {
        getline(myfile, sline);
        count++;
    }

    count = numberOfTicks;
    char *c;
    stringstream stream;
    string ss;

    while (count > 0) {
        getline(myfile, sline);

        string a;
        double b, g;
        int d;

        a = sline.substr(0, sline.find(","));
        sline = sline.substr(sline.find(",") + 1);

        stream << fixed << setprecision(6) << sline.substr(0, sline.find(",") - 1);
        ss = stream.str();
        stream.str(string());

        b = atof(ss.c_str());
        sline = sline.substr(sline.find(",") + 1);

        stream << fixed << setprecision(6) << sline.substr(0, sline.find(",") - 1);
        ss = stream.str();
        stream.str(string());

        g = atof(ss.c_str());
        sline = sline.substr(sline.find(",") + 1);
        d = stoi(sline);
        addToPriceVector(a, b, g, d);

        count--;

    }

    myfile.close();
    //cout << "Done Loading Ticks" << endl;
}

double DataStore::priceLookUpBuy(string date)
{
    int i = 0;
    while (i < priceVector.size() && priceVector.at(i).getDateTime().compare(date) <= 0) {
        i++;
    }
    return priceVector.at(i - 1).getAskQuote();
}

double DataStore::priceLookUpSell(string date)
{
    int i = 0;
    while (i < priceVector.size() && priceVector.at(i).getDateTime().compare(date) <= 0) {
        i++;
    }
    return priceVector.at(i - 1).getBidQuote();
}

double DataStore::determineIfBuy(vector<int> indicatorList, vector<double> weightVector)
{
    double val=0;
    vector<int> tmp=indicators->calculateBuyIndicatorVector(indicatorList);
    
    for (int i=0;i<tmp.size();i++)
    {
        val=val+(tmp.at(i)*weightVector.at(i));
    }
    
    return val;
}

double DataStore::determineIfSell(vector<int> indicatorList, vector<double> weightVector)
{  
    double val=0;
    vector<int> tmp=indicators->calculateSellIndicatorVector(indicatorList);
    
    for (int i=0;i<tmp.size();i++)
    {
        val=val+(tmp.at(i)*weightVector.at(i));
    }
    
    return val;
}

void DataStore::setFirstRunToFalse() {
    indicators->setFirstRunToFalse();
}

void DataStore::resetFirstRun() {
    indicators->setFirstRunToTrue();
}

void DataStore::refreshBuyIndicators()
{
    indicators->populateBuyIndicatorVariables(ohlcVector,priceVector);
}

void DataStore::refreshSellIndicators()
{
    indicators->populateSellIndicatorVariables(ohlcVector,priceVector);
}

double DataStore::latestPriceBuy() {
    return this->priceVector.back().getAskQuote();
}

double DataStore::latestPriceSell() {
    return this->priceVector.back().getBidQuote();
}

int DataStore::computeProximityIndex() {

    string tmpD=ohlcVector.back().getDate();
    int i = 0;
    while (i < priceVector.size() && priceVector.at(i).getDateTime()<tmpD) {
        i++;
    }
    return (i-1);

    return 0;
}

string DataStore::latestDateOLHC() {
    return ohlcVector.back().getDate();
}

string DataStore::getOLHCfn() {
    return this->OLHCfn;
}

string DataStore::getTickfn() {
    return this->tickfn;
}

void DataStore::setOLHCfn(string a) {
    this->OLHCfn=a;
}

void DataStore::setTickfn(string a) {
    this->tickfn=a;
}
