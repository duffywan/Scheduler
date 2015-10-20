//
//  Simulator.cpp
//  shed5
//
//  Created by Duffy Wan on 10/19/15.
//  Copyright (c) 2015 Duffy Wan. All rights reserved.
//

#include "Simulator.h"

using namespace::std;

Simulator::Simulator()
{
    processTotalNum = 0;
    randTotalNum = 0;
    ofs = 0;
    lastTimeIdleCPU = 0;
    lastTimeIdleIO = 0;
    FT = 0;
    idleCT = 0;
    idleIO = 0;
    totalTT = 0;
    totalCW = 0;
    throughput = 0;
    verbose = false;
    pickFlag = true;
}

int Simulator::myrandom(int burst)
{
    if (ofs == randTotalNum)
        ofs = 0;
    return 1 + randVals[ofs++] % burst;
}

void Simulator::InitProcessList(string inputFileName)
{
    ifstream readFile;
    int AT, TC, CB, IO;
    
    readFile.open(inputFileName.c_str());
    while (readFile >> AT >> TC >> CB >> IO)
    {
        // assign dynamic priority
        int priority = myrandom(4);
        ++processTotalNum;
        processList.push_back(*new Process(AT, TC, CB, IO, priority));
    }
    readFile.close();
}

void Simulator::InitRandValues(string randFileName)
{
    ifstream readFile;
    int rand;
    
    readFile.open(randFileName.c_str());
    readFile >> randTotalNum;
    while (readFile >> rand)
        randVals.push_back(rand);
}

void Simulator::InitScheduler(string schedulerType)
{
    if (schedulerType == "F")
        scheduler = new FCFS();
    if (schedulerType == "L")
        scheduler = new LCFS();
    if (schedulerType == "S")
        scheduler = new SJF();
    if (schedulerType[0] == 'R')
    {
        string qString = schedulerType.substr(1, schedulerType.length() - 1);
        int quantum = 0;
        for (int i = 0; i < qString.length(); ++i)
            quantum = quantum * 10 + qString[i] - '0';
        scheduler = new RR(quantum);
    }
    if (schedulerType[1] == 'P')
    {
        string qString = schedulerType.substr(1, schedulerType.length() - 1);
        int quantum = 0;
        for (int i = 0; i < qString.length(); ++i)
            quantum = quantum * 10 + qString[i] - '0';
        scheduler = new PRIO(quantum);
    }
}

void Simulator::InitEventQueue()
{
    for (int i = 0; i < processTotalNum; ++i)
        eventQueue.push(*new Event(processList[i].AT, processList[i].AT, i, -1, 0));
}

void Simulator::Run(string inputFileName, string randFileName, bool _verbose, string schedulerType)
{
    verbose = _verbose;
    InitRandValues(randFileName);
    InitProcessList(inputFileName);
    InitScheduler(schedulerType);
    InitEventQueue();
    
    while (true)
    {
        if (pickFlag && !readyQueue.empty())
            if (eventQueue.empty() || eventQueue.top() < scheduler->PickFirst(readyQueue, processList))
            {
                Event event = scheduler->Pick(readyQueue, processList);
                if (event.endTime > lastTimeIdleCPU)
                {
                    idleCT += event.endTime - lastTimeIdleCPU;
                    lastTimeIdleCPU = event.endTime;
                }
                pickFlag = false;
                eventQueue.push(*new Event(event.endTime, lastTimeIdleCPU, event.pid, 0, 1));
            }
        if (!eventQueue.empty())
        {
            Event todo =eventQueue.top();
            eventQueue.pop();
            ProcessEvent(todo);
        }
        else
            break;
    }
}
// update idle CT and idle IO for every event processed.
void Simulator::ProcessEvent(Event event){
    
    Process& p = processList[event.pid];
    
    if (event.status == 0) {
        if (event.prevStatus == 1) {
            // if cpu is not runing other processes, we can pick one from ready queue
            pickFlag = true;
            // update process total time, cpu burst left, simulator cpu last idle time
            p.TC -= event.endTime - event.startTime;
            p.CBLeft -= event.endTime - event.startTime;
            lastTimeIdleCPU = max(lastTimeIdleCPU, event.endTime);
            readyQueue.push_back(*new Event(event.endTime, event.endTime, event.pid, 1, 0));
            printf("%4d p=%1d duration=%1d: %s -> %s cb=%1d rem=%1d prio=%1d \n", event.endTime, event.pid, event.endTime - event.startTime, event.getPrevStatus().c_str(), event.getStatus().c_str(), p.CBLeft, p.TC, p.D_PRIO);
        } else if (event.prevStatus == 2) {
            // update process io time, simulator last io time, simulator total io time
            p.IT += event.endTime - event.startTime;
            lastTimeIdleIO = max(lastTimeIdleIO, event.endTime);
            readyQueue.push_back(*new Event(event.endTime, event.endTime, event.pid, 2, 0));
            printf("%4d p=%1d duration=%1d: %s -> %s\n", event.endTime, event.pid, event.endTime - event.startTime, event.getPrevStatus().c_str(), event.getStatus().c_str());
        } else {
            readyQueue.push_back(*new Event(event.endTime, event.endTime, event.pid, -1, 0));
            printf("%4d p=%1d duration=%1d: %s -> %s\n", event.endTime, event.pid, event.endTime - event.startTime, event.getPrevStatus().c_str(), event.getStatus().c_str());
        }
    }
    if (event.status == 1) {
        p.CW += event.endTime - event.startTime;
        if (p.CBLeft == 0) {
            p.CBLeft = myrandom(p.CB);
            if (p.CBLeft > p.TC) {
                p.CBLeft = p.TC;
            }
        }
        if (scheduler->quantum == 0 || p.CBLeft <= scheduler->quantum) {
            // non RR or PRIO, or RR & PRIO but quantum not expire, trans to block state
            eventQueue.push(*new Event(event.endTime, event.endTime + p.CBLeft, event.pid, 1, 2));
        } else {
            // RR or PRIO, quantum expres but cpu burst not finish, move to ready state
            eventQueue.push(*new Event(event.endTime, event.endTime + scheduler->quantum, event.pid, 1, 0));
        }
        printf("%4d p=%1d duration=%1d: %s -> %s cb=%1d rem=%1d prio=%1d \n", event.endTime, event.pid, event.endTime - event.startTime, event.getPrevStatus().c_str(), event.getStatus().c_str(), p.CBLeft, p.TC, p.D_PRIO);
    }
    if (event.status == 2) {
        // if cpu is not runing other processes, we can pick one from ready queue
        pickFlag = true;
        p.TC -= event.endTime - event.startTime;
        p.CBLeft -= event.endTime - event.startTime; // should be 0
        //pickFlag = true;
        lastTimeIdleCPU = max(lastTimeIdleCPU, event.endTime);
        if (p.TC == 0) {
            p.FT = event.endTime;
            p.TT = p.FT - p.AT;
            return;
        }
        int newIO = myrandom(p.IO);
        eventQueue.push(*new Event(event.endTime, event.endTime + newIO, event.pid, 2, 0));
        
        if (lastTimeIdleIO < event.endTime)
            idleIO += event.endTime - lastTimeIdleIO;
        if (lastTimeIdleIO < event.endTime + newIO)
            lastTimeIdleIO = event.endTime + newIO;
        printf("%4d p=%1d duration=%1d: %s -> %s ib=%d rem=%d\n", event.endTime, event.pid, event.endTime - event.startTime, event.getPrevStatus().c_str(), event.getStatus().c_str(), newIO, p.TC);
    }
}


void Simulator::Print() {
    if (scheduler->quantum == 0)
        printf("%s\n", scheduler->type.c_str());
    else
        printf("%s %d\n", scheduler->type.c_str(), scheduler->quantum);
    for (int i = 0; i < processTotalNum; ++i)
    {
        Process& p = processList[i];
        printf("%04d: %4d %4d %4d %4d %1d | %5d %5d %5d %5d\n", i, p.AT, p.oldTC, p.CB, p.IO, p.S_PRIO, p.FT, p.TT, p.IT, p.CW);
        if (p.FT > FT)
            FT = p.FT;
        totalTT += p.TT;
        totalCW += p.CW;
    }
    idleIO += FT - lastTimeIdleIO;
    printf("SUM: %d %.2lf %.2lf %.2lf %.2lf %.3lf\n", FT, (FT - idleCT) * 100 / FT, (FT - idleIO) * 100 / FT, totalTT / processTotalNum, totalCW / processTotalNum, 100.0 * processTotalNum / FT);
}