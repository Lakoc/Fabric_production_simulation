//////////////////////////////////////////////////////////////////////////////////////
//  School:     Faculty of Information Technology, Brno University of Technology    //
//  Course:     IMS - Modelling and Simulation                                      //
//  Module:     factory.h                                                           //
//  Authors:    Alexander Polok (xpolok03), Michal Rozsíval (xrozsi06)              //
//  Date:       7.12.2020                                                           //
//////////////////////////////////////////////////////////////////////////////////////

#ifndef __FACTORY_H__
#define __FACTORY_H__

#include "simlib.h"
#include "constants.h"

class Factory {

public:


    class WARP {
        static constexpr double _weightCoe = 11.0 / 70.0;
        static constexpr double _fabricCoe = 0.93;
        static constexpr double _lambdaLength = 0.0010554608880883147;
        static constexpr double _alfaThreadCount = 4947.738585247057;
        static constexpr double _betaThreadCount = 461.5743115569517;

    public:
        static constexpr uint32_t MeanThreadCount = _alfaThreadCount;

        static double GetFabricLength(double length) {
            return length * _fabricCoe;
        }

        static double GetWeight(double length) {
            return length * _weightCoe;
        }

        static double GetLength() {
            return Distribution::Exponential(_lambdaLength, 0, SEC);
        }

        static double GetThread() {
            return Distribution::Normal(_alfaThreadCount, _betaThreadCount, 0, SEC);
        }

    };


    class WARP_GENERATING {
        static constexpr double _alfa = 11.14872292162632;
        static constexpr double _beta = 3.458269798514816;
        static constexpr double _offset = 0;
    public:

        static double GetPeriod() {
            return Distribution::Normal(_alfa, _beta, _offset, MINUTE);
        }
    };

    class WINDING {
        static constexpr double _meanGo = 13.12031107440972;
        static constexpr double _standardDeviationGo = 6.317049313730782;
        static constexpr double _alfaTime = 1.109007961687189;
        static constexpr double _betaTime = 1.5663833901922863;
        static constexpr double _offsetTime = 1.4922279792746111;

    public:
        static bool GoWinding() {
            return Distribution::Random() * 100 < Distribution::Normal(_meanGo, _standardDeviationGo, 0, PERCENT);
        }


        static double GetTime(double weight) {
            return Distribution::Gamma(_alfaTime, _betaTime, _offsetTime, MINUTE) * weight;
        }
    };

    class WARPING {
        // WARP MACHINE type A, type B, type C

        // minutes to do 1 meter of warp
        static constexpr double _speed[] = {0.8, 0.225, 0.18};

        // max length of yarn in meters
        static constexpr uint32_t _maxLengthA = 150;
        static constexpr uint32_t _maxLengthB = 800;

        // seconds to do 1 thread
        static constexpr double _speedConnecting = 1.08;

    public:
        enum Type {
            A = 0,
            B,
            C,
            COUNT,
        };

        static double GetTime(Type type, double length) {
            return WARPING::_speed[type] * length * MINUTE;
        }

        static double GetConnectingTime(int threadCount) {
            return _speedConnecting * threadCount;
        }

        static Type GoWarping(double length) {
            if (length < _maxLengthA) {
                return A;
            } else if (length < _maxLengthB) {
                return B;
            } else {
                return C;
            }
        }
    };

    class NON_WEAV_CONNECTING {
        static constexpr double _mean = 10.07353786275826;
        static constexpr double _standardDeviation = 6.9069251429201355;
        static constexpr double _warpConnectingProbability = 0.9;

    public:
        static bool GoConnecting() {
            return Distribution::Random() * 100 < Distribution::Normal(_mean, _standardDeviation, 0, PERCENT);
        }

        // if Go Connecting returned yes, call this and check
        // if connecting gonna be on warping machine, or on rewinding bench
        static bool GoWarpConnecting() {
            return Distribution::Random() < _warpConnectingProbability;
        }
    };

    class GLUING {
        static constexpr double _alfaGo = 11.901974586210565;
        static constexpr double _betaGo = 6.240341918576309;

        static constexpr double _alfaTime = 5.54620743620452;
        static constexpr double _betaTime = 0.8482514443094381;

    public:
        static bool GoGluing() {
            double probability = Distribution::Gamma(_alfaGo, _betaGo, 0, PERCENT);
            if (probability >= 100.0) {
                probability = 100;
            }
            return Distribution::Random() * 100 < probability;
        }

        static double GetTime(double length) {
            return Distribution::Gamma(_alfaTime, _betaTime, 0, SEC) * length;
        }
    };

    class REWIND_CONNECTING {
        // seconds to do 1 thread
        static constexpr double _speedConnecting = 1.08;

    public:
        static double GetConnectingTime(int threadCount) {
            return _speedConnecting * threadCount;
        }
    };

    class LOOMING {
        static constexpr double _mean = 41.16399750802745;
        static constexpr double _standardDeviation = 11.099238721311924;

        static constexpr double _alfa = 1.2258893702224323;
        static constexpr double _beta = 0.5563355752239141;
        static constexpr double _offset = 0.7903113680436132;

    public:
        static bool GoLooming() {
            return Distribution::Random() * 100 < Distribution::Normal(_mean, _standardDeviation, 0, PERCENT);
        }

        static double GetTime(uint32_t threadCount) {
            return Distribution::Gamma(_alfa, _beta, _offset, SEC) * threadCount;
        }
    };

    class STOWING {
        static constexpr double _alfa = 7.140333054656914;
        static constexpr double _beta = 0.28422277660054224;

    public:
        static double GetTime() {
            return Distribution::Gamma(_alfa, _beta, 0, HOUR);
        }
    };

    class WEAVING {
        // WEAV MACHINE type A, type B, type C
        // minutes to do 1 meter of warp
        static constexpr double _speed[] = {144.0 / 17.0, 144.0 / 25.0, 144.0 / 35.0};


        // seconds to do 1 thread
        static constexpr double _speedConnecting = 0.72;

        static constexpr double _mean = 60.0;
        static constexpr double _standardDeviation = 3.0;

    public:
        enum Type {
            A = 0,
            B,
            C,
            COUNT,
        };

        static double GetConnectingTime(int threadCount) {
            return _speedConnecting * threadCount;
        }

        static double GetTime(double length, Type type) {
            return _speed[type] * length * MINUTE;
        }

        static double GetCheckTime() {
            return Distribution::Normal(_mean, _standardDeviation, 0, MINUTE);
        }
    };

    class FINAL_CHECKING {
        static constexpr double _alfa = 1.536284450430704;
        static constexpr double _beta = 0.749057614500348;
        static constexpr double _offset = 2.288135593220339;
    public:
        static double GetTime(double length) {
            return Distribution::Gamma(_alfa, _beta, _offset, SEC) * length;
        }
    };


    class SALE {
        static constexpr double _sale = 0.025;

    public:
        static bool GoSale() {
            return Distribution::Random() < _sale;
        }
    };

    Factory();

    ~Factory();

    Store *windingLine;
    Store *warpingLine[WARPING::COUNT];
    Queue *warpConnecting;
    Store *gluingLine;
    Store *rewindConnectingLine;
    Queue *rewindConnecting;
    Store *loomingLine;
    Store *weavConnectingLine;
    Store *weavingLine[WEAVING::COUNT];
    Queue *weavingFull;
    Store *finalCheckingLine;
};

#endif