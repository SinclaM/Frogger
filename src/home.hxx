#pragma once

#include <ge211.hxx>

#include "game_config.hxx"

class Home{
public:

    //
    // TYPE ALIASES
    //

    using Position = ge211::Posn<int>;
    using Rectangle = ge211::Rect<int>;

    //
    // PUBLIC MEMBER FUNCTIONS
    //

    /// Constructor
    explicit Home(const Game_config&, Position);

    /// Gets occupation status
    bool occupied() const;

    /// Sets occupation status to occupied
    void occupy();

    /// Gets the body
    Rectangle body() const;

private:

    //
    // DATA MEMBERS
    //

    /// The rectangular body of the home
    Rectangle body_;

    /// Whether the home is occupied
    bool occupied_;
};

/// Makes a vector of homes as specified by the game config
std::vector<Home> make_homes(const Game_config&);

/// Determines whether all homes in a vector are occupied
bool all_occupied(std::vector<Home>);