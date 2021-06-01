#include "frog.hxx"

Frog::Frog(Game_config const& config)
        : alive(true),
          facing_(0, -1),
          hop_dist_(config.hop_dist),
          body_(config.start.x - config.frog_dims.width / 2, config.start.y,
                config.frog_dims.width, config.frog_dims.height),
          x_(config.start.x),
          score_(0),
          highest_y_pos(config.start.y),
          lives_(config.frog_starting_lives)
{ }

Frog::Direction
Frog::facing() const
{
    return facing_;
}

Frog::Rectangle
Frog::body() const
{
    return body_;
}

int
Frog::get_frog_score()
{
    return score_;
}

int
Frog::frog_lives_left()
{
    return lives_;
}

bool
Frog::move_to(Frog::Position pos, Game_config const& config)
{
    if(config.in_scene(pos) &&
       config.in_scene(pos.down_right_by(config.frog_dims))) {
        body_.x = pos.x;
        x_ = pos.x;
        body_.y = pos.y;
        return true;
    }
    return false;
}

void
Frog::move(Frog::Direction dir, Game_config const& config)
{
    if(alive){
        if (move_to(body_.top_left() + dir * hop_dist_,
                    config)) {
            facing_ = dir;
        }
    }
}

bool
Frog::hits(Frog::Rectangle const rec) const
{
    if(body_.y > rec.bottom_right().y || body_.bottom_right().y < rec.y){
        return false;
    }else if(body_.bottom_right().x < rec.x || body_.x > rec.bottom_right().x){
        return false;
    }
    return true;
}

bool
Frog::stict_hits(Frog::Rectangle const rec, Game_config const& config) const
{
    Position new_tl(rec.top_left().right_by(
                            body_.width * config.frog_collision_fraction));
    Dimesion new_dims(rec.width -
                 2 * config.frog_collision_fraction * body_.width, rec.height);
    Rectangle squished_rec(new_tl.x, new_tl.y,
                           new_dims.width, new_dims.height);
    return hits(squished_rec);
}

void
Frog::move_with(Coaster const coaster, double const dt,
                Game_config const& config)
{
    auto dx = coaster.dx(dt);
    if(config.in_scene({static_cast<int>(x_ + dx), body_.y,
                        body_.width, body_.height})) {
        x_ += coaster.dx(dt);
        body_.x = x_;
        increment_score_for_foward_steps(config);
    }
}

void
Frog::increment_score_for_foward_steps(Game_config const& config)
{
    if (body_.y < highest_y_pos)
    {
        increment_score(config.forward_step_points);
        highest_y_pos = body_.y;
    }
}

void
Frog::increment_score_for_lillypad(const Game_config& config)
{
    increment_score(config.lilly_pad_points);
    highest_y_pos = config.start.y;
}

void
Frog::decrement_frog_life()
{
    lives_--;
}

void
Frog::increment_score(int increment)
{
    score_ += increment;
}