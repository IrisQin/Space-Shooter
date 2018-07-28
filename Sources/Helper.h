#pragma once
#include <iostream>
using namespace std;

template<class T> inline void destroy(T*& p) { delete p; p = nullptr; }

inline int randomInt(int min, int max) { return rand() % (max - min + 1) + min; }