#ifndef Wall_h
#define Wall_h

#include "Coordinates.h"

//----------------
class Wall{
protected:
  Coordinates<dimension_type> coordinates_{0,0};
  bool is_exist_{true};
public:
  Wall() = delete;
  Wall(Coordinates<dimension_type> new_coordinates);
  virtual ~Wall(){}

  
  Coordinates<dimension_type> GetCoordinates();
  bool GetIsExist();
  virtual void Tick();
  
};
//----------------
enum class WallType{  //4x4
  TETRISo,
  TETRISi,
  TETRISs,
  TETRISz,
  TETRISl,
  TETRISj,
  TETRISt,
  LINE2,
  LINE3,
  SQUARE3x3,
  SQUARE4x4,
  ANGLE2x2,
  ANGLE3x3,
  ANGLE4x4,
  //Тут придумать еще фигур и дальше создать шаблоны и доделать билдер
};
//----------------
class WallBuilder{
protected:
public:
  WallBuilder(){}
  virtual ~WallBuilder(){}  

  void BuildWall(Wall **walls, const int wall_array_length_, int& amount_wall, Coordinates<dimension_type> new_coordinates);
  void BuildWallsPerpendicular(Wall **walls, const int wall_array_length_, int& amount_wall, Coordinates<dimension_type> start_coordinates, unsigned int count, bool isVertical);
};
//----------------
#endif
