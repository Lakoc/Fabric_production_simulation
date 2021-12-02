//////////////////////////////////////////////////////////////////////////////////////
//  School:     Faculty of Information Technology, Brno University of Technology    //
//  Course:     IMS - Modelling and Simulation                                      //
//  Module:     model.cc                                                            //
//  Authors:    Alexander Polok (xpolok03), Michal Rozsíval (xrozsi06)              //
//  Date:       7.12.2020                                                           //
//////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <random>

#include "constants.h"
#include "simlib.h"
#include "factory.h"
#include "stats.h"
#include "warpGenerator.h"
#include "model.h"


Model::Model(double simulationTime) {

    // Init factory
    Factory *factory = new Factory();

    Init(0, simulationTime);
    Stats::Init();

    std::random_device Random;
    std::default_random_engine engine{Random()};
    Distribution::SetEngine(engine);

    // Create warp generator
    WarpGenerator *warpGenerator = new WarpGenerator(factory);
    // Start working on Monday 7 AM
    warpGenerator->Activate(HOUR * 7);

    Print("STARTING SIMULATION | %d s\n\n", (uint32_t) Time);

    Run();

    Print("SIMULATION ENDED | %d s\n\n", (uint32_t) Time);
    Print("GENERATING STATS\n\n");

    // Generating stats
    Stats::generateOutput(factory);

    Stats::Clear();
    delete factory;
    delete warpGenerator;
}