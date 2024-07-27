#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

struct ball_2D {
    sf::CircleShape shape;
    double mass;
    sf::Vector2f speed;
    ball_2D(sf::CircleShape&& shape_, sf::Vector2f&& speed_)     
    {
        shape = move(shape_);
        mass = (2 * 3.14 * shape.getRadius()) * 1.1;  //mass unit 1.1 * area of shape
        speed = move(speed_);
    }        
    ball_2D(sf::CircleShape&& shape_)         
    {
        shape = move(shape_);
        mass = (2 * 3.14 * shape.getRadius()) * 1.1;
        speed = sf::Vector2f(0, 0);
    } 
};


int main(int argc, char** argv) {
    srand(time(NULL));


    int windows_x_size = 800;
    int windows_y_size = 600;
    sf::RenderWindow window(sf::VideoMode(windows_x_size, windows_y_size), "collisions_1D");
    window.setFramerateLimit(30);
    
    vector<ball_2D> objs;

    int base_r = 10;
    size_t objs_number = 3;    
    int position_y = windows_y_size / 2;

    for(size_t i = 0; i < objs_number; ++i) {
        objs.emplace_back(
            ball_2D(sf::CircleShape( 
                base_r + rand()%5),                
                sf::Vector2f((i%2) ? rand()%10 : (-1 * rand()%10), 0)                
            )
        );        
    }
    for(size_t i = 0; i < objs_number; ++i) {
        objs[i].shape.setFillColor(sf::Color::Blue);
    }
    for(size_t i = 0; i < objs_number; ++i) {
        objs[i].shape.setPosition(sf::Vector2f(
            rand() % (windows_x_size - static_cast<int>(objs[i].shape.getRadius())),
            position_y            
        ));
    }



    sf::Event event;
    while(window.isOpen()) {
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();            
            }
        }
        window.clear();

        for(size_t i = 0; i < objs_number; ++i) {

            //border bounce   
            /* 
            SFML border coordinatess differ from window size ???
            bounce occurs before x0 and afer xEnd of window size

            not, but: 
                        
            SFML set x coordinates on left border, even for Cicle shape
            and y perhaps similiar
            So for our object we must recalculate x and y
            TODO: and this is not done here 
            */
            
            sf::Vector2f positionPrime = objs[i].shape.getPosition();
            float radius = objs[i].shape.getRadius();
            float diameter = radius * 2;
            if( 
                positionPrime.x - radius <= 0
                ||
                positionPrime.x + radius >= windows_x_size
            ){  //TODO shift
                objs[i].speed.x *= -1;
            }
            if( 
                positionPrime.y - radius <= 0
                ||
                positionPrime.y + radius >= windows_y_size
            ){  //TODO shift
                objs[i].speed.y *= -1;
            }

            //collision detection
            bool is_collision = false;
            for(size_t i = 0; i < objs_number; ++i) {
                for(size_t j = i + 1; j < objs_number; ++j) {
                    int distance = abs(objs[i].shape.getPosition().x - objs[j].shape.getPosition().x);
                    int radius_sum = objs[i].shape.getRadius() + objs[j].shape.getRadius();                    
                    if(distance <= radius_sum){
                        //collision occurs

                        //collision resolution
                        /*
                        TODO:
                        calculating overlaping not work properly                        
                        perhaps because of:
                        object position coordinates shoud be float/double
                        and cast to integer during setPosition()
                        So ball_2D class shoud have additional position member
                        (and perhaps radius for Cicle shape, 
                        and other dimension parameters for 
                        other shapes)
                        */
                        int overlap = radius_sum - distance;
                        int half_overlap = overlap / 2 + 1;
                        float vxa1 = objs[i].speed.x;
                        float vxb1 = objs[j].speed.x;
                        float ma = objs[i].mass;
                        float mb = objs[j].mass;

                        float vxa2 = (vxa1 * (ma - mb) + 2 * mb * vxb1)/(ma + mb);
                        float vxb2 = (vxb1 * (mb - ma) + 2 * ma * vxa1)/(ma + mb);

                        objs[i].speed.x = vxa2;
                        objs[j].speed.x = vxb2;

                        /*
                        for two objects overlapping problem can be solved
                        by simply shift x posiotion of object by overlaping/2
                        and new position in new frame will be calcualted based
                        on that shifted x and new speed
                        */
                        int xa = objs[i].shape.getPosition().x;
                        int xb = objs[j].shape.getPosition().x;
                        if(xa < xb) {
                            objs[i].shape.setPosition(xa - half_overlap, position_y);
                            objs[j].shape.setPosition(xb + half_overlap, position_y);
                        }
                        else {
                            objs[i].shape.setPosition(xa + half_overlap, position_y);
                            objs[j].shape.setPosition(xb - half_overlap, position_y);
                        }
                    }
                }
            }

            

            //new position
            positionPrime.x += objs[i].speed.x;
            positionPrime.y += objs[i].speed.y;

            objs[i].shape.setPosition(positionPrime);
            
            window.draw(objs[i].shape);
        }
        window.display();    
    }
    return 0;
}