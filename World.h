#ifndef World_h
#define World_h

#include <stdint.h>
#include "RandomAndOtherThings.h"
#include "Coordinates.h"
#include "Snake.h"
#include "Food.h"
#include "Wall.h"

//----------------
class World{
protected:
  dimension_type limit_x_{};  // [0 - limit)
  dimension_type limit_y_{};

  bool snakes_leave_parts_{false};
  
  static const int snakes_array_length_{100};
  Snake *snakes_[snakes_array_length_]{};
  int amount_snakes_{0};

  static const int food_array_length_{100};
  Food *food_[food_array_length_]{};
  int amount_food_{0};
  
  static const int wall_array_length_{100};
  Wall *wall_[wall_array_length_]{};
  int amount_wall_{0};

  Coordinates<dimension_type> FindFreePlace();
  bool IsCollideWithWorldParts(Coordinates<dimension_type> checking_place);
  void DestroyAndRestoreFood(Food *food);  
  
public:
  World() = delete;
  World(dimension_type new_limit_x, dimension_type new_limit_y);
  virtual ~World(){}

  void Tick();
  void AddSnake(Snake *new_snake);

};
//----------------
#endif
