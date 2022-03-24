#ifndef RandomAndOtherThings_h
#define RandomAndOtherThings_h

#include <Arduino.h>
//----------------
class Random{
  public:
  static SetSeed(unsigned long seed){
    randomSeed(seed);
  }
  static unsigned long GetRandom(unsigned long max){
    return random(max);
  }
  static unsigned long GetRandom(unsigned long min, unsigned long max){
    return random(min, max);
  }
};
//----------------
#endif
