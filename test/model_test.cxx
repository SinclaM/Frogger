#include "model.hxx"

#include <catch.hxx>

#include <iostream>

//
// TODO: Write preliminary model tests.
//
// These tests should demonstrate at least six of the functional
// requirements.
//

TEST_CASE("Frog moves")
{
    Model m;
    m.remove_coasters(); // no cars, please
    ge211::Posn<int> expected(m.frog().body().top_left());
    CHECK(m.frog().body().top_left() == expected);

    // Upward hop
    m.set_hop_clock_time(0);
    expected = expected.up_by(m.config.hop_dist.height);
    m.move_frog({0, -1});
    CHECK(m.frog().body().top_left() == expected);

    // Downward hop
    m.set_hop_clock_time(0);
    expected = expected.down_by(m.config.hop_dist.height);
    m.move_frog({0, 1});
    CHECK(m.frog().body().top_left() == expected);

    // Rightward hop
    m.set_hop_clock_time(0);
    expected = expected.right_by(m.config.hop_dist.width);
    m.move_frog({1, 0});
    CHECK(m.frog().body().top_left() == expected);

    // Leftward hop
    m.set_hop_clock_time(0);
    expected = expected.left_by(m.config.hop_dist.width);
    m.move_frog({-1, 0});
    CHECK(m.frog().body().top_left() == expected);

    // Forbidden hop. The frog can't go any farther down than it is initially
    // since that space is reserved for the timer, so it refuses to move.
    m.set_hop_clock_time(0);
    m.move_frog({0, 1});
    CHECK(m.frog().body().top_left() == expected);
}

TEST_CASE("Frog hits car")
{
    Model m;
    m.remove_coasters();

    // Place a car right above the frog
    ge211::Posn<int> pos(m.frog().body().top_left().up_by(
            m.config.hop_dist.height));
    Coaster c(m.config, Game_config::racecar_1_row, pos);
    m.add_coaster(c);
    CHECK_FALSE(m.frog().hits(c.body()));
    CHECK(m.frog().alive);

    // move up and hit
    m.set_hop_clock_time(0);
    m.move_frog({0, -1});
    CHECK(m.frog().hits(c.body()));
    CHECK(m.frog().frog_lives_left() == 3);

    // simulate one frame
    double const dt = 1.0 / 60;
    m.on_frame(dt);

    CHECK(m.frog().hits(c.body()));
    CHECK(c.is_hostile());
    CHECK_FALSE(m.frog().alive);
    CHECK(m.frog().frog_lives_left() == 2);

    // another frame, while the frog's death animation plays
    m.on_frame(dt);
    CHECK(m.frog().hits(c.body()));
    CHECK_FALSE(m.frog().alive);

    // Death animation means no extra life lost
    CHECK(m.frog().frog_lives_left() == 2);
}