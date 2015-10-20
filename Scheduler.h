//
//  Scheduler.h
//  shed5
//
//  Created by Duffy Wan on 10/19/15.
//  Copyright (c) 2015 Duffy Wan. All rights reserved.
//

#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <string>
#include <deque>
#include <vector>

#include "Event.h"
#include "Process.h"

using namespace::std;

class Scheduler
{
public:
    string type;
    int quantum;
    
    Scheduler();
    
    virtual Event Pick(deque<Event>& readydeque, vector<Process>& processList);
    
    Event PickFirst(deque<Event> &readyQueue, vector<Process>& processList);
};

class FCFS : public Scheduler
{
public:
    FCFS();
    
    Event Pick(deque<Event>& readydeque, vector<Process>& processList);
};

class LCFS : public Scheduler
{
public:
    LCFS();
    
    Event Pick(deque<Event>& readydeque, vector<Process>& processList);
};

class SJF : public Scheduler
{
public:
    SJF();
    
    Event Pick(deque<Event>& readydeque, vector<Process>& processList);
};

class RR : public Scheduler
{
public:
    RR(int _quantum);
    
    Event Pick(deque<Event>& readydeque, vector<Process>& processList);
};
class PRIO : public Scheduler
{
public:
    PRIO(int _quantum);
    
    Event Pick(deque<Event>& readydeque, vector<Process>& processList);
};
#endif