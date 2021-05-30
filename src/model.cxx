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
                            false),
          homes_(make_homes(config))
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
            Coaster::object_type type;
            if((i == 6 || i == 9) && j == 0){
                type = Coaster::turtle;
            }else{
                type = Coaster::other;
            }
            vec.push_back(Coaster(config, i, type, pos));
        }
        coasters_.push_back(vec);
    }
}

void
Model::on_frame(double dt)
{
    if(turtles_submersed.time() == 0){
        turtles_submersed.reset();
        turtle_torpedo.resume();
        turtle_timer.resume();
    }
    turtle_torpedo.dec(dt);
    turtle_timer.dec(dt);
    turtles_submersed.dec(dt);
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

    // Check if frog is at an unoccupied home
    Home* homep = frog_touching_home();
    if(homep != nullptr){
        homep->occupy();
        frog_.increment_score_for_lillypad(config);
        reset_frog();
    }


    const Coaster* cstrp = frog_on_platform();

    // check if frog is in kill_zone and not on moving platform
    if(frog_.hits(kill_zone_) && cstrp == nullptr && homep == nullptr){
        frog_.alive = false;
        reset_clock_.resume();
    }

    // move frog, if it's on a platform and alive
    if(cstrp != nullptr && frog_.alive){
        auto coaster = *cstrp;
        frog_.move_with(coaster, dt, config);
    }

    // submerges the turtles
    if (turtles_submersed.time() == 0){
        turtles_submerge();
    }
    else if (turtle_timer.time() == 0){
        turtles_submerge();
        turtle_timer.reset();
        turtle_timer.pause();
    }
    else if (turtle_torpedo.time() == 0){
        turtles_submerge();
        turtle_torpedo.reset();
        turtle_torpedo.pause();
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
Model::turtles_submerge()
{
    for (auto& vec : coasters_){
        for (auto& obj : vec){
            obj.submerge_turtle();
        }
    }
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

Home*
Model::frog_touching_home() const
{
    for(auto& home : homes_){
        if(!home.occupied() && frog_.hits(home.body())){
            return const_cast<Home *>(&home);
        }
    }
    return nullptr;
}

std::vector<Home>
Model::homes() const
{
    return homes_;
}

bool
Model::is_game_over() const
{
    // TODO: add checking for out of lives
    if(all_occupied(homes_)){
        return true;
    }
    return false;
}




