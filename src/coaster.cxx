#include "coaster.hxx"


coaster::coaster(const Game_config& config, object_type
type, int row_num, Position start_pos)
        : body_{start_pos.x, start_pos.y, config.car_dims.width,
                config.car_dims.height},
          type_(type),
          row_(row_num),
          velocity_(config.row_velocity(row_num)),
          hostile_(type > turtle)
{ }

void coaster::move_to(int x_pos, const Game_config& config)
{
    if(config.in_object_scene({x_pos, body_.center().y}))
    {
        body_.x = x_pos;
    }
    else
    {
        if(velocity_ < 0) {
            body_.x = config.scene_dims.width - body_.width;
        }else if(velocity_ > 0){
            body_.x = 0;
        }
    }
}

void coaster::move(const Game_config& config)
{
    move_to(body_.x + velocity_, config);
}

coaster::Position
coaster::coaster_pos() const
{
    return {body_.x, body_.y};
}

