#include "frog.hxx"


Frog::Frog(Game_config const& config)
        : body_{config.start.x - config.frog_dims.width / 2, config.start.y,
                config.frog_dims.width, config.frog_dims.height},
          hop_dist_(config.hop_dist),
          facing_{0, -1},
          alive(true)
{ }

void
Frog::move(Frog::Direction dir, Game_config const& config)
{
    if(alive) {
        if (move_to(body_.top_left() + dir * hop_dist_,
                    config)) {
            facing_ = dir;
        }
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
