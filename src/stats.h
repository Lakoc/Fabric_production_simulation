//////////////////////////////////////////////////////////////////////////////////////
//  School:     Faculty of Information Technology, Brno University of Technology    //
//  Course:     IMS - Modelling and Simulation                                      //
//  Module:     stats.h                                                             //
//  Authors:    Alexander Polok (xpolok03), Michal Rozsíval (xrozsi06)              //
//  Date:       7.12.2020                                                           //
//////////////////////////////////////////////////////////////////////////////////////

#ifndef __STATS_H__
#define __STATS_H__

#include "simlib.h"
#include "factory.h"

class Stats {
    static Histogram *_warpLength;
    static Histogram *_warpThreadCount;
    static Histogram *_warpPeriod;
    static Histogram *_warpCount;
    static Histogram *_windingProbability;
    static Histogram *_windingTime;
    static Histogram *_warpingLine;
    static Histogram *_warpingConnectingProbability;
    static Histogram *_warpingConnectingLine;
    static Histogram *_warpingConnectingThreads;
    static Histogram *_gluingProbability;
    static Histogram *_gluingTime;
    static Histogram *_rewindConnectingProbability;
    static Histogram *_rewindConnectingThreads;
    static Histogram *_loomingProbability;
    static Histogram *_loomingTime;
    static Histogram *_weavingLine;
    static Histogram *_weavingLength;
    static Histogram *_weavingControlTime;
    static Histogram *_weavingConnectingThreads;
    static Histogram *_stowingTime;
    static Histogram *_controlTime;
    static Histogram *_saleProbability;
    static Histogram *_weavingConnectingTime;
    static Histogram *_processLifeTime;
    static Histogram *_weavingTime;

public:
    static void Clear();

    static void Init();

    static void addWarpLength(double value);

    static void addWarpThreadCount(double value);

    static void addWarpPeriod(double value);

    static void addWarpCount(double value);

    static void addWindingProbability(double value);

    static void addWindingTime(double value);

    static void addWarpingLine(double value);

    static void addWarpingConnectingProbability(double value);

    static void addWarpingConnectingLine(double value);

    static void addWarpingConnectingThreads(double value);

    static void addGluingProbability(double value);

    static void addGluingTime(double value);

    static void addRewindConnectingProbability(double value);

    static void addRewindConnectingThreads(double value);

    static void addLoomingProbability(double value);

    static void addLoomingTime(double value);

    static void addWeavingLine(double value);

    static void addWeavingLength(double value);

    static void addWeavingControlTime(double value);

    static void addWeavingConnectingThreads(double value);

    static void addWeavingConnectingTime(double value);

    static void addStowingTime(double value);

    static void addControlTime(double value);

    static void addSaleProbability(double value);

    static void addProcessLifeTime(double value);

    static void addWeavingTime(double value);

    static void generateOutput(Factory *factory);
};

#endif
