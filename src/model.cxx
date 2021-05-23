#include "model.hxx"

Model::Model(Game_config const& config)
        : config_(config),
          frog_(config),
          time_left_(config.lifetime)
{ }

void
Model::on_frame(double dt)
{
    // TODO: Simulation of cars, turtles, logs, etc. moving
}

void
Model::reset_frog()
{
    frog_.move_to(config_.start, config_);
    time_left_ = config_.lifetime;
}

void
Model::move_frog(Model::Direction dir)
{
    frog_.move(dir, config_);
}

Model::Position
Model::frog_position() const
{
    return frog_.top_left();
}



