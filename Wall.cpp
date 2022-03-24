#include "Wall.h"

//----------------
Wall::Wall(Coordinates<dimension_type> new_coordinates) :coordinates_(new_coordinates){
}
//----------------
bool Wall::GetIsExist(){
  return this->is_exist_;
}
//----------------
Coordinates<dimension_type> Wall::GetCoordinates(){
  return this->coordinates_;
}
//----------------
void Wall::Tick(){
  return;
}
//----------------
//----------------
//----------------
void WallBuilder::BuildWall(Wall **walls, const int wall_array_length_, int& amount_wall, Coordinates<dimension_type> new_coordinates){
  if(amount_wall >= wall_array_length_){
    return;
  }  
  walls[amount_wall++] = new Wall(new_coordinates);  
}
//----------------
void WallBuilder::BuildWallsPerpendicular(Wall **walls, const int wall_array_length_, int& amount_wall, Coordinates<dimension_type> start_coordinates, unsigned int count, bool isVertical){
  for(int i = 0; i < count; i++){
    this->BuildWall(walls, wall_array_length_, amount_wall, start_coordinates);
    if(isVertical){
      start_coordinates.y_++;
    }else{
      start_coordinates.x_++;      
    }
  }
}
//----------------
