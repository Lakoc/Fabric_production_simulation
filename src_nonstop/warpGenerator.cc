//////////////////////////////////////////////////////////////////////////////////////
//  School:     Faculty of Information Technology, Brno University of Technology    //
//  Course:     IMS - Modelling and Simulation                                      //
//  Module:     warpGenerator.cc                                                    //
//  Authors:    Alexander Polok (xpolok03), Michal Rozsíval (xrozsi06)              //
//  Date:       7.12.2020                                                           //
//////////////////////////////////////////////////////////////////////////////////////

#include "../src/warpGenerator.h"
#include "../src/warp.h"
#include "../src/stats.h"

WarpGenerator::WarpGenerator(Factory *factory)
        : _factory(factory) {
    Print("CREATING WARP GENERATOR\n");
}

void WarpGenerator::Behavior() {
    Warp *warp = new Warp(_factory, _generated++);
    warp->Activate();
    Stats::addWarpLength(warp->GetLength());
    Stats::addWarpThreadCount(warp->GetThreadCount());

    // Actualize stats
    double nextWarpTime = Factory::WARP_GENERATING::GetPeriod();
    Stats::addWarpPeriod(nextWarpTime / MINUTE);
    _dailyCount += 1;

    // Activate it self after period of time
    Activate(Time + nextWarpTime);
}
