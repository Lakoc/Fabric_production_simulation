//////////////////////////////////////////////////////////////////////////////////////
//  School:     Faculty of Information Technology, Brno University of Technology    //
//  Course:     IMS - Modelling and Simulation                                      //
//  Module:     stats.cc                                                            //
//  Authors:    Alexander Polok (xpolok03), Michal Rozsíval (xrozsi06)              //
//  Date:       7.12.2020                                                           //
//////////////////////////////////////////////////////////////////////////////////////

#include "stats.h"

Histogram *Stats::_warpLength;
Histogram *Stats::_warpPeriod;
Histogram *Stats::_warpThreadCount;
Histogram *Stats::_warpCount;
Histogram *Stats::_windingProbability;
Histogram *Stats::_windingTime;
Histogram *Stats::_warpingLine;
Histogram *Stats::_warpingConnectingProbability;
Histogram *Stats::_warpingConnectingLine;
Histogram *Stats::_warpingConnectingThreads;
Histogram *Stats::_gluingProbability;
Histogram *Stats::_gluingTime;
Histogram *Stats::_rewindConnectingProbability;
Histogram *Stats::_rewindConnectingThreads;
Histogram *Stats::_loomingProbability;
Histogram *Stats::_loomingTime;
Histogram *Stats::_weavingLine;
Histogram *Stats::_weavingLength;
Histogram *Stats::_weavingControlTime;
Histogram *Stats::_stowingTime;
Histogram *Stats::_weavingConnectingThreads;
Histogram *Stats::_weavingConnectingTime;
Histogram *Stats::_controlTime;
Histogram *Stats::_saleProbability;
Histogram *Stats::_processLifeTime;
Histogram *Stats::_weavingTime;

void Stats::addWarpLength(double value) {
    (*_warpLength)(value);
}

void Stats::addWarpCount(double value) {
    (*_warpCount)(value);
}

void Stats::addWarpThreadCount(double value) {
    (*_warpThreadCount)(value);
}

void Stats::addWarpPeriod(double value) {
    (*_warpPeriod)(value);
}

void Stats::addWindingProbability(double value) {
    (*_windingProbability)(value);
}

void Stats::addWindingTime(double value) {
    (*_windingTime)(value);
}

void Stats::addWarpingLine(double value) {
    (*_warpingLine)(value);
}

void Stats::addWarpingConnectingProbability(double value) {
    (*_warpingConnectingProbability)(value);
}

void Stats::addWarpingConnectingThreads(double value) {
    (*_warpingConnectingThreads)(value);
}

void Stats::addWarpingConnectingLine(double value) {
    (*_warpingConnectingLine)(value);
}

void Stats::addGluingTime(double value) {
    (*_gluingTime)(value);
}

void Stats::addGluingProbability(double value) {
    (*_gluingProbability)(value);
}

void Stats::addRewindConnectingProbability(double value) {
    (*_rewindConnectingProbability)(value);
}

void Stats::addRewindConnectingThreads(double value) {
    (*_rewindConnectingThreads)(value);
}

void Stats::addLoomingProbability(double value) {
    (*_loomingProbability)(value);
}

void Stats::addLoomingTime(double value) {
    (*_loomingTime)(value);
}

void Stats::addWeavingLine(double value) {
    (*_weavingLine)(value);
}

void Stats::addWeavingLength(double value) {
    (*_weavingLength)(value);
}

void Stats::addWeavingControlTime(double value) {
    (*_weavingControlTime)(value);
}

void Stats::addStowingTime(double value) {
    (*_stowingTime)(value);
}

void Stats::addWeavingConnectingThreads(double value) {
    (*_weavingConnectingThreads)(value);
}

void Stats::addWeavingConnectingTime(double value) {
    (*_weavingConnectingTime)(value);
}

void Stats::addControlTime(double value) {
    (*_controlTime)(value);
}

void Stats::addSaleProbability(double value) {
    (*_saleProbability)(value);
}

void Stats::addProcessLifeTime(double value) {
    (*_processLifeTime)(value);
}

void Stats::addWeavingTime(double value) {
    (*_weavingTime)(value);
}


void Stats::generateOutput(Factory *factory) {

//    // histograms
    SetOutput("osnova_delka.dat");
    _warpLength->Output();
    SetOutput("osnova_nite.dat");
    _warpThreadCount->Output();
    SetOutput("osnova_cas.dat");
    _warpPeriod->Output();
    SetOutput("osnova_pocet.dat");
    _warpCount->Output();
    SetOutput("soukani_pravdepodobnost.dat");
    _windingProbability->Output();
    SetOutput("soukani_cas.dat");
    _windingTime->Output();
    SetOutput("snovani_linka.dat");
    _warpingLine->Output();
    SetOutput("snovani_pritaceni_pravdepodobnost.dat");
    _warpingConnectingProbability->Output();
    SetOutput("snovani_pritaceni_linka.dat");
    _warpingConnectingLine->Output();
    SetOutput("snovani_pritaceni_nite.dat");
    _warpingConnectingThreads->Output();
    SetOutput("klizeni_pravdepodobnost.dat");
    _gluingProbability->Output();
    SetOutput("klizeni_cas.dat");
    _gluingTime->Output();
    SetOutput("klizeni_pritaceni_pravdepodobnost.dat");
    _rewindConnectingProbability->Output();
    SetOutput("klizeni_pritaceni_nite.dat");
    _rewindConnectingThreads->Output();
    SetOutput("navadeni_pravdepodobnost.dat");
    _loomingProbability->Output();
    SetOutput("navadeni_cas.dat");
    _loomingTime->Output();
    SetOutput("tkani_linka.dat");
    _weavingLine->Output();
    SetOutput("tkani_delka.dat");
    _weavingLength->Output();
    SetOutput("tkani_kontrola.dat");
    _weavingControlTime->Output();
    SetOutput("tkani_pritaceni_nite.dat");
    _weavingConnectingThreads->Output();
    SetOutput("tkani_pritaceni_cas.dat");
    _weavingConnectingTime->Output();
    SetOutput("zakladani_cas.dat");
    _stowingTime->Output();
    SetOutput("kontrola_cas.dat");
    _controlTime->Output();
    SetOutput("sleva_pravdepodobnost.dat");
    _saleProbability->Output();
    SetOutput("doba_zpracovani_osnovy.dat");
    _processLifeTime->Output();
    SetOutput("tkani_cas.dat");
    _weavingTime->Output();


    // queue
    SetOutput("store_finalCheckingLine.dat");
    factory->finalCheckingLine->Output();

    SetOutput("store_weavingLines.dat");
    factory->weavingLine[0]->Output();
    factory->weavingLine[1]->Output();
    factory->weavingLine[2]->Output();

    SetOutput("store_gluingLine.dat");
    factory->gluingLine->Output();

    SetOutput("store_loomingLine.dat");
    factory->loomingLine->Output();

    SetOutput("queue_rewindConnecting.dat");
    factory->rewindConnecting->Output();

    SetOutput("store_rewindConnectingLine.dat");
    factory->rewindConnectingLine->Output();

    SetOutput("queue_warpConnecting.dat");
    factory->warpConnecting->Output();

    SetOutput("store_warpingLine.dat");
    factory->warpingLine[0]->Output();
    factory->warpingLine[1]->Output();
    factory->warpingLine[2]->Output();

    SetOutput("store_weavConnectingLine.dat");
    factory->weavConnectingLine->Output();

    SetOutput("queue_weavingFull.dat");
    factory->weavingFull->Output();

    SetOutput("store_windingLine.dat");
    factory->windingLine->Output();

    // Creating overview output
    SetOutput("general_info.dat");

    // General
    Print("__GENERAL__\n");
    uint32_t generated = _warpLength->stat.Number();
    uint32_t processed = _saleProbability->stat.Number();
    Print("Warps generated: %d\nWarps processed: %d\nGenerated / Processed rate: %f %\n", generated, processed,
          (double) processed / generated * 100);
    double warpDiscountRate = _saleProbability->stat.MeanValue();
    Print("Warps discounted: %d (%f %)\n\n", (uint32_t) (processed * warpDiscountRate), warpDiscountRate * 100);

    // Winding
    Print("__WINDING__\n");
    Print("Used capacity over time: %f %\n",
          factory->windingLine->tstat.MeanValue() / factory->windingLine->Capacity() * 100);
    Print("Actually winding: %d [%d], queue: %d\n", factory->windingLine->Used(), factory->windingLine->Capacity(),
          factory->windingLine->QueueLen());
    uint32_t wounded = _warpingLine->stat.Number();
    double windingProbability = _windingProbability->stat.MeanValue();
    Print("Warps wounded: %d (%f %)\n", (uint32_t) (wounded * windingProbability),
          windingProbability * 100);
    Print("Winding mean time per kg: %f m\n", _windingTime->stat.MeanValue());
    Print("Warps which finished winding: %d\n\n", wounded);

    // Warping
    Print("__WARPING__\n");
    uint32_t actuallyWarping = 0;
    uint32_t queueLen = 0;
    int lines = 3;
    double capacityUsed[lines + 1];
    capacityUsed[lines] = 0.0;
    uint32_t maxCapacity = 0;
    for (int i = 0; i < lines; i++) {
        queueLen += factory->warpingLine[i]->QueueLen();
        actuallyWarping += factory->warpingLine[i]->Used();
        capacityUsed[i] = factory->warpingLine[i]->tstat.MeanValue() / factory->warpingLine[i]->Capacity() * 100;
        capacityUsed[3] += capacityUsed[i];
        maxCapacity += factory->warpingLine[i]->Capacity();
    }
    capacityUsed[3] /= 3;
    Print("Used capacity over time: %f %, %f %, %f % (ø %f %)\n", capacityUsed[0], capacityUsed[1], capacityUsed[2],
          capacityUsed[3]);
    Print("Actually warping: %d [%d], queue: %d\n", actuallyWarping, maxCapacity, queueLen);
    uint32_t finished_warping = _gluingProbability->stat.Number();
    uint32_t preConnectionCount = _warpingConnectingProbability->stat.Number();
    double connectedProbability = _warpingConnectingProbability->stat.MeanValue();
    uint32_t connected = (uint32_t) (preConnectionCount * connectedProbability);
    Print("Warps connected during warping: %d (%f %) -> %d\n", connected, connectedProbability * 100, connected / 2);
    Print("Warps waiting for connection: %d\n", factory->warpConnecting->Length());
    Print("Warps which finished warping: %d\n\n", finished_warping);

    // Gluing
    Print("__GLUING__\n");
    Print("Used capacity over time: %f %\n",
          factory->gluingLine->tstat.MeanValue() / factory->gluingLine->Capacity() * 100);
    Print("Actually gluing: %d [%d], queue: %d\n", factory->gluingLine->Used(), factory->gluingLine->Capacity(),
          factory->gluingLine->QueueLen());
    double gluingProbability = _gluingProbability->stat.MeanValue();
    Print("Warps glued: %d (%f %)\n", (uint32_t) (finished_warping * gluingProbability),
          gluingProbability * 100);
    connectedProbability = _rewindConnectingProbability->stat.MeanValue();
    preConnectionCount = _rewindConnectingProbability->stat.Number();
    connected = (uint32_t) (preConnectionCount * connectedProbability);
    Print("Warps connected during gluing: %d (%f %) -> %d\n", connected, connectedProbability * 100, connected / 2);
    Print("Rewind machine used over time: %f %\n",
          factory->rewindConnectingLine->tstat.MeanValue() / factory->rewindConnectingLine->Capacity() * 100);
    Print("Gluing mean time per m: %f s\n", _gluingTime->stat.MeanValue());
    uint32_t finishedGluing = _loomingProbability->stat.Number();
    Print("Warps which finished gluing: %d\n\n", finishedGluing);

    // Looming
    Print("__LOOMING__\n");
    Print("Used capacity over time: %f %\n",
          factory->loomingLine->tstat.MeanValue() / factory->loomingLine->tstat.Max() * 100);
    Print("Actually looming: %d [%d], queue: %d\n", factory->loomingLine->Used(), factory->loomingLine->Capacity(),
          factory->loomingLine->QueueLen());
    double loomingProbability = _loomingProbability->stat.MeanValue();
    Print("Warps loomed: %d (%f %)\n", (uint32_t) (finishedGluing * loomingProbability),
          loomingProbability * 100);
    Print("Looming mean time per thread: %f s\n", _loomingTime->stat.MeanValue());
    uint32_t finishedLooming = _weavingLine->stat.Number();
    Print("Warps which finished looming: %d\n\n", finishedLooming);

    // Weaving lines
    Print("__WEAVING_LINES__\n");
    uint32_t actuallyWeaving = 0;
    lines = 3;
    capacityUsed[lines] = 0.0;
    maxCapacity = 0;
    for (int i = 0; i < lines; i++) {
        actuallyWeaving += factory->weavingLine[i]->Used();
        capacityUsed[i] = factory->weavingLine[i]->tstat.MeanValue() / factory->weavingLine[i]->Capacity() * 100;
        capacityUsed[3] += capacityUsed[i];
        maxCapacity += factory->weavingLine[i]->Capacity();
    }
    capacityUsed[3] /= 3;
    Print("Used capacity over time: %f %, %f %, %f % (ø %f %)\n", capacityUsed[0], capacityUsed[1], capacityUsed[2],
          capacityUsed[3]);
    Print("Actually using weaving machines: %d [%d], queue: %d\n\n", actuallyWeaving, maxCapacity,
          factory->weavingFull->Length());

    // Stowing
    Print("\t__STOWING__\n");
    uint32_t stowingCount = _stowingTime->stat.Number();
    Print("\tWarps stowed: %d (%f %)\n", stowingCount, (double) stowingCount / finishedLooming * 100);
    Print("\tStowing mean time: %f h\n\n", _stowingTime->stat.MeanValue());

    // Connecting
    Print("\t__CONNECTING__\n");
    uint32_t connectedCount = factory->weavConnectingLine->tstat.Number();
    Print("\tWarps connected: %d (%f %)\n", connectedCount, (double) connectedCount / finishedLooming * 100);
    Print("\tConnecting mean time: %f h\n\n", _weavingConnectingTime->stat.MeanValue() / HOUR);

    // Weaving
    Print("\t__WEAVING__\n");
    uint32_t weaved = _weavingTime->stat.Number();
    Print("\tWarps weaved: %d\n", weaved);
    Print("\tWeaving mean time: %f h\n\n", _weavingTime->stat.MeanValue() * DAY / HOUR);
    Print("Warps which finished weaving: %d\n\n", weaved);

    // Control
    Print("__CONTROL__\n");
    uint32_t controlCapacity = factory->finalCheckingLine->Capacity();
    Print("Used capacity over time: %f %\n",
          factory->finalCheckingLine->tstat.MeanValue() / controlCapacity * 100);
    Print("Actually using under control: %d [%d], queue: %d\n", factory->finalCheckingLine->Used(), controlCapacity,
          factory->finalCheckingLine->QueueLen());
    Print("Control mean time per m: %f s\n", _controlTime->stat.MeanValue());
    Print("Warps which finished control: %d\n\n", _controlTime->stat.Number());
}

void Stats::Init() {
    _warpLength = new Histogram("Warp length", 0, 500, 10);
    _warpThreadCount = new Histogram("Warp thread count", 2000, 500, 10);
    _warpPeriod = new Histogram("Period of warp generating", 0, 2, 20);
    _warpCount = new Histogram("Daily warps count", 20, 5, 8);
    _windingProbability = new Histogram("Winding probability", 0, 1, 2);
    _windingTime = new Histogram("Winding time", 0, 2, 10);
    _warpingLine = new Histogram("Warping line chosen", 0, 1, 3);
    _warpingConnectingProbability = new Histogram("Warp connecting probability after warping", 0, 1, 2);
    _warpingConnectingLine = new Histogram("Warp connecting line chosen after warping", 0, 1, 3);
    _warpingConnectingThreads = new Histogram("Warp connecting threads count after warping", 3000, 500, 10);
    _gluingProbability = new Histogram("Gluing probability", 0, 1, 2);
    _gluingTime = new Histogram("Gluing time", 0, 2, 10);
    _rewindConnectingProbability = new Histogram("Warp rewind probability after gluing", 0, 1, 2);
    _rewindConnectingThreads = new Histogram("Warp rewind thread count", 3000, 500, 10);
    _loomingProbability = new Histogram("Warp looming probability", 0, 1, 2);
    _loomingTime = new Histogram("Warp looming time", 0, 1, 8);
    _weavingLine = new Histogram("Weaving line", 0, 1, 3);
    _weavingControlTime = new Histogram("Weaving control time", 10, 1, 10);
    _weavingLength = new Histogram("Weaving length", 0, 500, 20);
    _stowingTime = new Histogram("Stowing time", 0, 1, 10);
    _weavingConnectingThreads = new Histogram("Weaving connecting count of threads", 3000, 500, 10);
    _weavingConnectingTime = new Histogram("Weaving connecting time", 0, 50, 100);
    _controlTime = new Histogram("Control time", 0, 2, 6);
    _saleProbability = new Histogram("Sale probability", 0, 1, 2);
    _processLifeTime = new Histogram("Process life time", 0, 5, 10);
    _weavingTime = new Histogram("Process life time", 0, 10, 10);
}

void Stats::Clear() {
    delete _warpLength;
    delete _warpThreadCount;
    delete _warpPeriod;
    delete _warpCount;
    delete _windingProbability;
    delete _windingTime;
    delete _warpingLine;
    delete _warpingConnectingProbability;
    delete _warpingConnectingLine;
    delete _warpingConnectingThreads;
    delete _gluingProbability;
    delete _gluingTime;
    delete _rewindConnectingProbability;
    delete _rewindConnectingThreads;
    delete _loomingProbability;
    delete _loomingTime;
    delete _weavingLine;
    delete _weavingControlTime;
    delete _weavingLength;
    delete _stowingTime;
    delete _weavingConnectingThreads;
    delete _weavingConnectingTime;
    delete _controlTime;
    delete _saleProbability;
    delete _processLifeTime;
    delete _weavingTime;
}