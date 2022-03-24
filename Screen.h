#ifndef Screen_h
#define Screen_h

#include <stdint.h>
#include "Coordinates.h"

#include "Camera.h"
#include "World.h"

//----------------
class Screen{
protected:
  const unsigned int limit_x_{};
  const unsigned int limit_y_{};
  bool** pixels{};
  bool** view_pixels{};
  Coordinates<dimension_type> offset_{0, 0};
  Camera* camera_{};
  World* world_{};
  
public:
  Screen() = delete;
  Screen(const unsigned int new_limit_x, const unsigned int new_limit_y, Camera* new_camera, World* new_world);
  
  virtual ~Screen();
  
};
//----------------
#endif
