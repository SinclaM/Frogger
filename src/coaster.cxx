#include "coaster.hxx"

#include <iostream>

coaster::coaster(const Game_config& config, object_type
type, int row_num, Position start_pos)
        : body_{start_pos.x, start_pos.y, config.car_dims.width,
                config.car_dims.height},
          x_(start_pos.x),
          type_(type),
          row_(row_num),
          velocity_(config.row_velocity(row_num)),
          hostile_(type > passive_turtle)
{ }

void coaster::move_to(int x_pos, const Game_config& config)
{
    if(config.in_object_scene({x_pos, body_.center().y})){
        body_.x = x_pos;
    }
    else{
        if(velocity_ < 0){
            body_.x = config.scene_dims.width - body_.width;
            x_ = body_.x;
        }else if(velocity_ > 0){
            body_.x = 0;
            x_ = body_.x;
        }
    }
}

void coaster::move(double const dt, const Game_config& config)
{
    x_ += dt * velocity_;
    body_.x = x_;
    move_to(x_, config);
}

coaster::Position
coaster::coaster_pos() const
{
    return {body_.x, body_.y};
}

coaster::Rectangle
coaster::body() const
{
    return body_;
}

bool
coaster::is_hostile() const
{
    return hostile_;
}

coaster::object_type&
coaster::coaster_type()
{
    return type_;
}

void
coaster::submerge_turtle()
{
    if (type_ == coaster::submerged_turtle)
    {
        type_ = coaster::turtle;
    }
    else if (type_ == coaster::submerging_turtle)
    {
        type_ = coaster::submerged_turtle;
    }
    else if (type_ == coaster::turtle)
    {
        type_ = coaster::submerging_turtle;
    }
}

int
coaster::get_row()
{
    return row_;
}
