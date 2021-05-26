#include "view.hxx"

static int background_layer = 0; // background scenery
static int surface_layer = 1; // water, scoring, timer, life count
static int coaster_layer = 2; // cars, turtles, logs
static int frog_layer = 3; // frog

View::View(Model const& model)
        : model_(model),
          frog_up_sprite("frog_up.png"),
          frog_right_sprite("frog_right.png"),
          frog_down_sprite("frog_down.png"),
          frog_left_sprite("frog_left.png"),
          frog_dead_sprite("dead_frog.png"),
          background("background.png"),
          car_sprite(model.config.car_dims),
          short_log_sprite(model.config.short_log_dims),
          medium_log_sprite(model.config.medium_log_dims),
          long_log_sprite(model.config.long_log_dims),
          two_turtle_sprite(model.config.two_turtle_dims),
          two_turtle_submerging_sprite(model.config.two_turtle_dims,
                                   ge211::Color::medium_green()),
          two_turtle_submerged_sprite(model.config.two_turtle_dims,
                                  ge211::Color::black()),
          three_turtle_sprite(model.config.three_turtle_dims),
          three_turtle_submerging_sprite(model.config.three_turtle_dims,
                                       ge211::Color::medium_green()),
          three_turtle_submerged_sprite(model.config.three_turtle_dims,
                                      ge211::Color::black())

{ }

void
View::draw(ge211::Sprite_set& set)
{
    // This needs to do something!
    set.add_sprite(background, ge211::the_origin, background_layer);
    draw_coasters(set);
    draw_frog(set);
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
    for (auto vec : model_.get_coasters()){

        for (auto obj : vec){
            if (obj.coaster_type() == coaster::object_type::car)
            {
                set.add_sprite(car_sprite, obj.coaster_pos(), coaster_layer);
            }
            else if (obj.coaster_type() == coaster::object_type::short_log)
            {
                set.add_sprite(short_log_sprite, obj.coaster_pos(),
                               coaster_layer);
            }
            else if (obj.coaster_type() == coaster::object_type::medium_log)
            {
                set.add_sprite(medium_log_sprite, obj.coaster_pos(),
                               coaster_layer);
            }
            else if (obj.coaster_type() == coaster::object_type::long_log)
            {
                set.add_sprite(long_log_sprite, obj.coaster_pos(),
                               coaster_layer);
            }
            else if (obj.coaster_type() == coaster::object_type::turtle ||
            obj.coaster_type() == coaster::passive_turtle)
            {
                if (obj.get_row() == 6) {
                    set.add_sprite(two_turtle_sprite, obj.coaster_pos(),
                                   coaster_layer);
                }
                else
                {
                    set.add_sprite(three_turtle_sprite, obj.coaster_pos(),
                                   coaster_layer);
                }
            }
            else if (obj.coaster_type() == coaster::object_type::submerging_turtle)
            {
                if (obj.get_row() == 6) {
                    set.add_sprite(two_turtle_submerging_sprite,
                                   obj.coaster_pos(),
                                   coaster_layer);
                }
                else
                {
                    set.add_sprite(three_turtle_submerging_sprite, obj
                    .coaster_pos(), coaster_layer);
                }
            }
            else if (obj.coaster_type() == coaster::object_type::submerged_turtle)
            {
                if (obj.get_row() == 6) {
                    set.add_sprite(two_turtle_submerged_sprite,
                                   obj.coaster_pos(),
                                   coaster_layer);
                }
                else
                {
                    set.add_sprite(three_turtle_submerged_sprite, obj
                            .coaster_pos(), coaster_layer);
                }
            }
            else if (obj.coaster_type() == coaster::object_type::passive_turtle)
            {
                set.add_sprite(two_turtle_sprite, obj.coaster_pos(),
                               coaster_layer);
            }
        }
    }
}

