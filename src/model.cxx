#include "model.hxx"
#include <iostream>

Model::Model(Game_config const& config)
        : frog_(config),
          life_clock_(config.lifetime, false),
          hop_clock_(config.hop_time, false),
          kill_zone_(config.kill_zone),
          reset_clock_(config.reset_wait_time, true),
          config(config),
          turtle_timer(config.turtle_sumberged_time, false),
          turtle_torpedo(config.turtle_submerging_time, false),
          turtles_submersed(config.turtle_sumbersed_for +
                            config.turtle_sumberged_time,
                            false)
{
    ge211::Random_source<int> deviation(-config.random_deviation_range,
                                        config.random_deviation_range);
    ge211::Random_source<int> initial(25, 100);
    for(size_t i = 0; i < config.coaster_rows.size(); i++) {
        std::vector<Coaster> vec;
        for (size_t j = 0; j < config.coaster_rows[i]; j++) {
            int x_step = config.spacings[i];
            int y_step = config.hop_dist.height + 1;
            Position pos(initial.next() + x_step * j + deviation.next(),
                         config.bottom_lane_y - y_step * i);
            vec.push_back(Coaster(config, i, pos));
        }
        coasters_.push_back(vec);
    }
}

void
Model::on_frame(double dt)
{
    hop_clock_.dec(dt);
    reset_clock_.dec(dt);

    move_coasters(dt, coasters_);

    // check collision with cars
    for(auto vec : coasters_){
        for(auto coaster : vec){
            if(frog_.hits(coaster.body()) && coaster.is_hostile()){
                frog_.alive = false;
                reset_clock_.resume();
            }
        }
    }

    const Coaster* cstrp = frog_on_platform();
    // check if frog is in kill_zone and not on moving platform
    if(frog_.hits(kill_zone_) && cstrp == nullptr){
        frog_.alive = false;
        reset_clock_.resume();
    }

    // move frog, if it's on a platform
    if(cstrp != nullptr){
        auto coaster = *cstrp;
        frog_.move_with(coaster, dt);
    }

    // reset the frog, if necessary
    if(reset_clock_.time() == 0){
        reset_frog();
    }
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
    if(hop_clock_.time() == 0){
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
Model::move_coasters(double const dt, Model::Coaster_matrix& matrix)
{
    for(auto& vec : matrix){
        for(auto& obj : vec){
            obj.move(dt, config);
        }
    }
}

Model::Coaster_matrix
Model::get_coasters() const
{
    return coasters_;
}

void
Model::turtles_submerge(Coaster_matrix& matrix)
{

}

const Coaster*
Model::frog_on_platform() const
{
    for(auto& vec : coasters_){
        for(auto& coaster : vec){
            if(frog_.hits(coaster.body()) && !coaster.is_hostile()){
                return &coaster;
            }
        }
    }
    return nullptr;
}


