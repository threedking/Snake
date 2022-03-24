#include "Camera.h"
#include "World.h"


//Camera::Camera(unsigned int new_limit_x, unsigned int new_limit_y, Coordinates<dimension_type>* new_target):limit_x_(new_limit_x), limit_y_(new_limit_y), target_(new_target){}
Camera::Camera(Coordinates<dimension_type> new_limits, Coordinates<dimension_type>* new_target): limits(new_limits), target_(new_target){
  this->limits.x_ = this->limits.x_ >= 1 ? this->limits.x_ : 1;
  this->limits.y_ = this->limits.y_ >= 1 ? this->limits.y_ : 1;
  this->FindFocus();
  this->GoToTarget();
}
  
void Camera::Tick(){
  
  if(this->target_->x_ < this->offset_.x_ + this->focus_[0].x_){
    this->offset_.x_ -= this->speed_;
  }else if(this->target_->x_ > this->offset_.x_ + this->focus_[1].x_){
    this->offset_.x_ += this->speed_;
  }
  if(this->target_->y_ > this->offset_.y_ + this->focus_[0].y_){
    this->offset_.y_ += this->speed_;
  }else if(this->target_->y_ < this->offset_.y_ + this->focus_[1].y_){
    this->offset_.y_ -= this->speed_;
  }

}

void Camera::GoToTarget(){
  this->offset_.x_ = this->target_->x_;
  this->offset_.y_ = this->target_->y_;
}

void Camera::FindFocus(){
  this->focus_[0].x_ = 0 - this->limits.x_ / 2;
  this->focus_[0].y_ = 0 - this->limits.y_ / 2;
  this->focus_[1].x_ = this->focus_[0].x_ + this->limits.x_;
  this->focus_[1].y_ = this->focus_[0].y_ + this->limits.y_;
}
Coordinates<dimension_type> Camera::GetOffset(){
  return this->offset_;
}
