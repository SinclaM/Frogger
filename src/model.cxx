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
          turtles_submersed(config.turtle_sumbersed_for + config
          .turtle_sumberged_time, false)
{

    /// Add car coasters //////////////////////////////////////////////////////
    /*
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
     */
    ///////////////////////////////////////////////////////////////////////////
    initialize_coaster(std::vector<int> {0, 1, 2, 3, 4},
                       coaster::object_type::car,
                       config
    .car_dims);

    initialize_coaster(std::vector<int> {7},
                       coaster::object_type::short_log,
                       config.short_log_dims);

    initialize_coaster(std::vector<int> {8},
                       coaster::object_type::long_log,
                       config.long_log_dims);

    initialize_coaster(std::vector<int> {10},
                       coaster::object_type::medium_log,
                       config.medium_log_dims);

    initialize_coaster(std::vector<int> {6}, coaster::object_type::passive_turtle,
                       config.three_turtle_dims);

    initialize_coaster(std::vector<int> {9}, coaster::object_type::passive_turtle,
                       config.two_turtle_dims);
}

void
Model::on_frame(double dt)
{
    // update the clocks
    if (turtles_submersed.time() == 0)
    {
        turtles_submersed.reset();
        turtle_torpedo.resume();
        turtle_timer.resume();
    }
    turtle_torpedo.dec(dt);
    turtle_timer.dec(dt);
    hop_clock_.dec(dt);
    reset_clock_.dec(dt);
    turtles_submersed.dec(dt);


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

    // submerges the turtles
    if (turtles_submersed.time() == 0)
    {
        turtles_submerge(coasters_);
    }
    else if (turtle_timer.time() == 0)
    {
        turtles_submerge(coasters_);
        turtle_timer.reset();
        turtle_timer.pause();
    }
    else if (turtle_torpedo.time() == 0)
    {
        turtles_submerge(coasters_);
        turtle_torpedo.reset();
        turtle_torpedo.pause();
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

void
Model::initialize_coaster(
        std::vector<int> rows_to_initialize,
        coaster::object_type obj_type,
        Dimension type_dimensions)
{
    std::vector<coaster> vec0;
    // learned how to use rand from https://www.cplusplus
    // .com/reference/cstdlib/rand/

    srand(time(NULL));
    int rand_num;
    for(auto row_num : rows_to_initialize)
    {
        for (int ct = 0; ct < config.coaster_rows.at(size_t(row_num)); ct++) {
            rand_num = rand() % 4000 + 1000;
            if (obj_type == coaster::passive_turtle && ct%2 == 0 && ct != 0)
            {
                vec0.push_back(
                        coaster(config, coaster::turtle,
                                row_num,
                                {(config.scene_dims.width * ct / (config
                                .coaster_rows.at(size_t(row_num)) -1))
                                 + rand_num / type_dimensions.width ,
                                 config.scene_dims.height - (3 + row_num) *
                                 45 + config.hop_dist.height/4}));
            }
            else {

                vec0.push_back(
                        coaster(config,
                                obj_type,
                                row_num,
                                {(config.scene_dims.width * ct / (config
                                .coaster_rows.at(size_t(row_num)) - 1))
                                 + rand_num / type_dimensions.width,
                                 config.scene_dims.height - (3 + row_num) *
                                 45 + config.hop_dist.height / 4}));
            }
        }
        coasters_.push_back(vec0);
        vec0 = {};
        row_num++;
    }
}

void
Model::turtles_submerge(coaster_matrix& matrix)
{
    for (auto& vec : matrix){

        for (auto& obj : vec)
        {
            std::cout << obj.coaster_type();
            obj.submerge_turtle();
            std::cout << obj.coaster_type() << "\n";
        }
    }
}