//
//  Simulator.h
//  shed5
//
//  Created by Duffy Wan on 10/19/15.
//  Copyright (c) 2015 Duffy Wan. All rights reserved.
//

#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <queue>
#include <deque>
#include <cstdlib>

#include "Process.h"
#include "Scheduler.h"
#include "Event.h"

using namespace::std;

class Simulator
{
public:
    int processTotalNum;
    int randTotalNum;
    int ofs;
    int lastTimeIdleCPU;
    int lastTimeIdleIO;
    int FT;
    double idleCT;
    double idleIO;
    double totalTT;
    double totalCW;
    double throughput;
    bool verbose;
    bool pickFlag;
    
    Scheduler * scheduler;
    
    vector<Process> processList;
    vector<int> randVals;
    
    deque<Event> readyQueue;
    deque<Event> expireQueue;
    priority_queue<Event> eventQueue;
    
    int myrandom(int burst);
    
    Simulator();
    
    void InitProcessList(string inputFileName);
    
    void InitRandValues(string randFileName);
    
    void InitScheduler(string schedulerType);
    
    void InitEventQueue();
    
    int GetMinEventNum(deque<Event> &readyQueue);
    
    void Run(string inputFileName, string randFileName, bool _verbose, string schedulerType);
    
    void ProcessEvent(Event event);
    
    void Print();
};

#endif