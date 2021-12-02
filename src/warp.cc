//////////////////////////////////////////////////////////////////////////////////////
//  School:     Faculty of Information Technology, Brno University of Technology    //
//  Course:     IMS - Modelling and Simulation                                      //
//  Module:     warp.cc                                                             //
//  Authors:    Alexander Polok (xpolok03), Michal Rozsíval (xrozsi06)              //
//  Date:       7.12.2020                                                           //
//////////////////////////////////////////////////////////////////////////////////////

#include <tuple>

#include "warp.h"
#include "stats.h"

Warp::Warp(Factory *factory, int count) : _factory(factory), _count(count), _startTime(Time) {}

void Warp::Behavior() {
    SetConnectingFlags();

    WindingProcess();
    WarpingProcess();
    GluingProcess();
    RewindBenchConnectingProcess();
    LoomingProcess();
    WeavingProcess();
    FinalCheckProcess();

    if (Factory::SALE::GoSale()) {
        Stats::addSaleProbability(1);
    } else {
        Stats::addSaleProbability(0);
    }
    Stats::addProcessLifeTime((Time - _startTime) / DAY);
}

Warp::~Warp() {
}

double Warp::GetLength() const {
    return _length;
}

uint32_t Warp::GetThreadCount() const {
    return _threadCount;
}

void Warp::SetConnectingFlags() {
    _goNonWeavConnecting = Factory::NON_WEAV_CONNECTING::GoConnecting();
    _goGluing = Factory::GLUING::GoGluing();
    if (_goNonWeavConnecting) {
        if (!_goGluing) {
            // cause rewind connecting is not reachable and connecting has to be made
            _goWarpConnecting = true;
        } else {
            // choose random connecting method
            _goWarpConnecting = Factory::NON_WEAV_CONNECTING::GoWarpConnecting();
        }
    }
}

void Warp::WindingProcess() {
    if (Factory::WINDING::GoWinding()) {
        Enter(*(_factory->windingLine), 1);
        Stats::addWindingProbability(1);
        double weight = Factory::WARP::GetWeight(_length);
        double windingTime = Factory::WINDING::GetTime(weight);
        Wait(windingTime);
        Stats::addWindingTime(windingTime / MINUTE / weight);
        Leave(*(_factory->windingLine), 1);
    } else {
        Stats::addWindingProbability(0);

    }
}


void Warp::WarpingProcess() {
    // warping process
    Factory::WARPING::Type warpingLineType = Factory::WARPING::GoWarping(_length);
    Store *warpingLine = _factory->warpingLine[warpingLineType];
    Enter(*warpingLine, 1);
    Stats::addWarpingLine(warpingLineType);
    Wait(Factory::WARPING::GetTime(warpingLineType, _length));
    Leave(*warpingLine, 1);
    if (_goNonWeavConnecting && _goWarpConnecting) {
        Stats::addWarpingConnectingProbability(1);
        // first arrived warp
        if (_factory->warpConnecting->Empty()) {
            // insert to queue and wait for another Warp
            _factory->warpConnecting->Insert(this);
            Passivate();
        } else {
            // warp already waiting for connecting, remove from queue
            // add it's length to this one and cancel waiting warp
            Warp *waiting = dynamic_cast<Warp *>(_factory->warpConnecting->GetFirst());
            _length += waiting->GetLength();
            _threadCount = (u_int32_t) (_threadCount + waiting->GetThreadCount()) / 2;
            waiting->Cancel();

            warpingLineType = Factory::WARPING::GoWarping(_length);;
            warpingLine = _factory->warpingLine[warpingLineType];
            Enter(*warpingLine, 1);
            Stats::addWarpingConnectingLine(warpingLineType);
            Wait(Factory::WARPING::GetConnectingTime(_threadCount));
            Stats::addWarpingConnectingThreads(_threadCount);
            Leave(*warpingLine, 1);
        }
    } else {
        Stats::addWarpingConnectingProbability(0);
    }
}

void Warp::GluingProcess() {
    if (_goGluing) {
        Enter(*(_factory->gluingLine), 1);
        Stats::addGluingProbability(1);
        double warpGluingTime = Factory::GLUING::GetTime(_length);
        Wait(warpGluingTime);
        Stats::addGluingTime(warpGluingTime / SEC / _length);
        Leave(*(_factory->gluingLine), 1);
    } else {
        Stats::addGluingProbability(0);
    }
}

void Warp::RewindBenchConnectingProcess() {
    if (_goNonWeavConnecting && !_goWarpConnecting) {
        Stats::addRewindConnectingProbability(1);
        if (_factory->rewindConnecting->Empty()) {
            // insert to queue and wait for another Warp
            _factory->rewindConnecting->Insert(this);
            Passivate();
        } else {
            // warp already waiting for connecting, remove from queue
            // add it's length to this one and cancel waiting warp
            Warp *waiting = dynamic_cast<Warp *>(_factory->rewindConnecting->GetFirst());
            _length += waiting->GetLength();
            _threadCount = (u_int32_t) (_threadCount + waiting->GetThreadCount()) / 2;
            waiting->Cancel();
        }
        Enter(*(_factory->rewindConnectingLine), 1);
        Wait(Factory::REWIND_CONNECTING::GetConnectingTime(_threadCount));
        Stats::addRewindConnectingThreads(_threadCount);
        Leave(*(_factory->rewindConnectingLine), 1);
    } else if (_goGluing) {
        Stats::addRewindConnectingProbability(0);
    }
}

void Warp::LoomingProcess() {
    if (Factory::LOOMING::GoLooming()) {
        Enter(*(_factory->loomingLine), 1);
        Stats::addLoomingProbability(1);
        double loomingTime = Factory::LOOMING::GetTime(_threadCount);
        Wait(loomingTime);
        Stats::addLoomingTime(loomingTime / _threadCount / SEC);
        _wasLoomed = true;
        Leave(*(_factory->loomingLine), 1);
    } else {
        Stats::addLoomingProbability(0);
    }
}

void Warp::WeavingProcess() {

    Store *line;
    Factory::WEAVING::Type type;

    while (true) {
        std::tie(line, type) = GetAvailableLine();
        if (line != nullptr) {
            break;
        }
        _factory->weavingFull->InsLast(this);
        Passivate();
    }
    Enter(*line);
    Stats::addWeavingLine(type);
    _weavingStartTime = Time;

    if (_wasLoomed) {
        double stowingTime = Factory::STOWING::GetTime();
        Wait(stowingTime);
        Stats::addStowingTime(stowingTime / HOUR);
    } else {
        Enter(*_factory->weavConnectingLine);
        Stats::addWeavingConnectingThreads(_threadCount);
        double connectingTime = Factory::WEAVING::GetConnectingTime(_threadCount);
        Wait(connectingTime);
        Stats::addWeavingConnectingTime(connectingTime);
        Leave(*_factory->weavConnectingLine);
    }

    double controlTime = Factory::WEAVING::GetCheckTime();
    Wait(controlTime);
    Stats::addWeavingControlTime(controlTime / MINUTE);

    double fabricLength = Factory::WARP::GetFabricLength(_length);
    Stats::addWeavingLength(fabricLength);
    Wait(Factory::WEAVING::GetTime(fabricLength, type));
    Stats::addWeavingTime((Time - _weavingStartTime) / DAY);
    Leave(*line);
    if (_factory->weavingFull->Length() > 0) {
        Warp *waiting = dynamic_cast<Warp *>(_factory->weavingFull->GetFirst());
        waiting->Activate();
    }
}

std::tuple<Store *, Factory::WEAVING::Type> Warp::GetAvailableLine() {
    // check all lines
    int i = Distribution::Random() < 0.3 ? Factory::WEAVING::A : Factory::WEAVING::C;
    for (; i >= 0; i--) {
        // if has at least one member, return line
        if (!_factory->weavingLine[i]->Full()) {
            return std::make_tuple(_factory->weavingLine[i], (Factory::WEAVING::Type) i);
        }
    }
    // no available line
    return std::make_tuple(nullptr, (Factory::WEAVING::Type) -1);
}

void Warp::FinalCheckProcess() {
    Enter(*_factory->finalCheckingLine);
    double controlTime = Factory::FINAL_CHECKING::GetTime(Factory::WARP::GetFabricLength(_length));
    Wait(controlTime);
    Stats::addControlTime(controlTime / _length / SEC);
    Leave(*_factory->finalCheckingLine);
}


