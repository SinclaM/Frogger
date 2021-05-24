#include "game_config.hxx"

Game_config::Game_config()
        : scene_dims{1000, 1000},
          frog_dims{50, 50},
          hop_dist(50),
          start{500, 900},
          lifetime(60),
          hop_time(7)
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


