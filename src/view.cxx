#include "view.hxx"

static int background_layer = 0; // background scenery
static int surface_layer = 1; // water, scoring, timer, life count
static int entity_layer = 2; // cars, turtles, logs
static int frog_layer = 3; // frog

View::View(Model const& model)
        : model_(model),
          frog_up_sprite("frog_up.png"),
          frog_right_sprite("frog_right.png"),
          frog_down_sprite("frog_down.png"),
          frog_left_sprite("frog_left.png"),
          frog_dead_sprite("dead_frog.png"),
          background("background.png"),
          car_sprite(model.config.car_dims)
{ }

void
View::draw(ge211::Sprite_set& set)
{
    // This needs to do something!
    set.add_sprite(background, ge211::the_origin, background_layer);
    draw_car(set);
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
View::draw_car(ge211::Sprite_set& set)
{
    for (auto vec : model_.get_coaster())
    {
        for (auto obj : vec)
        {
            set.add_sprite(car_sprite, obj.coaster_pos(), entity_layer);
        }
    }
}

