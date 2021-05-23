#include "view.hxx"

static ge211::Color frog_color{255, 0, 0};

View::View(Model const& model)
        : model_(model),
          frog_up_sprite("frog_up.png"),
          frog_right_sprite("frog_right.png"),
          frog_down_sprite("frog_down.png"),
          frog_left_sprite("frog_left.png")
{ }

void
View::draw(ge211::Sprite_set& set)
{
    // This needs to do something!
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
    if(model_.frog().facing() == Direction{0, -1}){
        set.add_sprite(frog_up_sprite, model_.frog().top_left());
    }else if(model_.frog().facing() == Direction{1, 0}){
        set.add_sprite(frog_right_sprite, model_.frog().top_left());
    }else if(model_.frog().facing() == Direction{0, 1}){
        set.add_sprite(frog_down_sprite, model_.frog().top_left());
    }else if(model_.frog().facing() == Direction{-1, 0}){
        set.add_sprite(frog_left_sprite, model_.frog().top_left());
    }
}
