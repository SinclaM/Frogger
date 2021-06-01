#include "model.hxx"

#include <catch.hxx>

#include <iostream>


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

TEST_CASE("Frog Standing on moving passive objects")
{


    // Create the coaster to be used in the test, a turtle coaster, to be
    // spawned in at the frog's starting position. Test cases for a log or
    // turtle are essentially identical.
    Coaster c(Game_config(), 6,
              Coaster::object_type::passive_turtle,
              {Game_config().start.x,
               Game_config().start.y});

    // create the coaster matrix
    Model::Coaster_matrix coasters{{c}};

    // create a model with only the single coaster created above
    Model m(coasters);

    // Create a posn with the initial frog position
    Model::Position initial_frog_position{m.config.start.x - m.config
    .frog_dims.width /2 , m.config.start.y};

    // Gets the actual frog position
    Model::Position actual_frog_position{m.frog().body().x, m.frog().body()
    .y};

    // Checks that the expected initial frog position and actual initial frog
    // positions are equal
    CHECK(actual_frog_position == initial_frog_position);

    // Checks to make sure a collision is detected with the turtle
    CHECK(m.frog().stict_hits(c.body(), m.config));

    // Create a half second frame
    m.on_frame(1.0 / 2);

    // Checks the collision with the turtle again
    CHECK(m.frog().stict_hits(c.body(), m.config));


    // Creates a posn representing the expected ending position of the frog
    // determined by the movement of the the turtle
    Model::Position frog_ending_pos{m.config.row_velocities[6] / 2 + m
            .config.start.x, m.config.start.y};

    // Gets the frog's actual position
    actual_frog_position = {m.frog().body().x, m.frog().body().y};

    // Checks that the expected final position and ending position are equal
    CHECK(actual_frog_position == frog_ending_pos);
}

TEST_CASE("Timer runs out"){
    Model m;
    m.remove_coasters();

    CHECK(m.life_clock().time() == 30);

    // Simulate a couple frames at 14 seconds per frame
    double const dt = 14;
    m.on_frame(dt);
    CHECK(m.life_clock().time() == 16);
    CHECK(m.frog().alive);
    m.on_frame(dt);
    CHECK(m.life_clock().time() == 2);
    CHECK(m.frog().alive);
    CHECK(m.frog().frog_lives_left() == 3);
    m.on_frame(dt);
    CHECK(m.life_clock().time() == 30); // Clock has reset
    CHECK_FALSE(m.frog().alive);
    CHECK(m.frog().frog_lives_left() == 2); // Life deducted
    // Time still 30 since reset_clock is active
    CHECK(m.life_clock().time() == 30);

    // Let the frog reset
    m.on_frame(dt);

    // Let's have the frog die some more and see if the player loses
    m.on_frame(dt); // 16
    CHECK(m.life_clock().time() == 16);
    m.on_frame(dt); // 2
    CHECK(m.frog().alive);
    m.on_frame(dt); // Death
    CHECK_FALSE(m.frog().alive);
    CHECK(m.frog().frog_lives_left() == 1);

    // Let the frog reset
    m.on_frame(dt);

    m.on_frame(dt); // 16
    CHECK(m.life_clock().time() == 16);
    m.on_frame(dt); // 2
    CHECK(m.frog().alive);
    m.on_frame(dt); // Death
    CHECK_FALSE(m.frog().alive);
    CHECK(m.frog().frog_lives_left() == 0);

    // Note: 0 lives does not mean game over. Rather, there are no lives left
    // in the bank for the frog, meaning one more death is game over.
    CHECK_FALSE(m.is_game_over());

    // Let the frog reset
    m.on_frame(dt);

    m.on_frame(dt); // 16
    CHECK(m.life_clock().time() == 16);
    m.on_frame(dt); // 2
    CHECK(m.frog().alive);
    m.on_frame(dt); // Final death
    CHECK_FALSE(m.frog().alive);
    CHECK(m.is_game_over());
}

TEST_CASE("Objects speed up"){
    Model m;
    m.remove_coasters(); // Let's focus on just one coaster
    ge211::Posn<int> pos(m.frog().body().top_left().up_by(
            m.config.hop_dist.height));
    Coaster c(m.config, Game_config::racecar_1_row, pos);
    m.add_coaster(c);
    int speed = abs(c.velocity()); // initial speed

    // Now let's occupy a couple homes and see if the coaster speeds up
    m.frog_ref().move_to(m.homes()[0].body().top_left(), m.config);
    CHECK(m.frog().stict_hits(m.homes()[0].body(), m.config));
    m.on_frame(1.0 / 60); // simulate a frame so the model can update
    CHECK(occupied_count(m.homes()) == 1);
    // The car sped up
    CHECK(abs(m.coasters()[0][0].velocity()) == speed + 5);

    // Let's try that again
    m.frog_ref().move_to(m.homes()[1].body().top_left(), m.config);
    m.on_frame(1.0 / 60);
    CHECK(occupied_count(m.homes()) == 2);
    CHECK(abs(m.coasters()[0][0].velocity()) == speed + 10);
}


TEST_CASE("Occupying all homes results in a win!")
{
    // Creates a model
    Model m;

    // iterates over all the homes
    for(size_t ct = 0; ct < m.homes_ref().size(); ct++)
    {
        // Check that the home is unoccupied
        CHECK_FALSE(m.homes_ref().at(ct).occupied());

        // occupy the home
        m.homes_ref().at(ct).occupy();

        //check that the home is now occupied
        CHECK(m.homes_ref().at(ct).occupied());


        if(ct < 4)
        {
            // check that the game is not yet over
            CHECK_FALSE(m.is_game_over());
        }
        else
        {
            // after occupying all homes, check that the game is over, and
            // that all the homes are in fact occupied. This is the
            // condition for a game win
            CHECK(m.is_game_over());
            CHECK(all_occupied(m.homes()));
        }
    }
}

TEST_CASE("Occupying homes with the frog")
{
    // Creates a model
    Model m;

    // iterates over all the homes
    for(size_t ct = 0; ct < m.homes_ref().size(); ct++)
    {
        // Checks that the home is not occupied
        CHECK_FALSE(m.homes_ref().at(ct).occupied());

        // moves the frog over the home
        m.frog_ref().move_to(m.homes_ref().at(ct).body().center(), m.config);

        //runs the game for 1/60 of a second
        m.on_frame(1.0/60);

        // Checks that the home is now occupied
        CHECK(m.homes_ref().at(ct).occupied());

        // runs a check on only the first iteration of the for loop that
        // moving a frog to an already occupied home kills it
        if(ct == 0)
        {
            m.frog_ref().move_to(m.homes_ref().at(ct).body().center(),
                                                            m.config);

            m.on_frame(1.0/60);

            CHECK_FALSE(m.frog().alive);
        }

        if(ct < 4)
        {
            //Checks that the game is not yet over
            CHECK_FALSE(m.is_game_over());
        }
        else
        {
            // on the final iteration of the for loop, checks that the game
            // is over and that all the homes are occupied, this is the
            // condition for a game win.
            CHECK(m.is_game_over());
            CHECK(all_occupied(m.homes()));
        }
    }
}