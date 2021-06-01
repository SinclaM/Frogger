#include "game_config.hxx"

// ----------------------------------------------------------------------
// These are the configuration constants, which must be defined as global
// constants to make GSC happy about magic numbers. Frankly, it is redundant
// and ugly, but this is how GSC wants it.
Game_config::Dimension const s_dims(692, 720);
Game_config::Dimension const f_dims(32, 24);
Game_config::Dimension const h_dist(46, 45);
Game_config::Dimension const c_small(32, 32);
Game_config::Dimension const c_medium(64, 32);
Game_config::Dimension const c_long(96, 32);
Game_config::Dimension const c_longest(128, 32);
Game_config::Dimension const h_dims(50, 45);
Game_config::Position const st_pos(346, 639);
Game_config::Rectangle const k_zone(0, 0, 692, 356);
double const l_time = 30;
double const h_time = 7.0 / 60;
double const rw_time = 45.0 / 60;
double const tsed_time = 10;
double const tsing_time = 3;
double const ts_for = 3;
double const fc_fraction = 0.3;
int const bl_y = 595;
int const rd_range = 30;
int const fs_points = 10;
int const lp_points = 200;
int const fs_lives = 3;
int const s_min = 25;
int const s_max = 100;
int const v_gain = 5;
std::vector<int> const r_velocities{-30, 30, -30, 70, -50, 0,
                                    -40, 50, 80, -50, 30};
std::vector<int> const c_rows{3, 3, 3, 1, 2, 0, 4, 3, 3, 4, 5};
std::vector<int> const spac_vec{200, 200, 200, 200, 400, 0, 200, 200, 400,
                                200, 200};
std::vector<Game_config::Position> const h_locations{{47, 88},
         {182, 88}, {320, 88},{457, 88},{595, 88}};
Game_config::Position const sc_pos(620, 20);
Game_config::Position const ll_pos(8, 40);
Game_config::Rectangle const t_rec(173, 680, 346, 28);
int const l_spacing = 36;
int const sf_size = 25;
int const lf_size = 50;
int const left_wrap_boundary = -150;
int const right_wrap_boundary = 300;
ge211::Color const egbf_loss(0, 0, 0, 200);
ge211::Color const egbf_win(0, 63, 0, 200);
ge211::Color const t_color(20, 100, 80);
// ---------------------------------------------------------------------

Game_config::Game_config()
        : scene_dims(s_dims),
          frog_dims(f_dims),
          hop_dist(h_dist),
          coaster_small(c_small),
          coaster_medium(c_medium),
          coaster_long(c_long),
          coaster_longest(c_longest),
          home_dims(h_dims),
          start(st_pos),
          kill_zone(k_zone),
          lifetime(l_time),
          hop_time(h_time),
          reset_wait_time(rw_time),
          turtle_sumberged_time(tsed_time),
          turtle_submerging_time(tsing_time),
          turtle_sumbersed_for(ts_for),
          frog_collision_fraction(fc_fraction),
          bottom_lane_y(bl_y),
          random_deviation_range(rd_range),
          forward_step_points(fs_points),
          lilly_pad_points(lp_points),
          frog_starting_lives(fs_lives),
          shift_min(s_min),
          shift_max(s_max),
          velocity_gain(v_gain),
          row_velocities(r_velocities),
          coaster_rows(c_rows),
          spacings(spac_vec),
          home_locations(h_locations),
          score_pos(sc_pos),
          leftmost_life_pos(ll_pos),
          timer_rec(t_rec),
          life_spacing(l_spacing),
          small_font_size(sf_size),
          large_font_size(lf_size),
          end_game_background_fade_loss(egbf_loss),
          end_game_background_fade_win(egbf_win),
          timer_color(t_color)
{ }

int
Game_config::row_velocity(int const row) const
{
    return row_velocities.at(row);
}

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

bool
Game_config::in_object_scene(Position const pos) const
{
    return pos.x >= left_wrap_boundary && 
           pos.x - right_wrap_boundary <= scene_dims.width &&
           pos.y >= 0 && pos.y <= scene_dims.height;
}
