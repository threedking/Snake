#ifndef Food_h
#define Food_h

#include "Coordinates.h"

//----------------
class Food{
protected:
  Coordinates<dimension_type> coordinates_{0,0};
  int nutrition_energy_{0};
  bool is_exist_{true};
public:
  Food() = delete;
  Food(Coordinates<dimension_type> new_coordinates);
  virtual ~Food(){}
  
  bool TryEat(Coordinates<dimension_type> eat_coordinates);
  Coordinates<dimension_type> GetCoordinates();
  int GetNutritionEnergy();
  virtual void Tick();
  void Destroy();
  bool GetIsExist();
  void Restore(Coordinates<dimension_type> new_coordinates);
};
//----------------
class Cherry: public Food{
protected:  
public:
  Cherry() = delete;
  Cherry(Coordinates<dimension_type> new_coordinates);
  virtual ~Cherry(){}
};
//----------------
#endif
