//
//  Process.h
//  shed5
//
//  Created by Duffy Wan on 10/19/15.
//  Copyright (c) 2015 Duffy Wan. All rights reserved.
//

#ifndef PROCESS_H
#define PROCESS_H

class Process
{
public:
    int AT;
    int TCLeft;
    int CB;
    int IO;
    int S_PRIO;
    int D_PRIO;
    
    int TC;
    int CBLeft;
    int FT;
    int TT;
    int IT;
    int CW;
    
    Process(int _AT, int _TC, int _CB, int _IO, int _PRIO);
};

#endif