#include "view.hxx"

#include "game_config.hxx"

#include <ge211_resource.hxx>

View::View(Model const& model)
        : model_(model),
          frog_up_sprite("frog_up.png"),
          frog_right_sprite("frog_right.png"),
          frog_down_sprite("frog_down.png"),
          frog_left_sprite("frog_left.png"),
          frog_dead_sprite("dead_frog.png"),
          background("background.png"),
          racecar_1_sprite("racecar_1.png"),
          tractor_sprite("tractor.png"),
          pink_car_sprite("pink_car.png"),
          racecar_2_sprite("racecar_2.png"),
          truck_sprite("truck_sprite.png"),
          small_log_sprite("small_log.png"),
          medium_log_sprite("medium_log.png"),
          long_log_sprite("long_log.png"),
          two_turtles_sprite("two_turtles.png"),
          three_turtles_sprite("three_turtles.png"),
          two_turtles_diving_sprite("two_turtles_diving.png"),
          three_turtles_diving_sprite("three_turtles_diving.png"),
          home_sprite("home.png"),
          // score_sprite(),
          life_sprite("life.png"),
          // end_game_score(),
          // game_over_text(),
          // your_score_text(),
          end_game_fade({model.config.scene_dims},
                        model.config.end_game_background_fade),
          timer_sprite(model.config.timer_rec.dimensions(),
                       model.config.timer_color)
{ }

void
View::draw(ge211::Sprite_set& set)
{
    set.add_sprite(background, ge211::the_origin, background_layer);
    draw_coasters(set);
    draw_frog(set);
    draw_homes(set);
    draw_score(set);
    draw_lives(set);
    draw_timer(set, model_.life_clock().time() /
                              model_.config.lifetime);
    if(model_.is_game_over()){
        draw_game_over(set);
    }
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
    if(model_.frog().alive){
        if (model_.frog().facing() == Direction {0, -1}) {
            set.add_sprite(frog_up_sprite, model_.frog().body().top_left(),
                           frog_layer);
        } else if (model_.frog().facing() == Direction {1, 0}) {
            set.add_sprite(frog_right_sprite, model_.frog().body().top_left(),
                           frog_layer);
        } else if (model_.frog().facing() == Direction {0, 1}) {
            set.add_sprite(frog_down_sprite, model_.frog().body().top_left(),
                           frog_layer);
        } else if (model_.frog().facing() == Direction {-1, 0}) {
            set.add_sprite(frog_left_sprite, model_.frog().body().top_left(),
                           frog_layer);
        }
    }else{
        set.add_sprite(frog_dead_sprite, model_.frog().body().top_left(),
                       frog_layer);
    }
}

void
View::draw_coasters(ge211::Sprite_set& set)
{
    for (auto vec : model_.get_coasters()) {
        for (auto coaster : vec) {
            switch (coaster.row()) {
            case Game_config::racecar_1_row:
                set.add_sprite(racecar_1_sprite,
                               coaster.coaster_pos(),
                               coaster_layer);
                break;
            case Game_config::tractor_row:
                set.add_sprite(tractor_sprite,
                               coaster.coaster_pos(),
                               coaster_layer);
                break;
            case Game_config::pink_car_row:
                set.add_sprite(pink_car_sprite,
                               coaster.coaster_pos(),
                               coaster_layer);
                break;
            case Game_config::racecar_2_row:
                set.add_sprite(racecar_2_sprite,
                               coaster.coaster_pos(),
                               coaster_layer);
                break;
            case Game_config::truck_row:
                set.add_sprite(truck_sprite,
                               coaster.coaster_pos(),
                               coaster_layer);
                break;
            case Game_config::three_turtles_row:
                if(coaster.type() == Coaster::other ||
                   coaster.type() == Coaster::turtle){
                    set.add_sprite(three_turtles_sprite,
                                   coaster.coaster_pos(),
                                   coaster_layer);
                }else if(coaster.type() == Coaster::submerging_turtle){
                    set.add_sprite(three_turtles_diving_sprite,
                                   coaster.coaster_pos(),
                                   coaster_layer);
                }
                break;
            case Game_config::small_log_row:
                set.add_sprite(small_log_sprite,
                               coaster.coaster_pos(),
                               coaster_layer);
                break;
            case Game_config::long_log_row:
                set.add_sprite(long_log_sprite,
                               coaster.coaster_pos(),
                               coaster_layer);
                break;
            case Game_config::two_turtles_row:
                if(coaster.type() == Coaster::other ||
                   coaster.type() ==Coaster::turtle){
                    set.add_sprite(two_turtles_sprite,
                                   coaster.coaster_pos(),
                                   coaster_layer);
                }else if(coaster.type() == Coaster::submerging_turtle){
                    set.add_sprite(two_turtles_diving_sprite,
                                   coaster.coaster_pos(),
                                   coaster_layer);
                }
                break;
            case Game_config::medium_log_row:
                set.add_sprite(medium_log_sprite,
                               coaster.coaster_pos(),
                               coaster_layer);
                break;
            }
        }
    }
}

void
View::draw_homes(ge211::Sprite_set& set)
{
    for(auto home : model_.homes()){
        if(home.occupied()){
            set.add_sprite(home_sprite, home.body().top_left(),
                           surface_layer);
        }
    }
}


void
View::draw_score(ge211::Sprite_set& set)
{
    std::string score_string =
            std::to_string(model_.frog().get_frog_score());
    ge211::Text_sprite::Builder score_builder(sans25);
    score_builder.color(ge211::Color::white()) << score_string;
    score_sprite.reconfigure(score_builder);
    set.add_sprite(score_sprite, model_.config.score_pos, surface_layer);
}


void
View::draw_lives(ge211::Sprite_set& set)
{
    for(int ct = 0; ct < model_.frog().frog_lives_left(); ct++){
        set.add_sprite(life_sprite,
                       model_.config.leftmost_life_pos.right_by(
                                            model_.config.life_spacing * ct),
                       surface_layer);
    }
}


void
View::draw_game_over(ge211::Sprite_set& set)
{
    set.add_sprite(end_game_fade, ge211::the_origin, top_screen_layer);

    ge211::Text_sprite::Builder game_over_builder(end_game_score_font);
    game_over_builder.color(ge211::Color::white()) << "Game Over";
    game_over_text.reconfigure(game_over_builder);
    set.add_sprite(game_over_text, {model_.config.scene_dims.width / 2 -
                                    game_over_text.dimensions().width / 2,
                                    model_.config.scene_dims.height / 2 -
                                    game_over_text.dimensions().height},
                   end_display_layer);

    ge211::Text_sprite::Builder your_score_builder(end_game_score_font);
    your_score_builder.color(ge211::Color::white()) << "Your Score Is:";
    your_score_text.reconfigure(your_score_builder);
    set.add_sprite(your_score_text, {model_.config.scene_dims.width / 2 -
                                    your_score_text.dimensions().width / 2,
                                    model_.config.scene_dims.height / 2 -
                                    your_score_text.dimensions().height / 2},
                   end_display_layer);

    std::string score_string =
            std::to_string(model_.frog().get_frog_score());
    ge211::Text_sprite::Builder score_builder(end_game_score_font);
    score_builder.color(ge211::Color::white()) << score_string;
    end_game_score.reconfigure(score_builder);
    set.add_sprite(end_game_score,
                   {model_.config.scene_dims.width / 2 -
                        end_game_score.dimensions().width / 2,
                        model_.config.scene_dims.height / 2},
                        end_display_layer);
}

void
View::draw_timer(ge211::Sprite_set& set, double x_scale)
{
    set.add_sprite(timer_sprite, model_.config.timer_rec.top_left(),
                   surface_layer, ge211::Transform::scale_x(x_scale));
}
