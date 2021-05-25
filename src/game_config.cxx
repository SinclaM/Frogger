#include "game_config.hxx"

Game_config::Game_config()
        : scene_dims(692, 720),
          frog_dims(42, 42),
          hop_dist(46, 45),
          start(346, 632),
          lifetime(60),
          hop_time(7.0 / 60),
          car_dims(75, 50),
          row_velocities{50, 50, 50},
          car_rows{5, 5, 5, 5, 5},
          kill_zone(0, 0, 692, 356),
          reset_wait_time(45.0 / 60)
{ }

bool
Game_config::in_scene(Game_config::Position const pos) const
{
    return pos.x >= 0 && pos.x <= scene_dims.width &&
           pos.y >= 0 && pos.y <= scene_dims.height;
}

bool
Game_config::in_scene(Game_config::Rectangle const rect) const
{
    return in_scene(rect.top_left()) && in_scene(rect.bottom_left()) &&
           in_scene(rect.top_right()) && in_scene(rect.bottom_right());
}

int
Game_config::row_velocity(const int row) const
{
    return row_velocities.at(row);
}


