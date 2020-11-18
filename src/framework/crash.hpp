#ifndef CRASH_HPP
#define CRASH_HPP

#include <cstdio>

#define crash(label, msg) do { printf(msg "\n"); goto label;} while(0);

#define crash_and_burn(msg) do { printf(msg "\n"); exit(1); } while(0);

#endif // CRASH_HPP