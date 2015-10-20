//
//  Scheduler.cpp
//  shed5
//
//  Created by Duffy Wan on 10/19/15.
//  Copyright (c) 2015 Duffy Wan. All rights reserved.
//

#include "Scheduler.h"

using namespace::std;

Scheduler::Scheduler()
{
    quantum = 0;
}

Event Scheduler::Pick(deque<Event>& readydeque, vector<Process>& processList)
{
    return * new Event();
}

Event Scheduler::PickFirst(deque<Event> &readyQueue, vector<Process>& processList)
{
    deque<Event>::iterator itPick = readyQueue.begin();
    
    for (deque<Event>::iterator it = readyQueue.begin(); it != readyQueue.end(); ++it)
        if (it->endTime < itPick->endTime || (it->endTime == itPick->endTime && it->eventNum < itPick->eventNum))
            itPick = it;
    
    return *itPick;
}

FCFS::FCFS()
{
    type = "FCFS";
}

Event FCFS::Pick(deque<Event> &readyQueue, vector<Process>& processList)
{
    deque<Event>::iterator itPick = readyQueue.begin();
    
    for (deque<Event>::iterator it = readyQueue.begin(); it != readyQueue.end(); ++it)
        if (it->endTime < itPick->endTime || (it->endTime == itPick->endTime && it->eventNum < itPick->eventNum))
            itPick = it;
    Event ret = *itPick;
    readyQueue.erase(itPick);
    
    return ret;
}

LCFS::LCFS()
{
    type = "LCFS";
}

Event LCFS::Pick(deque<Event> &readyQueue, vector<Process>& processList)
{
    deque<Event>::iterator itPick = readyQueue.begin();
    
    for (deque<Event>::iterator it = readyQueue.begin(); it != readyQueue.end(); ++it)
        if (it->endTime > itPick->endTime || (it->endTime == itPick->endTime && it->eventNum > itPick->eventNum))
            itPick = it;
    Event ret = *itPick;
    readyQueue.erase(itPick);
    
    return ret;
}

SJF::SJF()
{
    type = "SJF";
}

Event SJF::Pick(deque<Event> &readyQueue, vector<Process>& processList)
{
    deque<Event>::iterator itPick = readyQueue.begin();
    
    for (deque<Event>::iterator it = readyQueue.begin(); it != readyQueue.end(); ++it)
        if (processList[it->pid].TC < processList[itPick->pid].TC)
            itPick = it;
        else
            if (processList[it->pid].TC == processList[itPick->pid].TC)
                if (it->endTime < itPick->endTime || (it->endTime == itPick->endTime && it->eventNum < itPick->eventNum))
                    itPick = it;
    Event ret = *itPick;
    readyQueue.erase(itPick);
    
    return ret;
}

RR::RR(int _quantum)
{
    type = "RR";
    quantum = _quantum;
}

Event RR::Pick(deque<Event> &readyQueue, vector<Process>& processList)
{
    deque<Event>::iterator itPick = readyQueue.begin();
    
    for (deque<Event>::iterator it = readyQueue.begin(); it != readyQueue.end(); ++it)
        if (it->endTime < itPick->endTime || (it->endTime == itPick->endTime && it->eventNum < itPick->eventNum))
            itPick = it;
    Event ret = *itPick;
    readyQueue.erase(itPick);
    
    return ret;
}
PRIO::PRIO(int _quantum)
{
    type = "PRIO";
    quantum = _quantum;
}

Event PRIO::Pick(deque<Event> &readyQueue, vector<Process>& processList)
{
    deque<Event>::iterator itPick = readyQueue.begin();
    // todo
    for (deque<Event>::iterator it = readyQueue.begin(); it != readyQueue.end(); ++it) {
        Process p = processList[it->pid];
        Process pPick = processList[itPick->pid];
        if (p.D_PRIO > pPick.D_PRIO || (p.D_PRIO == pPick.D_PRIO && it->eventNum < itPick->eventNum))
            itPick = it;
    }
    Event ret = *itPick;
    readyQueue.erase(itPick);
    
    return ret;
}





