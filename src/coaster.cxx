#include "coaster.hxx"

#include <iostream>

Coaster::Coaster(const Game_config& config, int row_num, object_type
type, Position start_pos)
        : x_(start_pos.x),
          type_(type),
          row_(row_num),
          velocity_(config.row_velocity(row_num)),
          hostile_(false)
{
    Dimension body_dims;
    if(row_num < Game_config::truck_row) {
        hostile_ = true;
        body_dims = config.coaster_small;
    }else if(row_num == Game_config::truck_row){
        hostile_ = true;
        body_dims = config.coaster_medium;
    }else if(row_num == Game_config::small_log_row ||
             row_num == Game_config::two_turtles_row){
        body_dims = config.coaster_medium;
    }else if(row_num == Game_config::three_turtles_row ||
             row_num == Game_config::medium_log_row ){
        body_dims = config.coaster_long;
    }else if(row_num == Game_config::long_log_row){
        body_dims = config.coaster_longest;
    }else{
        std::cerr << row_num << " is not valid" << std::endl;
        throw std::invalid_argument("Invalid row number");
    }
    body_ = {start_pos.x, start_pos.y, body_dims.width, body_dims.height};
}

Coaster::Coaster(Game_config const& config, int row_num, Position pos)
        : Coaster(config, row_num, other, pos)
{ }

Coaster::Position
Coaster::coaster_pos() const
{
    return {body_.x, body_.y};
}

Coaster::Rectangle
Coaster::body() const
{
    return body_;
}

double
Coaster::dx(double const dt) const
{
    return dt * velocity_;
}

int
Coaster::row() const
{
    return row_;
}

int
Coaster::velocity() const
{
    return velocity_;
}

bool
Coaster::is_hostile() const
{
    return hostile_;
}

void Coaster::move_to(int x_pos, const Game_config& config)
{
    if(config.in_object_scene({x_pos, body_.center().y})){
        body_.x = x_pos;
    }
    else{
        if(velocity_ < 0){
            body_.x = config.scene_dims.width;
            x_ = body_.x;
        }else if(velocity_ > 0){
            body_.x = -body_.width;
            x_ = body_.x;
        }
    }
}

void Coaster::move(double const dt, const Game_config& config)
{
    x_ += dt * velocity_;
    body_.x = x_;
    move_to(x_, config);
}

void
Coaster::submerge_turtle()
{
    if(type_ == Coaster::submerged_turtle){
        type_ = Coaster::turtle;
        hostile_ = false;
    }else if (type_ == Coaster::submerging_turtle){
        type_ = Coaster::submerged_turtle;
        hostile_ = true;
    }else if (type_ == Coaster::turtle){
        type_ = Coaster::submerging_turtle;
    }
}

void
Coaster::inc_speed(int dv)
{
    velocity_ > 0 ? velocity_ += dv
                  :  velocity_ -= dv;
}

Coaster::object_type
Coaster::type()
{
    return type_;
}


