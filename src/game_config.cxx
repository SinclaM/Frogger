#include "game_config.hxx"

Game_config::Game_config()
        : scene_dims{692, 720},
          frog_dims{42, 42},
          hop_dist{46, 45},
          start{346, 632},
          lifetime(60),
          hop_time(7),
          car_dims{65, 20},
          row_velocities{-1, -3, -1, -2, -4},
          car_rows{4, 2, 4, 4, 3}
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

bool
Game_config::in_object_scene(const Position pos) const
{
    return pos.x >= -150 && pos.x - 300 <= scene_dims.width &&
           pos.y >= 0 && pos.y <= scene_dims.height;
}


