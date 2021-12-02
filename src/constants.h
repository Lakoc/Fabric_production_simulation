//////////////////////////////////////////////////////////////////////////////////////
//  School:     Faculty of Information Technology, Brno University of Technology    //
//  Course:     IMS - Modelling and Simulation                                      //
//  Module:     constants.h                                                         //
//  Authors:    Alexander Polok (xpolok03), Michal Rozsíval (xrozsi06)              //
//  Date:       7.12.2020                                                           //
//////////////////////////////////////////////////////////////////////////////////////

#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

#include <cstdint>
#include <random>

static constexpr uint32_t PERCENT = 1;
static constexpr uint32_t SEC = 1;
static constexpr uint32_t MINUTE = 60 * SEC;
static constexpr uint32_t HOUR = 60 * MINUTE;
static constexpr uint32_t DAY = 24 * HOUR;
static constexpr uint32_t WEEK = 7 * DAY;
static constexpr uint32_t MONTH = (uint32_t) ((365.25 / 12.0) * (double) DAY);
static constexpr uint32_t YEAR = (uint32_t) (365.25 * (double) DAY);


class Distribution {

    static std::default_random_engine _engine;

public:
    Distribution();

    static void SetEngine(std::default_random_engine engine);

    static double Normal(double mean, double standardDeviation, double offset, uint32_t timeUnit);

    static double Gamma(double alfa, double beta, double offset, uint32_t timeUnit);

    static double Exponential(double lambda, double offset, uint32_t timeUnit);

    static double Random();
};

#endif