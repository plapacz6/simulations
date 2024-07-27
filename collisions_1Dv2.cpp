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

#define ABS_D(DOUBLE_VALUE) (((DOUBLE_VALUE) > 0) ? (DOUBLE_VALUE) : (-1 * (DOUBLE_VALUE)))

/************************************************************************************** */

double ball_2D::get_xR_size(sf::Vector2<double> ) {
    //do the mat
    //i 1D for Circle it is equal radius
    return shape.getRadius();
}

double ball_2D::get_xL_size(sf::Vector2<double> ) {
    //do the math 
    //i 1D for Circle it is equal radius
    return shape.getRadius();
}    

/*
SFML set x coordinates on left bcollision_dt, even for Cicle shape
and y perhaps similiar
So for our object we must recalculate x and y
*/    
void ball_2D::setPosition(sf::Vector2<double> ps) {
    newpos.x = pos.x = ps.x;
    newpos.y = pos.y = ps.y;
    float radius = shape.getRadius();
    shape.setPosition(
        sf::Vector2f(
            static_cast<float>(pos.x - radius), 
            static_cast<float>(pos.y - radius)
        )
    );
    printf("newpos: %g, pos:%g, speed:%g\n", newpos.x, pos.x, speed.x);
}   

void ball_2D::setPosition(double x, double y) {
    newpos.x = pos.x = x;
    newpos.y = pos.y = y;
    float radius = shape.getRadius();
    shape.setPosition(
        sf::Vector2f(
            static_cast<float>(pos.x - radius), 
            static_cast<float>(pos.y - radius)
        )
    );
    printf("newpos: %g, pos:%g, speed:%g\n", newpos.x, pos.x, speed.x);
}; 

ball_2D::ball_2D(sf::CircleShape&& shape_, sf::Vector2<double>&& speed_) {
    shape = move(shape_);
    // mass = (2 * 3.14 * shape.getRadius()) * 1.1;  //mass unit 1.1 * area of shape
    mass = ((4.0/3.0) * 3.14 * std::pow(static_cast<double>(shape.getRadius()), 3));
    speed = move(speed_);
    pos.x = pos.y = newpos.x = newpos.y = 0;
}        

ball_2D::ball_2D(sf::CircleShape&& shape_) {
    shape = move(shape_);
    mass = ((4.0/3.0) * 3.14 * std::pow(static_cast<double>(shape.getRadius()), 3));
    speed = sf::Vector2<double>{0.0, 0.0};
    pos.x = pos.y = newpos.x = newpos.y = 0;
} 

/************************************************************************************** */

wall_1D::wall_1D() : wall_1D(sf::Vector2<double>{0.0, 0.0}) {
}

wall_1D::wall_1D(sf::Vector2<double> ps) {
    mass = -1;
    speed.x = 0;
    speed.y = 0;
    newpos.x = pos.x = ps.x;
    newpos.y = pos.y = ps.y;
}

double wall_1D::get_xR_size(sf::Vector2<double>) {
    return 0;
}

void wall_1D::setPosition(sf::Vector2<double> ps) {        
    newpos.x = pos.x = ps.x;
    newpos.y = pos.y = ps.y;
}
void wall_1D::setPosition(double x, double y) {
    newpos.x = pos.x = x;
    newpos.y = pos.y = y;    
};

double wall_1D::get_xL_size(sf::Vector2<double> ) {
    return 0;
}

/************************************************************************************** */

collision_1D::collision_1D(object_2D& oL, object_2D& oR) {
    set(oL, oR);
    position_y = oL.pos.y;        
}

void collision_1D::set(object_2D& oL, object_2D& oR) {
    objL = &oL;
    objR = &oR;
    clear();
}

void collision_1D::clear() {
    is = false;
    overlap = 0;
    ol_L = 0;
    ol_R = 0;
    collision_dt = -1;        
}

double collision_1D::calculate_dt(double curr_dt){
    if(ol_L) {
        collision_dt = objL->speed.x / ol_L;
    }
    else if(ol_R) {
        collision_dt = objR->speed.x / ol_R;
    }
    else {
        collision_dt = curr_dt;
    }
    return collision_dt;
}    

void collision_1D::calculate_overlap_proportion() {
    if(objL->speed.x || objR->speed.x) {

        double vxL = ABS_D(objL->speed.x);
        double vxR = ABS_D(objR->speed.x);

        ol_L = overlap * (vxL / (vxL + vxR));
        ol_R = overlap * (vxR / (vxL + vxR));

        printf("ol_L: %g, ol_R: %g\n", ol_L, ol_R);
    }
    else {
        ol_L = ol_R = 0.0;
        printf("objects doesn't move!!! : ol_L: %g, ol_R: %g\n", ol_L, ol_R);
    }
}

bool collision_1D::check() {                
    
    double xa = objL->newpos.x;
    double xb = objR->newpos.x;                    

    double distance;    
    double min_distance;                

    double prev_xa = objL->pos.x;
    double prev_xb = objR->pos.x;

    if(prev_xa < prev_xb) {
        min_distance = objL->get_xR_size() + objR->get_xL_size();
        if(xa < xb) {
            distance = ABS_D(xb - xa);        
            if((min_distance - distance) > 0) {
                is = true;
                overlap = ABS_D(min_distance - distance);
            }
        }
        else if((min_distance - distance) == 0) {
            printf("%s\n", "????????? 1 ");                    
            // overlap = 0;
            assert(false);
        } else {  //b pass thought a
            distance = ABS_D(xb - xa);
            overlap = distance + min_distance;
            is = true;
        }
    }
    if(prev_xa == prev_xb) {
        printf("%s\n", "????????? 3 ");                    
        assert(false);
    }
    else {
        min_distance = objL->get_xL_size() + objR->get_xR_size();
        if(xb < xa) {
            distance = ABS_D(xa - xb);        
            if((min_distance - distance) > 0) {
                is = true;
                overlap = ABS_D(min_distance - distance);
            }
        }
        else if((min_distance - distance) == 0) {
            printf("%s\n", "????????? 2 ");                    
            // overlap = 0;
            assert(false);
        }
        else {  //b pass thought a
            distance = ABS_D(xa - xb);
            overlap = distance + min_distance;
            is = true;
        }        
    }
    if(is) {
        return true;
    }
    else {        
        printf("%c", '.');
        fflush(stdout);
        overlap = 0;
        this->is = false;
        return false;
    }   
    return false;      
}

void collision_1D::calculate_new_speed() {
    double vxa1 = objL->speed.x;
    double vxb1 = objR->speed.x;
    double ma = objL->mass;
    double mb = objR->mass;
    double vxa2;
    double vxb2;

    if(ma == -1) {
        vxb2 = -vxb1;
    }
    else 
    if(mb == -1) {
        vxa2 = -vxa1;
    }
    else {
        vxa2 = (vxa1 * (ma - mb) + 2 * mb * vxb1)/(ma + mb);
        vxb2 = (vxb1 * (mb - ma) + 2 * ma * vxa1)/(ma + mb);
    }

    objL->speed.x = vxa2;
    objR->speed.x = vxb2;
}

void collision_1D::set_new_position() {
    double xa = objL->pos.x;
    double xb = objR->pos.x;            

    if(xa < xb) {                            
        objL->newpos.x = xa - ol_L;
        objR->newpos.x = xb + ol_R;
    }
    else {
        objL->newpos.x = xa + ol_L;
        objR->newpos.x = xb - ol_R;
    }
}    

/************************************************************************************** */
animation_1D::animation_1D() 
:
    windows_x_size {1600},
    windows_y_size {200},
    position_y {windows_y_size / 2},
    wall_L {sf::Vector2<double> {0.0, static_cast<double>(position_y)}},
    wall_R {sf::Vector2<double> {static_cast<double>(windows_x_size), static_cast<double>(position_y)}},
    frame_per_second {60}
{

}

void animation_1D::init() {        
    objs_number = 5;
    int objs_size_diff = 4;   
    int base_r = 10;        

    //set object size
    int speed_range = 10;
    for(size_t i = 0; i < objs_number; ++i) {
        double initial_speed = (rand() % speed_range) * frame_per_second;
        printf("D_initial_speed: %g\n", initial_speed);
        assert(initial_speed < 10 * 60);
        objs.emplace_back(
            ball_2D(
                sf::CircleShape(base_r + rand()%(base_r * objs_size_diff)),                
                sf::Vector2<double>((i%2) 
                    ? initial_speed
                    : (-1 * initial_speed)
                , 0)                
            )
        );        
    }

    //set object color
    for(size_t i = 0; i < objs_number; ++i) {
        size_t color_nr = i % 3;
        objs[i].shape.setFillColor(
            color_nr == 0 
            ? sf::Color::Blue 
            : color_nr == 1 ? sf::Color::Red : sf::Color::Green
        );
    }
    
    //beginning arrangement of objects
    int delta_place = windows_x_size / (objs_number + 3);
    for(size_t i = 0; i < objs_number; ++i) {
        objs[i].setPosition(
            objs[i].get_xL_size() + ((i + 1) * delta_place),
            position_y            
        );
    }  

    for(size_t i = 0; i < objs_number; ++i) {
        collisions.emplace_back( collision_1D{wall_L, objs[i]});
        collisions.emplace_back( collision_1D{objs[i], wall_R});
        for(size_t j = i + 1; j < objs_number; ++j) {
            collisions.emplace_back( collision_1D{objs[i], objs[j]} );
            collisions.emplace_back( collision_1D{objs[j], objs[i]} );
        }
    }
}

void animation_1D::calculate_positions() { 
    
    const double time_unit = 1.0 / frame_per_second;   //1sec/display_speed
    //0. assuming that dt == time_unit
    double dt = time_unit;        
    double rest_time = 0;
    bool at_least_one_collision = false;
    rest_time = 0;
    dt = time_unit;
    printf("D0a: time_unit: %g, dt: %g, rest_time: %g  \n", time_unit, dt, rest_time );
    do {            
        printf("D0a: time_unit: %g, dt: %g, rest_time: %g  \n", time_unit, dt, rest_time );
        assert(rest_time <= time_unit);
        //1. calculating new position based on current obiects speed and dt
        for(auto& o: objs) {
            o.newpos.x = o.pos.x + o.speed.x * dt;
            printf("D1: newpos: %g, pos:%g, speed:%g\n", o.newpos.x, o.pos.x, o.speed.x);
        }
        //2. checking collisions and calcualting overap
        at_least_one_collision = false;
        for(auto& c: collisions) {
            c.clear();
            if(c.check() == true) {
                at_least_one_collision = true;                    
                c.calculate_dt(dt);
            }     
        }        
        //if collision:   //remembering in some way accumulation of next dts
        if(at_least_one_collision) {
            //3. choosing maximal overlap
            collision_1D& first_collision = *(min_element(collisions.begin(), collisions.end(),
                [](auto& a, auto& b) { return a.collision_dt > b.collision_dt; }
            ));
            //4. calculating bigger part of overlap OB (faster obiect)
            first_collision.calculate_overlap_proportion();
            //5. calulating dt based on comparing that OB with distance throuout by that
            //   faster object in unit_time
            printf("D_first_collision: objL->speed.x:%g, objR->speed.x:%g\n", first_collision.objL->speed.x, first_collision.objR->speed.x);            
            dt = first_collision.collision_dt;

            printf("D2a: dt: %g\n", dt );
            assert(dt <= time_unit);

            for(auto& o: objs) {
                o.newpos.x = o.pos.x + o.speed.x * dt;
                printf("D2 :newpos: %g, pos:%g, speed:%g\n", o.newpos.x, o.pos.x, o.speed.x);
            }

            //set current new position           
            for(auto& o: objs) {                    
                o.setPosition(o.newpos);
            }

            first_collision.calculate_new_speed();                                

            rest_time += dt;
            dt = time_unit - rest_time;
            printf("D3a: time_unit: %g, dt: %g, rest_time: %g  \n", time_unit, dt, rest_time );
        }
        else {
            //set current new position           
            for(auto& o: objs) {                    
                o.setPosition(o.newpos);
            }

            rest_time += dt;
            dt = time_unit - rest_time;                
        }            
    } while(time_unit - rest_time > 0);    
} 
        

#undef ABS_D