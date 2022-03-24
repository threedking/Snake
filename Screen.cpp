#include "Screen.h"

Screen::Screen(const unsigned int new_limit_x, const unsigned int new_limit_y, Camera* new_camera, World* new_world):limit_x_(new_limit_x), limit_y_(new_limit_y), camera_(new_camera), world_(new_world){
  if(this->limit_x_ > 0 && this->limit_y_ > 0){
    this->pixels = new bool*[this->limit_x_];
    for (int i = 0; i < this->limit_x_; i++){
      this->pixels[i] = new bool[this->limit_y_]{};
    }
    this->view_pixels = this->pixels;
  }
}
Screen::~Screen(){
  for (int i = 0; i < this->limit_x_; i++){
    delete[] this->pixels[i];
  }
  delete[] this->pixels;
  delete[] this->view_pixels;
}
