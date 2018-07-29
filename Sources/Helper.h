#pragma once
#include <iostream>
using namespace std;

// TODO
// abandon all static
// smart pointer somewhere
// add blink when something is hurt but not die
// too many timers?!
// friend class
// very tiny bug: when player upgrade on boundary, it may be stuck
// sprite should be an abstract class...


// avoid wild pointer
template<class T> inline void destroy(T*& p) { delete p; p = nullptr; }
// return a random number between [min,max]
inline int randomInt(int min, int max) { return rand() % (max - min + 1) + min; }