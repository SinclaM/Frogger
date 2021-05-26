#include "model.hxx"
#include <iostream>

Model::Model(Game_config const& config)
        : frog_(config),
          life_clock_(config.lifetime, false),
          hop_clock_(config.hop_time, false),
          kill_zone_(config.kill_zone),
          reset_clock_(config.reset_wait_time, true),
          config(config)
{
    std::vector<coaster> vec0;
    int row_num = 0;

    // learned how to use rand from https://www.cplusplus
    // .com/reference/cstdlib/rand/
    srand(time(NULL));
    int rand_num;
    for(size_t row = 0; row < config.car_rows.size(); row++)
    {
        for (int ct = 0; ct < config.car_rows.at(row); ct++) {
            rand_num = rand() % 100;
            vec0.push_back(
                coaster(config,
                        coaster::object_type::car,
                        row_num,
                        {(config.scene_dims.width - config.car_dims.width)
                                * ct / 4 + rand_num,
                         config.scene_dims.height - (3 + row_num) * 45 +
                                config.hop_dist.height/4}));
        }
        coasters_.push_back(vec0);
        vec0 = {};
        row_num++;
    }
}

void
Model::on_frame(double dt)
{
    // update the clocks
    hop_clock_.dec(dt);
    reset_clock_.dec(dt);

    move_coasters(dt, coasters_);

    // check if frog is in kill_zone
    if(frog_.hits(kill_zone_)){
        frog_.alive = false;
        reset_clock_.resume();
    }

    // check collision with cars
    for(auto vec : coasters_){
        for(auto coaster : vec){
            if(frog_.hits(coaster.body()) && coaster.is_hostile()){
                frog_.alive = false;
                reset_clock_.resume();
            }
        }
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
Model::move_coasters(double const dt, Model::coaster_matrix& matrix)
{
    for(auto& vec : matrix){
        for(auto& obj : vec){
            obj.move(dt, config);
        }
    }
}

Model::coaster_matrix
Model::get_coasters() const
{
    return coasters_;
}
