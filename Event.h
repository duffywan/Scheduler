//
//  Event.h
//  shed5
//
//  Created by Duffy Wan on 10/19/15.
//  Copyright (c) 2015 Duffy Wan. All rights reserved.
//

#ifndef EVENT_H
#define EVENT_H

#include <string>

using namespace::std;

class Event
{
public:
    static int maxEventNum;
    
    int startTime;
    int endTime;
    int eventNum;
    int pid;
    int status;
    int prevStatus;
    
    Event();
    Event(int _startTime, int _endTime, int _pid, int _prevStatus, int _status);
    
    bool operator<(const Event &right) const;
    string getStatus();
    string getPrevStatus();
};

#endif