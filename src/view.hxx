#pragma once

#include "model.hxx"

class View
{
public:

    //
    // TYPE ALIASES
    //

    using Dimensions = ge211::Dims<int>;
    using Position = ge211::Posn<int>;
    using Rectangle = ge211::Rect<int>;

    explicit View(Model const& model);

    void draw(ge211::Sprite_set& set);

    /// Communicate desired window size to controller
    Dimensions initial_window_dimensions() const;

    /// Communicate desired window name to controller
    std::string initial_window_title() const;

private:
    Model const& model_;

    // TODO: Figure out how to use Image_sprites. This is too small.
    ge211::Image_sprite const frog_sprite;
};
