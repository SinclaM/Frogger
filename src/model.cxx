#include "model.hxx"

Model::Model(Game_config const& config)
        : frog_(config),
          time_left_(config.lifetime),
          cool_down(config.hop_time),
          config(config)
{
    vector<Interactive_object> vec0;
    int row_num = 0;
    int ct_num = 0;
    for(size_t row = 0; row < config.car_rows.size(); row++)
    {
        std::cout << "entered first loop" << endl;
        for (size_t ct = 0; ct_num < config.car_rows.at(row); ct++) {
            std::cout << "entered second loop" << endl;
            vec0.push_back(Interactive_object(config,
                       Interactive_object::object_type::car,
                       row_num, {(config.car_dims.width + 10) * ct_num,
                             config.scene_dims.height - (1 + row_num) * 45}));
            ct_num++;

        }
        interactive_.push_back(vec0);
        vec0.clear();
        row_num++;
        ct_num = 0;
    }
    std::cout << "exited both loops" << endl;

}

void
Model::on_frame(double dt)
{
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
    move_interactive_objects(interactive_);
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
Model::move_interactive_objects(std::vector<std::vector<Interactive_object>>
interactive_vec)
{
    for (auto vec : interactive_vec)
    {
        for (auto obj : vec)
        {
            obj.move(config);
        }
    }
}

vector<vector<Interactive_object>>
Model::get_interactive() const
{
    return interactive_;
}





