//
//  Process.cpp
//  shed5
//
//  Created by Duffy Wan on 10/19/15.
//  Copyright (c) 2015 Duffy Wan. All rights reserved.
//

#include "Process.h"

Process::Process(int _AT, int _TC, int _CB, int _IO, int _PRIO)
{
    AT = _AT;
    TCLeft = _TC;
    CB = _CB;
    IO = _IO;
    S_PRIO = _PRIO;
    D_PRIO = S_PRIO - 1;
    
    TC = TCLeft;
    CBLeft = 0;
    FT = 0;
    TT = 0;
    IT = 0;
    CW = 0;
}

