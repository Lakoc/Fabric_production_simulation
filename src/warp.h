//////////////////////////////////////////////////////////////////////////////////////
//  School:     Faculty of Information Technology, Brno University of Technology    //
//  Course:     IMS - Modelling and Simulation                                      //
//  Module:     warp.h                                                              //
//  Authors:    Alexander Polok (xpolok03), Michal Rozsíval (xrozsi06)              //
//  Date:       7.12.2020                                                           //
//////////////////////////////////////////////////////////////////////////////////////

#ifndef __WARP_H__
#define __WARP_H__
#include <tuple>

#include "simlib.h"
#include "factory.h"

class Warp : public Process {
    Factory *_factory;
    uint32_t _count;
    double _length = Factory::WARP::GetLength();
    uint32_t _threadCount = Factory::WARP::GetThread();

    // stats
    double _startTime;
    double _weavingStartTime;

    // flags
    bool _goNonWeavConnecting = false;
    bool _goGluing = false;
    bool _goWarpConnecting = false;
    bool _wasLoomed = false;

    void SetConnectingFlags();

    // processes
    void WindingProcess();

    void WarpingProcess();

    void GluingProcess();

    void RewindBenchConnectingProcess();

    void LoomingProcess();

    void WeavingProcess();

    std::tuple<Store *, Factory::WEAVING::Type> GetAvailableLine();

    void FinalCheckProcess();


public:
    Warp(Factory *factory, int count);

    ~Warp() override;

    void Behavior() override;

    double GetLength() const;

    uint32_t GetThreadCount() const;
};


#endif