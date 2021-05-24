#include "interactive_object.hxx"

Interactive_object::Interactive_object(const Game_config& config, object_type
type, int row_num, Position start_pos)
        : body_{start_pos.x, start_pos.y, config.car_dims.width,
                config.car_dims.height},
          type_(type),
          row_(row_num),
          velocity_(config.row_velocity(row_num)),
          hostile_(type > turtle)
{ }

void Interactive_object::move_to(int x_pos, const Game_config& config)
{
    if(config.in_scene({x_pos, body_.center().y}))
    {
        body_.x = x_pos + body_.width / 2;
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

void Interactive_object::move(const Game_config& config)
{
    move_to(body_.center().x + velocity_, config);
}

