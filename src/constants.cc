//////////////////////////////////////////////////////////////////////////////////////
//  School:     Faculty of Information Technology, Brno University of Technology    //
//  Course:     IMS - Modelling and Simulation                                      //
//  Module:     constants.cc                                                        //
//  Authors:    Alexander Polok (xpolok03), Michal Rozsíval (xrozsi06)              //
//  Date:       7.12.2020                                                           //
//////////////////////////////////////////////////////////////////////////////////////

#include "constants.h"

std::default_random_engine Distribution::_engine;

void Distribution::SetEngine(std::default_random_engine engine) {
    _engine = engine;
}

double Distribution::Normal(double mean, double standardDeviation, double offset, uint32_t timeUnit) {
    std::normal_distribution<double> distribution{mean, standardDeviation};
    double value = (distribution(_engine) + offset) * timeUnit;
    while (value <= 0) {
        value = (distribution(_engine) + offset) * timeUnit;
    }
    return value;
}

double Distribution::Gamma(double alfa, double beta, double offset, uint32_t timeUnit) {
    std::gamma_distribution<double> distribution{alfa, beta};
    return (distribution(_engine) + offset) * timeUnit;
}


double Distribution::Exponential(double lambda, double offset, uint32_t timeUnit) {
    std::exponential_distribution<double> distribution{lambda};
    return (distribution(_engine) + offset) * timeUnit;
}

double Distribution::Random() {
    std::uniform_real_distribution<double> distribution{0.0, 1.0};
    return distribution(_engine);
}