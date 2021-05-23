#pragma once

#include "model.hxx"

class View
{
public:

    //
    // TYPE ALIASES
    //

    using Direction = ge211::Dims<int>;
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
    //
    // PRIVATE HELPERS
    //

    /// Add the appropriate frog sprite
    void draw_frog(ge211::Sprite_set& set);

    //
    // PRIVATE DATA MEMBERS
    //
    Model const& model_;

    /// The sprites for the frog
    ge211::Image_sprite const frog_up_sprite;
    ge211::Image_sprite const frog_right_sprite;
    ge211::Image_sprite const frog_down_sprite;
    ge211::Image_sprite const frog_left_sprite;
};
