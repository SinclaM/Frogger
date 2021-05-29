#include "coaster.hxx"

#include <iostream>

Coaster::Coaster(const Game_config& config, int row_num, Position start_pos)
        : x_(start_pos.x),
          row_(row_num),
          velocity_(config.row_velocity(row_num)),
          hostile_(false)
{
    Dimension body_dims;
    if(row_num < 4) {
        hostile_ = true;
        body_dims = config.coaster_small;
    }else if(row_num == 4){
        hostile_ = true;
        body_dims = config.coaster_medium;
    }else if(row_num == 7 || row_num == 9){
        body_dims = config.coaster_medium;
    }else if(row_num == 6 || row_num == 10){
        body_dims = config.coaster_long;
    }else if(row_num == 8){
        body_dims = config.coaster_longest;
    }else{
        std::cerr << row_num << " is not valid" << std::endl;
        throw std::invalid_argument("Invalid row number");
    }
    body_ = {start_pos.x, start_pos.y, body_dims.width, body_dims.height};
}

void Coaster::move_to(int x_pos, const Game_config& config)
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

void Coaster::move(double const dt, const Game_config& config)
{
    x_ += dt * velocity_;
    body_.x = x_;
    move_to(x_, config);
}

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

bool
Coaster::is_hostile() const
{
    return hostile_;
}

void
Coaster::submerge_turtle()
{

}

int
Coaster::row() const
{
    return row_;
}

double
Coaster::dx(double const dt) const
{
    return dt * velocity_;
}
