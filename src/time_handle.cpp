#include "time_handle.h"

time_t time_elapsed(timeval start, timeval end)
{
    long seconds = end.tv_sec - start.tv_sec;
    long microseconds = end.tv_usec - start.tv_usec;
    return seconds * 1e3 + microseconds * 1e-3;
}
