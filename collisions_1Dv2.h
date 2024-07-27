#ifndef COLLISION_1DV2_H
#define COLLISION_1DV2_H

#include <SFML/Graphics.hpp>
#include <vector>

struct object_2D {
    double mass;
    sf::Vector2<double> speed;
    sf::Vector2<double> pos;
    sf::Vector2<double> newpos;  

    virtual double get_xL_size(sf::Vector2<double> line = sf::Vector2<double>{0,0}) = 0;
    
    virtual double get_xR_size(sf::Vector2<double> line = sf::Vector2<double>{0,0}) = 0;
    
    virtual void setPosition(sf::Vector2<double> ps) = 0;

    virtual void setPosition(double x, double y) = 0;
};


struct ball_2D : object_2D {
    sf::CircleShape shape;

    /**
     * @brief Get distance from x to right bcollision_dt of object along line
     * 
     * @param line 
     * @return double 
     */
    double get_xR_size(sf::Vector2<double> line = sf::Vector2<double>{1.0, 0.0}) override;

    double get_xL_size(sf::Vector2<double> line = sf::Vector2<double>{1.0, 0.0}) override;

    void setPosition(sf::Vector2<double> ps) override;

    virtual void setPosition(double x, double y) override;

    ball_2D(sf::CircleShape&& shape_, sf::Vector2<double>&& speed_);

    ball_2D(sf::CircleShape&& shape_);
};


struct wall_1D : object_2D {

    wall_1D();    

    wall_1D(sf::Vector2<double> ps);

    double get_xR_size(sf::Vector2<double> line = sf::Vector2<double>{0,0}) override;

    void setPosition(sf::Vector2<double> ps) override;

    virtual void setPosition(double x, double y) override;
    
    double get_xL_size(sf::Vector2<double> line = sf::Vector2<double>{0,0}) override;
};


struct collision_1D {
    bool is;
    object_2D* objL;
    object_2D* objR;
    double overlap;
    double ol_L;
    double ol_R;
    double collision_dt;
    double position_y; //NOT NEEDED, obj has proper y position inside

    collision_1D(object_2D& oL, object_2D& oR);

    void set(object_2D& oL, object_2D& oR);

    /**
     * @brief set to 0/false:  is, overlap, ol_L, ol_R, collision_dt
     * 
     */
    void clear();

    /**
     * @brief calculates dt after which collision occurs
     * 
     * @return double 
     */
    double calculate_dt(double curr_dt);

    /**
     * @brief calculate how much objects overlap eachother
     * 
     */
    void calculate_overlap_proportion();

    /**
     * @brief calcualting distance, overlap and check if objects colide
     * 
     * @return true 
     * @return false 
     */
    bool check();

    void calculate_new_speed();

    /**
     * @brief not used - Set the new position object
     * 
     */
    void set_new_position();
};


struct animation_1D {
    int windows_x_size;
    int windows_y_size;
    int position_y;
    wall_1D wall_L;
    wall_1D wall_R;

    size_t frame_per_second;
    size_t objs_number;    
        
    std::vector<ball_2D> objs;
    std::vector<collision_1D> collisions;

    animation_1D();

    void init();

    /**
     * @brief call 1 time for SFML frame (inside main SFML loop)
     * 
     */
    void calculate_positions();        
};

#endif // COLLISION_1DV2_H