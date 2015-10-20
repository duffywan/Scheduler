//
//  Event.cpp
//  shed5
//
//  Created by Duffy Wan on 10/19/15.
//  Copyright (c) 2015 Duffy Wan. All rights reserved.
//

#include "Event.h"

using namespace::std;

int Event::maxEventNum = 0;

Event::Event()
{
}

Event::Event(int _startTime, int _endTime, int _pid, int _prevStatus, int _status)
{
    startTime = _startTime;
    endTime = _endTime;
    eventNum = maxEventNum++;
    pid = _pid;
    prevStatus = _prevStatus;
    status = _status;
}

string Event::getStatus() {
    switch (status) {
        case -1:
            return "CREATED";
        case 0:
            return "READY";
        case 1:
            return "RUNNG";
        case 2:
            return "BLOCK";
    }
    return "";
}
string Event::getPrevStatus() {
    switch (prevStatus) {
        case -1:
            return "CREATED";
        case 0:
            return "READY";
        case 1:
            return "RUNNG";
        case 2:
            return "BLOCK";
    }
    return "";
}
bool Event::operator<(const Event &right) const
{
    if (endTime > right.endTime)
        return true;
    if (endTime == right.endTime)
        return eventNum > right.eventNum;
    return false;
}

