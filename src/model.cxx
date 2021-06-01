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
          homes_(make_homes(config)),
          game_status(true)
{
    ge211::Random_source<int> deviation(-config.random_deviation_range,
                                        config.random_deviation_range);
    ge211::Random_source<int> initial(config.shift_min, config.shift_max);
    for(size_t i = 0; i < config.coaster_rows.size(); i++) {
        std::vector<Coaster> vec;
        int row_shift = initial.next();
        for (size_t j = 0; j < config.coaster_rows[i]; j++) {
            int x_step = config.spacings[i];
            int y_step = config.hop_dist.height + 1;
            Position pos(row_shift + x_step * j + deviation.next(),
                         config.bottom_lane_y - y_step * i);
            Coaster::object_type type;
            if((i == Game_config::three_turtles_row ||
            i == Game_config::two_turtles_row) && j == 0){
                type = Coaster::turtle;
            }else{
                type = Coaster::other;
            }
            vec.push_back(Coaster(config, i, type, pos));
        }
        coasters_.push_back(vec);
    }
}


Model::Model(Coaster_matrix const& coasters, const Game_config& config)
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
          homes_(make_homes(config)),
          game_status(true),
          coasters_(coasters)
{}

void
Model::on_frame(double dt)
{
    // update the clocks
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
    life_clock_.dec(dt);

    move_coasters(dt, coasters_);

    // reset the frog is the life timer has run out
    if(life_clock_.time() == 0){
        on_frog_death();
    }

    // increment the score if frog passes a new highest y value
    frog_.increment_score_for_foward_steps(config);

    // check collision with cars
    for(auto vec : coasters_) {
        for (auto coaster : vec) {
            if (frog_.hits(coaster.body()) && coaster.is_hostile() &&
                frog_.alive) {
                on_frog_death();
            }
        }
    }

    // Check if frog is at an unoccupied home
    Home* homep = frog_touching_home();
    if(homep != nullptr){
        homep->occupy();
        frog_.increment_score_for_lillypad(config);
        reset_frog();
        speed_up(config.velocity_gain);
        if(all_occupied(homes_)){
            life_clock_.pause();
        }
    }


    const Coaster* cstrp = frog_on_platform();

    // check if frog is in kill_zone and not on moving platform
    if(frog_.hits(kill_zone_) && cstrp == nullptr && homep == nullptr &&
    frog_.alive){
        on_frog_death();
    }

    // move frog, if it's on a platform and alive
    if(cstrp != nullptr && frog_.alive){
        auto coaster = *cstrp;
        frog_.move_with(coaster, dt, config);
    }

    // submerges the turtles
    if (turtles_submersed.time() == 0){
        turtles_submerge();
    }else if (turtle_timer.time() == 0){
        turtles_submerge();
        turtle_timer.reset();
        turtle_timer.pause();
    }else if (turtle_torpedo.time() == 0){
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
    reset_clock_.reset();
    reset_clock_.pause();
    life_clock_.reset();
    life_clock_.resume();
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
            if(frog_.stict_hits(coaster.body(), config) &&
                                     !coaster.is_hostile()){
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
        if(!home.occupied() && frog_.stict_hits(home.body(), config)){
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
    if(all_occupied(homes_) || !game_status){
        return true;
    }
    return false;
}

void
Model::speed_up(int dv)
{
    for(auto& vec : coasters_){
        for(auto& coaster : vec){
            coaster.inc_speed(dv);
        }
    }
}

void
Model::on_frog_death()
{
    frog_.alive = false;
    life_clock_.reset();
    life_clock_.pause();
    if (frog_.frog_lives_left() == 0){
        game_status = false;
    }else{
        reset_clock_.resume();
        frog_.decrement_frog_life();
    }
}

Clock
Model::life_clock() const
{
    return life_clock_;
}

void
Model::remove_coasters()
{
    coasters_ = {};
}

void
Model::add_coaster(Coaster coaster)
{
    coasters_.push_back({coaster});
}
