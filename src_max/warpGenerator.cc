//////////////////////////////////////////////////////////////////////////////////////
//  School:     Faculty of Information Technology, Brno University of Technology    //
//  Course:     IMS - Modelling and Simulation                                      //
//  Module:     warpGenerator.cc                                                    //
//  Authors:    Alexander Polok (xpolok03), Michal Rozsíval (xrozsi06)              //
//  Date:       7.12.2020                                                           //
//////////////////////////////////////////////////////////////////////////////////////

#include <math.h>

#include "../src/warpGenerator.h"
#include "../src/warp.h"
#include "../src/stats.h"

double speed = 1.4;

WarpGenerator::WarpGenerator(Factory *factory)
        : _factory(factory) {
    Print("CREATING WARP GENERATOR\n");
}

void WarpGenerator::Behavior() {
    // Generates warps only in working schedule Monday-Friday 07:00 - 15:00
    if (fmod(Time, WEEK) < DAY * 5) {
        // Working time 07:00 - 15:00
        if ((fmod(Time, DAY) >= HOUR * 7) && (fmod(Time, DAY) <= HOUR * 15)) {
            // Generator is in active state  -> generate new warp
            Warp *warp = new Warp(_factory, _generated++);
            warp->Activate();
            Stats::addWarpLength(warp->GetLength());
            Stats::addWarpThreadCount(warp->GetThreadCount());

            // Actualize stats
            double nextWarpTime = Factory::WARP_GENERATING::GetPeriod() / speed;
            Stats::addWarpPeriod(nextWarpTime / MINUTE);
            _dailyCount += 1;

            // Activate it self after period of time
            Activate(Time + nextWarpTime);
        } else {
            // Shift ended -> record daily count and reset counter
            Stats::addWarpCount(_dailyCount);
            _dailyCount = 0;
            // Delay activation to next Monday
            if (fmod(Time, WEEK) >= DAY * 4) {
                Activate(Time + DAY * 2 + 16 * HOUR);
            } else {
                // Delay activation to next working day
                Activate(Time + HOUR * 16);
            }
        }
    } else {
        // Should not get here
        Print("UNKNOWN BEHAVIOR AT TIME | %d\n", Time);
        _dailyCount = 0;
        // Delay activation to next Monday
        Activate(Time + DAY * 2 + 16 * HOUR);
    }
}
