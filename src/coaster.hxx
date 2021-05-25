#pragma once

#include <ge211.hxx>

#include "game_config.hxx"

/// Interactive objects within the game
class coaster
{
public:
    //
    // TYPE ALIASES
    //

    /// A direction is always {1, 0}, {-1, 0}, {0, 1}, or {0, -1}.
    /// It has not been made an enum class because using dims simplifies
    /// many operations
    using Direction = ge211::Dims<int>;
    using Dimension = ge211::Dims<int>;
    using Position = ge211::Posn<int>;
    using Rectangle = ge211::Rect<int>;

    enum type {lilypad, occupied_lilypad, short_log, medium_log,
        long_log, turtle, submerged_turtle, car};

    //
    // PUBLIC MEMBER FUNCTIONS
    //

    /// Default constructor
    explicit coaster(Game_config const&, type, int, Position);

    /// Moves the object to the desired x value
    void move_to(int x, Game_config const&);

    /// Moves the object in time one frame
    void move(Game_config const&);

    /// Returns the position of the interactive object
    Position interactive_pos() const;

private:

    /// The objects hit box
    Rectangle body_;

    /// Object Type
    type type_;

    /// Specifies which row the object is int
    int row_;

    /// The direction and speed of movement per second;
    int velocity_;

    /// Determines if the interactive object has the ability to kill
    bool hostile_;
};