#include "view.hxx"

static ge211::Color frog_color{255, 0, 0};

View::View(Model const& model)
        : model_(model),
          frog_sprite("frog.png")
{ }

void
View::draw(ge211::Sprite_set& set)
{
    // This needs to do something!
    set.add_sprite(frog_sprite, model_.frog_position());
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
