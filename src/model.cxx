#include "model.hxx"

Model::Model(Game_config const& config)
        : frog_(config),
          time_left_(config.lifetime),
          cool_down_(config.hop_time),
          config(config)
{

}

void
Model::on_frame(double dt)
{
    if(cool_down_ > 0){
        // Have to make sure subtracted dt will not make cool_down less
        // than zero
        if(cool_down_ > dt){
            cool_down_ -= dt;
        }else{
            cool_down_ = 0;
        }
    }
    // TODO: Simulation of cars, turtles, logs, etc. moving
    move_coasters();
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





