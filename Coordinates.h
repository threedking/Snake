#ifndef Coordinates_h
#define Coordinates_h
#include <math.h>

using dimension_type = int;

//----------------
template <typename T>
class Coordinates{
  public:
    T x_;
    T y_;
    
    Coordinates() = delete;
    Coordinates(T new_x, T new_y):x_(new_x), y_(new_y){}
    virtual ~Coordinates(){}
    
    bool operator==(const Coordinates &coordinates){
      return this->x_ == coordinates.x_ && this->y_ == coordinates.y_;
    }
};

template <>
class Coordinates<int>{
  public:
    int x_{-1};
    int y_{-1};
    
    Coordinates(){}
    Coordinates(int new_x, int new_y):x_(new_x), y_(new_y){}
    virtual ~Coordinates(){}
    
    bool operator==(const Coordinates &coordinates){
      return this->x_ == coordinates.x_ && this->y_ == coordinates.y_;
    }
};

template <>
class Coordinates<float>{
  public:
    float x_{0.0f};
    float y_{0.0f};
    
    Coordinates(){}
    Coordinates(float new_x, float new_y):x_(new_x), y_(new_y){}
    virtual ~Coordinates(){}
    
    bool operator==(const Coordinates &coordinates){
      return fabs(this->x_ - coordinates.x_) < 1e-7f && fabs(this->y_ - coordinates.y_) < 1e-7f;
    }
};
//----------------
#endif
