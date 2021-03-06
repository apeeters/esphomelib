//
//  template_cover.cpp
//  esphomelib
//
//  Created by Otto Winter on 20.05.18.
//  Copyright © 2018 Otto Winter. All rights reserved.
//

#include "esphomelib/defines.h"

#ifdef USE_TEMPLATE_COVER

#include "esphomelib/cover/template_cover.h"

ESPHOMELIB_NAMESPACE_BEGIN

namespace cover {

TemplateCover::TemplateCover(const std::string &name)
    : Cover(name), open_trigger_(new Trigger<NoArg>()), close_trigger_(new Trigger<NoArg>),
      stop_trigger_(new Trigger<NoArg>()) {

}
void TemplateCover::open() {
  if (this->optimistic_)
    this->publish_state(COVER_OPEN);
  this->open_trigger_->trigger();
}
void TemplateCover::close() {
  if (this->optimistic_)
    this->publish_state(COVER_CLOSED);
  this->close_trigger_->trigger();
}
void TemplateCover::stop() {
  this->stop_trigger_->trigger();
}
void TemplateCover::loop() {
  if (this->f_.has_value()) {
    auto s = (*this->f_)();
    if (s.has_value())
      this->publish_state(*s);
  }
}
void TemplateCover::set_optimistic(bool optimistic) {
  this->optimistic_ = optimistic;
}
bool TemplateCover::optimistic() {
  return this->optimistic_;
}
void TemplateCover::set_state_lambda(std::function<optional<CoverState>()> &&f) {
  this->f_ = f;
}
float TemplateCover::get_setup_priority() const {
  return setup_priority::HARDWARE;
}
Trigger<NoArg> *TemplateCover::get_open_trigger() const {
  return this->open_trigger_;
}
Trigger<NoArg> *TemplateCover::get_close_trigger() const {
  return this->close_trigger_;
}
Trigger<NoArg> *TemplateCover::get_stop_trigger() const {
  return this->stop_trigger_;
}

} // namespace cover

ESPHOMELIB_NAMESPACE_END

#endif //USE_TEMPLATE_COVER
