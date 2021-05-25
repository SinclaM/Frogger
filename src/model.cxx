#include "model.hxx"

Model::Model(Game_config const& config)
        : frog_(config),
          time_left_(config.lifetime),
          cool_down(config.hop_time),
          frame_counter(0),
          config(config)

{
    vector<coaster> vec0;
    int row_num = 0;

    //learned how to use rand from https://www.cplusplus
    // .com/reference/cstdlib/rand/
    srand(time(NULL));
    int rand_num;
    for(size_t row = 0; row < config.car_rows.size(); row++)
    {
        for (int ct = 0; ct < config.car_rows.at(row); ct++) {
            rand_num = rand() % 100;
            vec0.push_back(coaster(config,
                       coaster::object_type::car,
                       row_num, {(config.scene_dims.width - config.car_dims
                       .width) * ct / 4 +
                       rand_num,
                             config.scene_dims.height - (3 + row_num) * 45 +
                             config.hop_dist.height/4}));


        }
        coaster_.push_back(vec0);
        vec0 = {};
        row_num++;
    }
}

void
Model::on_frame(double dt)
{
    frame_counter++;
    if(cool_down > 0){
        // Have to make sure subtracted dt will not make cool_down less
        // than zero
        if(cool_down > dt){
            cool_down -= dt;
        }else{
            cool_down = 0;
        }
    }
    // TODO: Simulation of cars, turtles, logs, etc. moving


    move_coasters(coaster_);


    if (frame_counter == 100)
    {
        frame_counter = 0;
    }
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

void
Model::move_coasters(std::vector<std::vector<coaster>> &
interactive_vec)
{
    if (frame_counter%4 == 0) {
        for (auto& vec : interactive_vec) {
            for (auto& obj : vec) {
                obj.move(config);

            }

        }
    }

}

vector<vector<coaster>>
Model::get_coaster() const
{
    return coaster_;
}





