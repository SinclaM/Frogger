#include "model.hxx"
#include <iostream>

Model::Model(Game_config const& config)
        : frog_(config),
          time_left_(config.lifetime),
          cool_down_(config.hop_time),
          kill_zone_(config.kill_zone),
          time_to_reset_(config.reset_wait_time),
          config(config)
{ }

void
Model::on_frame(double dt)
{
    // update cool_down if, necessary
    if(cool_down_ > 0){
        // Have to make sure subtracted dt will not make cool_down less
        // than zero
        if(cool_down_ > dt){
            cool_down_ -= dt;
        }else{
            cool_down_ = 0;
        }
    }

    // update time_to_reset if, necessary
    if(!frog_.alive && time_to_reset_ > 0){
        if(time_to_reset_ > dt){
            time_to_reset_ -= dt;
        }else{
            time_to_reset_ = 0;
        }
    }

    // check if frog is in kill_zone
    if(frog_.hits(kill_zone_)){
        frog_.alive = false;
        if(time_to_reset_ == 0) {
            reset_frog();
        }
    }

    // TODO: Simulation of cars, turtles, logs, etc. moving
}

void
Model::reset_frog()
{
    frog_.move_to(config.start.left_by(config.frog_dims.width / 2), config);
    time_left_ = config.lifetime;
    time_to_reset_ = config.reset_wait_time;
    frog_.alive = true;
}

void
Model::move_frog(Model::Direction dir)
{
    if(cool_down_ == 0) {
        frog_.move(dir, config);
        cool_down_ = config.hop_time;
    }
}

Frog
Model::frog() const
{
    return frog_;
}
