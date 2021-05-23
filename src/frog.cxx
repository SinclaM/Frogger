#include "frog.hxx"

Frog::Frog(Game_config const& config)
        : body_{config.start.x, config.start.y,
                config.frog_dims.width, config.frog_dims.height},
          hop_dist_(config.hop_dist)
{ }

void
Frog::move(Frog::Direction dir, Game_config const& config)
{
    move_to({body_.x + hop_dist_ * dir.width,
                 body_.y + hop_dist_ * dir.height},
            config);
}

void
Frog::move_to(Frog::Position pos, Game_config const& config)
{
    if(config.in_scene(pos) &&
            config.in_scene(pos.down_right_by(config.frog_dims))) {
        body_.x = pos.x;
        body_.y = pos.y;
    }
}

Frog::Position
Frog::top_left() const
{
    return body_.top_left();
}

Frog::Rectangle
Frog::body() const
{
    return body_;
}
