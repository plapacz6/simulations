#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <cstdio>
#include <algorithm>
#include <cassert>

#include "collisions_1Dv2.h"

using namespace std;


int main(int argc, char** argv) {
    srand(time(NULL));

    animation_1D aa;
    aa.init();
 
    sf::RenderWindow window(sf::VideoMode(aa.windows_x_size, aa.windows_y_size), "collisions_1D");

    size_t frame_per_second = aa.frame_per_second;


    window.setFramerateLimit(frame_per_second);
    
    
    sf::Event event;
    while(window.isOpen()) {
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();            
            }
        }
        window.clear();
        for(size_t i = 0; i < aa.objs_number; ++i) {
            window.draw(aa.objs[i].shape);
        }
        window.display();    

        aa.calculate_positions();

    }//while SFML
    return 0;
}


