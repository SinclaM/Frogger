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
    using Image = ge211::Image_sprite;

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

    void draw_coasters(ge211::Sprite_set& set);

    //
    // PRIVATE DATA MEMBERS
    //
    Model const& model_;

    /// The sprites for the frog
    Image const frog_up_sprite;
    Image const frog_right_sprite;
    Image const frog_down_sprite;
    Image const frog_left_sprite;
    Image const frog_dead_sprite;

    /// Background
    Image const background;

    /// the coaster sprites ***** TO BE CHANGED
    ge211::Rectangle_sprite const car_sprite;
    ge211::Rectangle_sprite const short_log_sprite;
    ge211::Rectangle_sprite const medium_log_sprite;
    ge211::Rectangle_sprite const long_log_sprite;
    ge211::Rectangle_sprite const two_turtle_sprite;
    ge211::Rectangle_sprite const two_turtle_submerging_sprite;
    ge211::Rectangle_sprite const two_turtle_submerged_sprite;
    ge211::Rectangle_sprite const three_turtle_sprite;
    ge211::Rectangle_sprite const three_turtle_submerging_sprite;
    ge211::Rectangle_sprite const three_turtle_submerged_sprite;
};
