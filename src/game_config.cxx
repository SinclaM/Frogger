#include "game_config.hxx"

Game_config::Game_config()
        : scene_dims(692, 720),
          frog_dims(42, 42),
          hop_dist(46, 45),
          start(346, 632),
          lifetime(60),
          hop_time(7.0 / 60),
          car_dims(64, 32),
          row_velocities{-30, 30, -50, 70, -60},
          car_rows{3, 3, 3, 1, 2},
          kill_zone(0, 0, 692, 356),
          reset_wait_time(45.0 / 60),
          bottom_lane_y(595),
          spacings{200, 200, 200, 200, 400},
          random_deviation_range(10),
          coaster_small(32, 32),
          coaster_medium(64, 32),
          coaster_long(96, 64),
          coaster_longest(128, 64)
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
Game_config::row_velocity(int const row) const
{
    return row_velocities.at(row);
}

bool
Game_config::in_object_scene(Position const pos) const
{
    return pos.x >= -150 && pos.x - 300 <= scene_dims.width &&
           pos.y >= 0 && pos.y <= scene_dims.height;
}


