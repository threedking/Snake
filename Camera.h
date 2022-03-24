#ifndef Camera_h
#define Camera_h

#include <stdint.h>
#include "Coordinates.h"


//----------------
class Camera{ //рисует слева направо, сверху вниз
protected:
  /*unsigned int limit_x_{};  
  unsigned int limit_y_{};*/
  Coordinates<dimension_type> limits{}; // [0 - limit)
  Coordinates<dimension_type> offset_{0,0}; // К центру камеры
  Coordinates<dimension_type> focus_[2]{{0, 1}, {0, 1}}; //{1, 4}, {6, 10
  Coordinates<dimension_type>* target_{};
  dimension_type speed_{1};
  
  void FindFocus();
  
public:
  Camera() = delete;
  //Camera(unsigned int new_limit_x, unsigned int new_limit_y, Coordinates<dimension_type>* new_target);
  Camera(Coordinates<dimension_type> new_limits, Coordinates<dimension_type>* new_target);
  
  virtual ~Camera(){}
  
  void Tick();
  void GoToTarget();
  Coordinates<dimension_type> GetOffset();
};
//----------------
#endif
