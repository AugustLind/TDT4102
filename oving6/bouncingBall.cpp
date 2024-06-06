#include "std_lib_facilities.h"
#include "AnimationWindow.h"
#include "bouncingBall.h"

constexpr Point BOUNCE_WINDOW_TOP_LEFT{50, 50};
constexpr int BOUNCE_WINDOW_WIDTH{800}; 
constexpr int BOUNCE_WINDOW_HEIGHT{500};


const map<int, Color> colorMap{
    {1, Color::red},    
    {2, Color::green},  
    {3, Color::blue}, 
    {4, Color::orange}, 
};

istream& operator>>(istream& is, Config& cfg) {
    is >> cfg.upColor >> cfg.downColor >> cfg.velocity;
    return is;
}

void bouncingBall() {
    AnimationWindow window{BOUNCE_WINDOW_TOP_LEFT.x, BOUNCE_WINDOW_TOP_LEFT.y, 
                           BOUNCE_WINDOW_WIDTH, BOUNCE_WINDOW_HEIGHT, "Bouncing ball"};
    
    const int radius{30};
    int alpha{1};
    int velocity{2};
    Color colour_up{Color::blue};
    Color colour_down{Color::blue};
    int x{0};
    int y{360};
    int increment_x{0};
    int increment_y{0};
    int count_bounce_top{0};
    int count_bounce_bottom{0};
    int count_num_passes{0};

    // read from configuration file
    filesystem::path config_file{"konfigurasjon.txt"};
    ifstream is{config_file};

    if (!is) {
        std::cout << "Filen ble ikke åpnet.";
        return;
    }

    Config slow;
    is >> slow;
    Config fast;
    is >> fast;

    Config c = slow;
    // initialise the run
    colour_up = colorMap.at(c.upColor);
    colour_down = colorMap.at(c.downColor);
    velocity = c.velocity;

    while (!window.should_close()) {
        // determine increments based on the velocity
        increment_x = velocity * cos(alpha);
        increment_y = velocity * sin(alpha);

        // movement i x-direction
        if ((increment_x + x) > window.width()+radius) {
            // reached right side - wrap around to the leftmost
            x = 0;
            // increment counter which counts number of full left-to-right passes
            count_num_passes++;
            // alternate between slow and fast configuration every fifth pass
            if (count_num_passes % 5 == 0) {
                // change configuration
                // update both velcity and colors
                if (c.downColor == fast.downColor){
                    c = slow;
                } else{
                    c = fast;
                }

                colour_up = colorMap.at(c.upColor);
                colour_down = colorMap.at(c.downColor);
                velocity = c.velocity;
            }
        } else {
            // moving rightwards
            x += increment_x;
        }
        if (y <= 0 + radius) {
            count_bounce_top++;
        } else if (y >= window.height()-radius) {
            count_bounce_bottom++;
        }
        // movement i y-direction
        if (((count_bounce_top + count_bounce_bottom) % 2) == 0) {
            // move upwards
            y -= increment_y;
            window.draw_circle(Point{x, y}, 30, colour_up);
        } else {
            // move downward
            y += increment_y;
            window.draw_circle(Point{x, y}, 30, colour_down);
        }
    
        window.next_frame();
    }
}

