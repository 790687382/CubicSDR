// Copyright (c) Charles J. Cliffe
// SPDX-License-Identifier: GPL-2.0+

#pragma once
#include "ModemAnalog.h"

class ModemLSB : public ModemAnalog {
public:
    ModemLSB();
    ~ModemLSB();
    
    std::string getName();
    
    static ModemBase *factory();
    
    int checkSampleRate(long long sampleRate, int audioSampleRate);
    int getDefaultSampleRate();

    void demodulate(ModemKit *kit, ModemIQData *input, AudioThreadInput *audioOut);
    
private:
#ifdef WIN32
	firfilt_crcf ssbFilt;
#else
	iirfilt_crcf ssbFilt;
#endif
    firhilbf c2rFilt;
    nco_crcf ssbShift;
    //    firfilt_crcf ssbFilt;
    //    ampmodem demodAM_LSB;
};