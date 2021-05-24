#include "interactive_object.hxx"

Interactive_object::Interactive_object(const Game_config& config, object_type
type, int row_num, Position start_pos)
        : body_ {start_pos.x, start_pos.y, config.car_dims.width, config
        .car_dims.height},
        type_(type),
        row_(row_num)
{
    velocity = config.row_velocity(row_num);
    if (type > 5)
    {
        hostile_ = true;
    }
    else
    {
        hostile_ = false;
    }
}


void Interactive_object::move(int x_pos, const Game_config& config)
{
    if (config.in_scene({x_pos, body_.center().y}))
    {
        body_.center().x = x_pos;
    }
    else
    {
        body_.x = config.scene_dims.width - body_.width;
    }
}

vooid Interactive_object::move_to(const Game_config&)
{
    move(body_.center().x + velocity_);
}

