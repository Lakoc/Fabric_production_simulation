//////////////////////////////////////////////////////////////////////////////////////
//  School:     Faculty of Information Technology, Brno University of Technology    //
//  Course:     IMS - Modelling and Simulation                                      //
//  Module:     model.cc                                                            //
//  Authors:    Alexander Polok (xpolok03), Michal Rozsíval (xrozsi06)              //
//  Date:       7.12.2020                                                           //
//////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <tuple>

#include "model.h"
#include "constants.h"

uint32_t GetUnit(std::string arg);

std::tuple<bool, uint32_t> GetCount(std::string arg);

void ArgErrFormat();

void ArgErrOverflow();


int main(int argc, char *argv[]) {
    uint32_t defCount = 1;
    uint32_t defUnit = YEAR;
    if (argc > 1 && argc != 3) {
        ArgErrFormat();
    }
    if (argc == 3) {
        bool valid = true;
        std::tie(valid, defCount) = GetCount(argv[1]);
        if (valid) {
            defUnit = GetUnit(argv[2]);
        }
    }

    uint32_t simTime = defCount * defUnit;
    if (defCount != 0 && simTime / defCount != defUnit) {
        // overflow handling
        ArgErrOverflow();
        simTime = 1 * YEAR;
    }

    std::cout << "RUNNING SIMULATION WITH DURATION '" << simTime << "' SECONDS\n\n";

    delete new Model(simTime);
    return 0;
}


uint32_t GetUnit(std::string arg) {
    if (arg.size() != 1) {
        ArgErrFormat();
        return YEAR;
    }

    switch (arg.at(0)) {
        case 'D':
            return DAY;
        case 'W':
            return WEEK;
        case 'M':
            return MONTH;
        case 'Y':
            return YEAR;
        default:
            ArgErrFormat();
            return YEAR;
    }
}

std::tuple<bool, uint32_t> GetCount(std::string arg) {
    uint32_t defCount;

    try {
        std::size_t pos;
        defCount = std::stoul(arg, &pos);
        if (pos < arg.size()) {
            ArgErrFormat();
            return std::make_tuple<bool, uint32_t>(false, 1);
        }
    } catch (std::invalid_argument const &ex) {
        ArgErrFormat();
        return std::make_tuple<bool, uint32_t>(false, 1);
    } catch (std::out_of_range const &ex) {
        ArgErrOverflow();
        return std::make_tuple<bool, uint32_t>(false, 1);
    }

    if (defCount <= 0) {
        ArgErrFormat();
        return std::make_tuple<bool, uint32_t>(false, 1);
    }

    return std::make_tuple<bool, uint32_t>(true, (uint32_t) defCount);
}

void ArgErrFormat() {
    std::cerr
            << "WRONG PARAMETERS FORMAT (expected [X D/W/M/Y], X whole number > 0, D - day, W - week, M - month, Y - year) - using default value 1 year\n";
}

void ArgErrOverflow() {
    std::cerr << "UNSIGNED OVERFLOW - using default value 1 year\n";
}