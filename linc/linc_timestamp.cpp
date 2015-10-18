#include "./linc_timestamp.h"

#include <sys/time.h>
#include <stdint.h>

#ifdef HX_LINUX
    #include <unistd.h>
    #include <stdio.h>
#endif

#ifdef HX_MACOS
    #include <mach/mach_time.h>
    #include <mach-o/dyld.h>
    #include <CoreServices/CoreServices.h>
#endif

#ifdef IPHONE
    #include <QuartzCore/QuartzCore.h>
#endif

#ifdef ANDROID
    #include <time.h>
#endif


namespace linc {

    namespace timestamp {

        static double t0 = 0;

        double now() {

            #if defined(HX_MACOS)

                static double time_scale = 0.0;

                if (time_scale == 0.0) {
                    mach_timebase_info_data_t info;
                    mach_timebase_info(&info);
                    time_scale = 1e-9 * (double)info.numer / info.denom;
                }

               double r =  mach_absolute_time() * time_scale;
               return mach_absolute_time() * time_scale;

            #else

                #if defined(IPHONE)

                    double t = CACurrentMediaTime();

                #elif defined(GPH) || defined(HX_LINUX) || defined(EMSCRIPTEN)

                    struct timeval tv;

                    if( gettimeofday(&tv,NULL) ) {
                        return 0;
                    }

                    double t =  ( tv.tv_sec + ((double)tv.tv_usec) / 1000000.0 );

                #else

                    struct timespec ts;

                    clock_gettime(CLOCK_MONOTONIC, &ts);

                    double t =  ( ts.tv_sec + ((double)ts.tv_nsec)*1e-9  );

                #endif

                if (t0 == 0) {
                    t0 = t;
                }

                return t - t0;

            #endif

        } //now()

    } //timestamp namespace

} //linc
