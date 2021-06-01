#include "game_config.hxx"

Game_config::Game_config()
        : scene_dims(692, 720),
          frog_dims(32, 24),
          hop_dist(46, 45),
          start(346, 639),
          lifetime(30),
          hop_time(7.0 / 60),
          kill_zone(0, 0, 692, 356),
          reset_wait_time(45.0 / 60),
          row_velocities{-30, 30, -30, 70, -50, 0, -40, 50, 80, -50, 30},
          coaster_rows{3, 3, 3, 1, 2, 0, 4, 3, 3, 4, 5},
          turtle_sumberged_time(10),
          turtle_submerging_time(7),
          turtle_sumbersed_for(3),
          bottom_lane_y(595),
          spacings{200, 200, 200, 200, 400, 0, 200, 200, 400, 200, 200},
          random_deviation_range(30),
          coaster_small(32, 32),
          coaster_medium(64, 32),
          coaster_long(96, 32),
          coaster_longest(128, 32),
          home_dims(50, 45),
          home_locations{{47, 88}, {182, 88}, {320, 88},
                         {457, 88}, {595, 88}},
          forward_step_points(10),
          lilly_pad_points(200),
          frog_starting_lives(3),
          shift_min(25),
          shift_max(100),
          frog_collision_fraction(0.3),
          end_game_background_fade_loss(0,0,0, 200),
          end_game_background_fade_win(0, 63, 0, 200),
          leftmost_life_pos(8, 40),
          life_spacing(36),
          score_pos(620, 20),
          velocity_gain(5),
          timer_rec(173, 680, 346, 28),
          timer_color(20, 100, 80),
          small_font_size(25),
          large_font_size(50)
{ }

bool
Game_config::in_scene(Game_config::Position const pos) const
{
    return pos.x >= 0 && pos.x <= scene_dims.width &&
           pos.y >= 0 && pos.y <= scene_dims.height - hop_dist.height;
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
