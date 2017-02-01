#include <hxcpp.h>

#include "./linc_timestamp.h"

// Originally adapted for snow from nme
// https://github.com/underscorediscovery/snow
// https://github.com/haxenme/nme

#if HX_WINDOWS
#include <Shlobj.h>
#include <time.h>
// #include <windows.h>

    namespace linc {

        namespace timestamp {

            static double t0 = 0;

            double now() {

                __int64 current;
                static __int64 t0 = 0;
                static double period = 0;

                if(QueryPerformanceCounter((LARGE_INTEGER*)&current)) {

                    if(t0 == 0) {

                        t0 = current;

                        __int64 freq;
                        QueryPerformanceFrequency((LARGE_INTEGER*)&freq);

                        if(freq != 0) {
                            period = 1.0/freq;
                        }

                    } //t0 == 0

                    if(period != 0 ) {
                        return (current - t0) * period;
                    }

                } //query

               return (double)clock() / ( (double)CLOCKS_PER_SEC);

            } //now()

        } //timestamp namespace

    } //linc

#endif //HX_WINDOWS
