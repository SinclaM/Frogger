#include "frog.hxx"

Frog::Frog(Game_config const& config)
        : body_{config.start.x, config.start.y,
                config.frog_dims.width, config.frog_dims.height},
          hop_dist_(config.hop_dist),
          facing_{0, -1}
{ }

void
Frog::move(Frog::Direction dir, Game_config const& config)
{
    if(move_to({body_.x + hop_dist_ * dir.width,
                    body_.y + hop_dist_ * dir.height},
               config)){
        facing_ = dir;
    }
}

bool
Frog::move_to(Frog::Position pos, Game_config const& config)
{
    if(config.in_scene(pos) &&
            config.in_scene(pos.down_right_by(config.frog_dims))) {
        body_.x = pos.x;
        body_.y = pos.y;
        return true;
    }
    return false;
}

Frog::Position
Frog::top_left() const
{
    return body_.top_left();
}

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
