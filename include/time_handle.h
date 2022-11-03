#include <sys/time.h>

// typedef unsigned long long time64_t;
#define time_now(var) (gettimeofday(&var, 0))

// restituisce il tempo passato tra start e end in millisecondi
time_t time_elapsed(timeval start, timeval end);