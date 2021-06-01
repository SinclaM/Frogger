#pragma once

#include "model.hxx"

/// The view controls the visual elements of the game such a the sprite, the
/// number of lives left, the score, and the timer
class View
{
public:
    /// enumeration for layers to draw on
    enum layer{background_layer, surface_layer, coaster_layer, frog_layer,
            top_screen_layer, end_display_layer};

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

    /// Add the coasters
    void draw_coasters(ge211::Sprite_set& set);

    /// Add the homes
    void draw_homes(ge211::Sprite_set& set);

    /// Add the score
    void draw_score(ge211::Sprite_set& set);

    /// Display's the frog's remaining lives
    void draw_lives(ge211::Sprite_set& set);

    /// Draw the game over screen
    void draw_game_over(ge211::Sprite_set& set);

    /// Draw the timer
    void draw_timer(ge211::Sprite_set& set, double x_scale);

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

    /// Sprites for the cars
    Image const racecar_1_sprite;
    Image const tractor_sprite;
    Image const pink_car_sprite;
    Image const racecar_2_sprite;
    Image const truck_sprite;

    /// Logs
    Image const small_log_sprite;
    Image const medium_log_sprite;
    Image const long_log_sprite;

    /// Turtles
    Image const two_turtles_sprite;
    Image const three_turtles_sprite;
    Image const two_turtles_diving_sprite;
    Image const three_turtles_diving_sprite;

    /// Happy frog sitting in a home
    Image const home_sprite;

    /// Score Sprite
    ge211::Font sans25;
    ge211::Text_sprite score_sprite;

    /// Lives Sprite
    Image const life_sprite;

    /// Sprite for end game screen
    ge211::Text_sprite end_game_score;
    ge211::Text_sprite game_over_text;
    ge211::Text_sprite your_score_text;
    ge211::Font end_game_score_font;
    ge211::Rectangle_sprite end_game_fade_loss;
    ge211::Rectangle_sprite end_game_fade_win;

    /// Sprite for timer
    ge211::Rectangle_sprite timer_sprite;
};
