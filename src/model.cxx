#include "model.hxx"

Model::Model(Game_config const& config)
        : config(config),
          frog_(config),
          time_left_(config.lifetime),
          cool_down(config.hop_time)
{ }

void
Model::on_frame(double dt)
{
    if(cool_down > 0){
        cool_down--;
    }
    // TODO: Simulation of cars, turtles, logs, etc. moving
}

void
Model::reset_frog()
{
    frog_.move_to(config.start.down_right_by({config.frog_dims.width,
                                               config.frog_dims.height}),
                  config);
    time_left_ = config.lifetime;
}

void
Model::move_frog(Model::Direction dir)
{
    if(cool_down == 0) {
        frog_.move(dir, config);
        cool_down = config.hop_time;
    }
}

Frog
Model::frog() const
{
    return frog_;
}



