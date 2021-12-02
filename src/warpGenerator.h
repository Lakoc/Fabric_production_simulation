//////////////////////////////////////////////////////////////////////////////////////
//  School:     Faculty of Information Technology, Brno University of Technology    //
//  Course:     IMS - Modelling and Simulation                                      //
//  Module:     warpGenerator.h                                                     //
//  Authors:    Alexander Polok (xpolok03), Michal Rozsíval (xrozsi06)              //
//  Date:       7.12.2020                                                           //
//////////////////////////////////////////////////////////////////////////////////////

#ifndef __WARP_GENERATOR_H__
#define __WARP_GENERATOR_H__

#include "simlib.h"
#include "factory.h"

class WarpGenerator : public Event {
    int _generated = 0;
    Factory *_factory;
    unsigned _dailyCount = 0;

public:
    WarpGenerator(Factory *factory);

    void Behavior();
};


#endif