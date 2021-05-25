#include "model.hxx"
#include <iostream>

Model::Model(Game_config const& config)
        : frog_(config),
          life_clock_(config.lifetime, false),
          hop_clock_(config.hop_time, false),
          kill_zone_(config.kill_zone),
          reset_clock_(config.reset_wait_time, true),
          config(config)
{ }

void
Model::on_frame(double dt)
{
    hop_clock_.dec(dt);
    reset_clock_.dec(dt);

    // check if frog is in kill_zone
    if(frog_.hits(kill_zone_)){
        frog_.alive = false;
        reset_clock_.resume();
        if(reset_clock_.time() == 0){
            reset_frog();
        }
    }

    // TODO: Simulation of cars, turtles, logs, etc. moving
    move_coasters();
}

void
Model::reset_frog()
{
    frog_.move_to(config.start.left_by(config.frog_dims.width / 2), config);
    life_clock_.reset();
    reset_clock_.reset();
    reset_clock_.pause();
    frog_.alive = true;
}

void
Model::move_frog(Model::Direction dir)
{
    if(hop_clock_.time() == 0) {
        frog_.move(dir, config);
        hop_clock_.reset();
    }
}

Frog
Model::frog() const
{
    return frog_;
}

void
Model::move_coasters()
{
    for (auto& vec : coasters_)
    {
        for (auto& obj : vec)
        {
            obj.move(config);
        }
    }
}

Model::coaster_matrix
Model::get_coasters() const
{
    return coasters_;
}
