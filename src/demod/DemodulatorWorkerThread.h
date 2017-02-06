// Copyright (c) Charles J. Cliffe
// SPDX-License-Identifier: GPL-2.0+

#pragma once

#include <queue>
#include <vector>

#include "liquid/liquid.h"
#include "AudioThread.h"
#include "ThreadQueue.h"
#include "CubicSDRDefs.h"
#include "Modem.h"

class DemodulatorWorkerThreadResult {
public:
    enum DemodulatorThreadResultEnum {
        DEMOD_WORKER_THREAD_RESULT_NULL, DEMOD_WORKER_THREAD_RESULT_FILTERS
    };

    DemodulatorWorkerThreadResult() :
            cmd(DEMOD_WORKER_THREAD_RESULT_NULL), iqResampler(nullptr), iqResampleRatio(0), sampleRate(0), bandwidth(0), modemKit(nullptr), modemType("") {

    }

    DemodulatorWorkerThreadResult(DemodulatorThreadResultEnum cmd) :
            DemodulatorWorkerThreadResult() {
        this->cmd = cmd;
    }

    DemodulatorThreadResultEnum cmd;

    msresamp_crcf iqResampler;
    double iqResampleRatio;
    
    DemodulatorThread *demodThread;

    long long sampleRate;
    unsigned int bandwidth;
    Modem *modem;
    ModemKit *modemKit;
    std::string modemType;
    std::string modemName;
};

class DemodulatorWorkerThreadCommand {
public:
    enum DemodulatorThreadCommandEnum {
        DEMOD_WORKER_THREAD_CMD_NULL, DEMOD_WORKER_THREAD_CMD_BUILD_FILTERS, DEMOD_WORKER_THREAD_CMD_MAKE_DEMOD
    };

    DemodulatorWorkerThreadCommand() :
            cmd(DEMOD_WORKER_THREAD_CMD_NULL), frequency(0), sampleRate(0), bandwidth(0), audioSampleRate(0), demodType("") {

    }

    DemodulatorWorkerThreadCommand(DemodulatorThreadCommandEnum cmd) :
            cmd(cmd), frequency(0), sampleRate(0), bandwidth(0), audioSampleRate(0), demodType("") {

    }

    DemodulatorThreadCommandEnum cmd;

    long long frequency;
    long long sampleRate;
    unsigned int bandwidth;
    unsigned int audioSampleRate;
    std::string demodType;
    ModemSettings settings;
};

typedef ThreadQueue<DemodulatorWorkerThreadCommand> DemodulatorThreadWorkerCommandQueue;
typedef ThreadQueue<DemodulatorWorkerThreadResult> DemodulatorThreadWorkerResultQueue;

class DemodulatorWorkerThread : public IOThread {
public:

    DemodulatorWorkerThread();
    ~DemodulatorWorkerThread();

    virtual void run();

    void setCommandQueue(DemodulatorThreadWorkerCommandQueue *tQueue) {
        commandQueue = tQueue;
    }

    void setResultQueue(DemodulatorThreadWorkerResultQueue *tQueue) {
        resultQueue = tQueue;
    }

    virtual void terminate();

protected:

    DemodulatorThreadWorkerCommandQueue *commandQueue;
    DemodulatorThreadWorkerResultQueue *resultQueue;
    Modem *cModem;
    ModemKit *cModemKit;
    std::string cModemType;
    std::string cModemName;
};
