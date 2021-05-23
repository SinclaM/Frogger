#include "frog.hxx"

Frog::Frog(Game_config const& config)
        : body_{config.start.x, config.start.y,
                config.frog_dims.width, config.frog_dims.height},
          hop_dist_(config.hop_dist)
{ }

void
Frog::move(Frog::Direction dir, Game_config const& config)
{
    // TODO: fix this broken mess
    if(body_.x + hop_dist_ * dir.width >= 0 &&
            body_.x + 2 * config.frog_dims.width + hop_dist_ * dir.width <
                                                    config.scene_dims.width &&
            body_.y + hop_dist_ * dir.height >= 0 &&
            body_.y + 2 * config.frog_dims.height + hop_dist_ * dir.height <
                                                    config.scene_dims.height){
        body_.x += hop_dist_ * dir.width;
        body_.y += hop_dist_ * dir.height;
    }
}

void
Frog::move_to(Frog::Position pos, Game_config const& config)
{
    body_.x = pos.x - body_.width / 2;
    body_.y = pos.y - body_.height / 2;
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
