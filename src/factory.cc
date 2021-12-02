//////////////////////////////////////////////////////////////////////////////////////
//  School:     Faculty of Information Technology, Brno University of Technology    //
//  Course:     IMS - Modelling and Simulation                                      //
//  Module:     factory.cc                                                          //
//  Authors:    Alexander Polok (xpolok03), Michal Rozsíval (xrozsi06)              //
//  Date:       7.12.2020                                                           //
//////////////////////////////////////////////////////////////////////////////////////

#include <iostream>

#include "factory.h"

Factory::Factory() {
    Print("INITIALIZING FACTORY\n");

    windingLine = new Store("Winding machine store", 2);

    warpingLine[WARPING::A] = new Store("Warping machine A store", 1);
    warpingLine[WARPING::B] = new Store("Warping machine B store", 2);
    warpingLine[WARPING::C] = new Store("Warping machine C store", 9);

    warpConnecting = new Queue("Connecting on warping machine queue");

    gluingLine = new Store("Gluing machine store", 2);

    rewindConnectingLine = new Store("Connecting on rewinding bench machine store", 1);
    rewindConnecting = new Queue("Connecting on rewind bench machine queue");

    loomingLine = new Store("Looming people store", 3);

    weavConnectingLine = new Store("Connecting on weaving machine store", 3);

    weavingLine[WEAVING::A] = new Store("Weaving machine A store", 36);
    weavingLine[WEAVING::B] = new Store("Weaving machine B store", 44);
    weavingLine[WEAVING::C] = new Store("Weaving machine C store", 66);
    weavingFull = new Queue("Waiting for any weaving line queue");

    finalCheckingLine = new Store("Final checking people store", 3);
}

Factory::~Factory() {
    std::cout << "CLEANING\n";

    delete windingLine;

    for (int i = 0; i < WARPING::COUNT; i++) {
        delete warpingLine[i];
    }

    delete warpConnecting;
    delete gluingLine;
    delete rewindConnectingLine;
    delete rewindConnecting;
    delete loomingLine;
    delete weavConnectingLine;

    for (int i = 0; i < WEAVING::COUNT; i++) {
        delete weavingLine[i];
    }

    delete weavingFull;
    delete finalCheckingLine;
}