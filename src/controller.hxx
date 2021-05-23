#pragma once

#include "model.hxx"
#include "view.hxx"

#include <ge211.hxx>

class Controller : public ge211::Abstract_game
{
public:
    Controller();

    /// The GE211 framework calls this to updates the game state to
    /// reflect the passage of time. This function is passed `dt`, the
    /// elapsed time in seconds since the previous frame. The
    /// implementation in controller.cxx delegates to model.on_frame().
    void on_frame(double dt) override;

protected:
    /// These three delegate to the view:
    void draw(ge211::Sprite_set&) override;
    View::Dimensions initial_window_dimensions() const override;
    std::string initial_window_title() const override;

    /// Defines how the game responds to key events.
    void on_key(ge211::Key) override;


private:
    Model model_;
    View view_;
};

