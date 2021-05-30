#include "view.hxx"

static int background_layer = 0; // background scenery
static int surface_layer = 1; // water, scoring, timer, life count
static int coaster_layer = 2; // cars, turtles, logs
static int frog_layer = 3; // frog

ge211::Font sans25{"sans.ttf", 25};

View::View(Model const& model)
        : model_(model),
          frog_up_sprite("frog_up.png"),
          frog_right_sprite("frog_right.png"),
          frog_down_sprite("frog_down.png"),
          frog_left_sprite("frog_left.png"),
          frog_dead_sprite("dead_frog.png"),
          background("background.png"),
          racecar_1_sprite("racecar_1.png"),
          tractor_sprite("tractor.png"),
          pink_car_sprite("pink_car.png"),
          racecar_2_sprite("racecar_2.png"),
          truck_sprite("truck_sprite.png"),
          small_log_sprite("small_log.png"),
          medium_log_sprite("medium_log.png"),
          long_log_sprite("long_log.png"),
          two_turtles_sprite("two_turtles.png"),
          three_turtles_sprite("three_turtles.png"),
          two_turtles_diving_sprite("two_turtles_diving.png"),
          three_turtles_diving_sprite("three_turtles_diving.png"),
          home_sprite("home.png"),
          score_sprite()
{ }

void
View::draw(ge211::Sprite_set& set)
{
    // This needs to do something!
    set.add_sprite(background, ge211::the_origin, background_layer);
    draw_coasters(set);
    draw_frog(set);
    draw_homes(set);
 //   draw_score(set);
}

View::Dimensions
View::initial_window_dimensions() const
{
    return model_.config.scene_dims;
}

std::string
View::initial_window_title() const
{
    return "Frogger";
}

void
View::draw_frog(ge211::Sprite_set& set)
{
    if(model_.frog().alive){
        if (model_.frog().facing() == Direction {0, -1}) {
            set.add_sprite(frog_up_sprite, model_.frog().body().top_left(),
                           frog_layer);
        } else if (model_.frog().facing() == Direction {1, 0}) {
            set.add_sprite(frog_right_sprite, model_.frog().body().top_left(),
                           frog_layer);
        } else if (model_.frog().facing() == Direction {0, 1}) {
            set.add_sprite(frog_down_sprite, model_.frog().body().top_left(),
                           frog_layer);
        } else if (model_.frog().facing() == Direction {-1, 0}) {
            set.add_sprite(frog_left_sprite, model_.frog().body().top_left(),
                           frog_layer);
        }
    }else{
        set.add_sprite(frog_dead_sprite, model_.frog().body().top_left(),
                       frog_layer);
    }
}

void
View::draw_coasters(ge211::Sprite_set& set)
{
    for (auto vec : model_.get_coasters()) {
        for (auto coaster : vec) {
            switch (coaster.row()) {
            case 0:
                set.add_sprite(racecar_1_sprite,
                               coaster.coaster_pos(),
                               coaster_layer);
                break;
            case 1:
                set.add_sprite(tractor_sprite,
                               coaster.coaster_pos(),
                               coaster_layer);
                break;
            case 2:
                set.add_sprite(pink_car_sprite,
                               coaster.coaster_pos(),
                               coaster_layer);
                break;
            case 3:
                set.add_sprite(racecar_2_sprite,
                               coaster.coaster_pos(),
                               coaster_layer);
                break;
            case 4:
                set.add_sprite(truck_sprite,
                               coaster.coaster_pos(),
                               coaster_layer);
                break;
            case 6:
                if(coaster.type() == Coaster::other ||
                   coaster.type() ==Coaster::turtle){
                    set.add_sprite(three_turtles_sprite,
                                   coaster.coaster_pos(),
                                   coaster_layer);
                }else if(coaster.type() == Coaster::submerging_turtle){
                    set.add_sprite(three_turtles_diving_sprite,
                                   coaster.coaster_pos(),
                                   coaster_layer);
                }
                break;
            case 7:
                set.add_sprite(small_log_sprite,
                               coaster.coaster_pos(),
                               coaster_layer);
                break;
            case 8:
                set.add_sprite(long_log_sprite,
                               coaster.coaster_pos(),
                               coaster_layer);
                break;
            case 9:
                if(coaster.type() == Coaster::other ||
                   coaster.type() ==Coaster::turtle){
                    set.add_sprite(two_turtles_sprite,
                                   coaster.coaster_pos(),
                                   coaster_layer);
                }else if(coaster.type() == Coaster::submerging_turtle){
                    set.add_sprite(two_turtles_diving_sprite,
                                   coaster.coaster_pos(),
                                   coaster_layer);
                }
                break;
            case 10:
                set.add_sprite(medium_log_sprite,
                               coaster.coaster_pos(),
                               coaster_layer);
                break;
            }
        }
    }
}

void
View::draw_homes(ge211::Sprite_set& set)
{
    for(auto home : model_.homes()){
        if(home.occupied()){
            set.add_sprite(home_sprite, home.body().top_left(), coaster_layer);
        }
    }
}

/*
void
View::draw_score(ge211::Sprite_set& set)
{
    std::string score_string =
            std::to_string(model_.frog().get_frog_score());
    ge211::Text_sprite::Builder score_builder(sans25);
    score_builder.color(ge211::Color::white()) << score_string;
    score_sprite.reconfigure(score_builder);
    set.add_sprite(score_sprite, {25, 25}, frog_layer);
}
 */