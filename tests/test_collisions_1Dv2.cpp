#include <gtest/gtest.h>
#include "../collisions_1Dv2.h"
#include <cmath>

using namespace std;


TEST(test_ball_2D, test_01) {
    ball_2D b1{sf::CircleShape(10.0), sf::Vector2<double>{2.0, -3.0}};
    EXPECT_EQ(10.0, b1.get_xL_size());
    EXPECT_EQ(10.0, b1.get_xR_size());
    EXPECT_EQ(2.0, b1.speed.x);
    EXPECT_EQ(-3.0, b1.speed.y);
    double expected_mass = (4.0/3.0) * 3.14 * std::pow(10.0, 3);
    EXPECT_EQ(expected_mass , b1.mass);
    EXPECT_EQ(0.0, b1.pos.x);
    EXPECT_EQ(0.0, b1.pos.y);
    EXPECT_EQ(0.0, b1.newpos.x);
    EXPECT_EQ(0.0, b1.newpos.y);

    ball_2D b2{sf::CircleShape(11.0)};
    EXPECT_EQ(11.0, b2.get_xL_size());
    EXPECT_EQ(11.0, b2.get_xR_size());
    EXPECT_EQ(0.0, b2.speed.x);
    EXPECT_EQ(0.0, b2.speed.y);
    expected_mass = (4.0/3.0) * 3.14 * std::pow(11.0, 3);
    EXPECT_EQ(expected_mass , b2.mass);
    EXPECT_EQ(0.0, b2.pos.x);
    EXPECT_EQ(0.0, b2.pos.y);
    EXPECT_EQ(0.0, b2.newpos.x);
    EXPECT_EQ(0.0, b2.newpos.y);

    b2.setPosition(sf::Vector2<double>{9.0, 19.0});
    EXPECT_EQ(11.0, b2.get_xL_size());
    EXPECT_EQ(11.0, b2.get_xR_size());
    EXPECT_EQ(0.0, b2.speed.x);
    EXPECT_EQ(0.0, b2.speed.y);
    EXPECT_EQ(expected_mass , b2.mass);
    EXPECT_EQ(9.0, b2.pos.x);
    EXPECT_EQ(19.0, b2.pos.y);
    EXPECT_EQ(9.0, b2.newpos.x);
    EXPECT_EQ(19.0, b2.newpos.y);       

    b2.setPosition(19.0, 29.0);
    EXPECT_EQ(11.0, b2.get_xL_size());
    EXPECT_EQ(11.0, b2.get_xR_size());
    EXPECT_EQ(0.0, b2.speed.x);
    EXPECT_EQ(0.0, b2.speed.y);
    EXPECT_EQ(expected_mass , b2.mass);
    EXPECT_EQ(19.0, b2.pos.x);
    EXPECT_EQ(29.0, b2.pos.y);
    EXPECT_EQ(19.0, b2.newpos.x);
    EXPECT_EQ(29.0, b2.newpos.y);           
}

TEST(test_wall_1D, test_01){
    wall_1D w1;
    EXPECT_EQ(0.0, w1.pos.x);
    EXPECT_EQ(0.0, w1.newpos.x);
    EXPECT_EQ(0.0, w1.pos.y);
    EXPECT_EQ(0.0, w1.newpos.y);
    EXPECT_EQ(0.0, w1.speed.x);
    EXPECT_EQ(0.0, w1.speed.y);
    EXPECT_EQ(0.0, w1.get_xL_size());
    EXPECT_EQ(0.0, w1.get_xR_size());
    EXPECT_EQ(-1.0, w1.mass);
    w1.setPosition(sf::Vector2<double> {12.0, 13.0});
    EXPECT_EQ(12.0, w1.pos.x);
    EXPECT_EQ(12.0, w1.newpos.x);
    EXPECT_EQ(13.0, w1.pos.y);
    EXPECT_EQ(13.0, w1.newpos.y);
    EXPECT_EQ(0.0, w1.speed.x);
    EXPECT_EQ(0.0, w1.speed.y);
    EXPECT_EQ(0.0, w1.get_xL_size());
    EXPECT_EQ(0.0, w1.get_xR_size());
    EXPECT_EQ(-1.0, w1.mass);   
    wall_1D w2(sf::Vector2<double> {14.0, 15.0});
    EXPECT_EQ(14.0, w2.pos.x);
    EXPECT_EQ(14.0, w2.newpos.x);
    EXPECT_EQ(15.0, w2.pos.y);
    EXPECT_EQ(15.0, w2.newpos.y);
    EXPECT_EQ(0.0, w2.speed.x);
    EXPECT_EQ(0.0, w2.speed.y);
    EXPECT_EQ(0.0, w2.get_xL_size());
    EXPECT_EQ(0.0, w2.get_xR_size());
    EXPECT_EQ(-1.0, w2.mass);   
    w2.setPosition(16.0, 18.0);
    EXPECT_EQ(16.0, w2.pos.x);
    EXPECT_EQ(16.0, w2.newpos.x);
    EXPECT_EQ(18.0, w2.pos.y);
    EXPECT_EQ(18.0, w2.newpos.y);
    EXPECT_EQ(0.0, w2.speed.x);
    EXPECT_EQ(0.0, w2.speed.y);
    EXPECT_EQ(0.0, w2.get_xL_size());
    EXPECT_EQ(0.0, w2.get_xR_size());
    EXPECT_EQ(-1.0, w2.mass);   
}

class test_collision_1D : public testing::Test {
    protected:
        double position_y;  //collision_dt matters

        wall_1D w1;
        wall_1D w2;
        ball_2D b1;        
        ball_2D b2;

        collision_1D c1;
        collision_1D c2;
        collision_1D c3;
        
    test_collision_1D() 
    :
        position_y {100.0},
        w1 {sf::Vector2<double>{0.0, position_y}},
        w2 {sf::Vector2<double>{200.0, position_y}},

        b1 {sf::CircleShape{10.0}, sf::Vector2<double>{10.0, position_y}},
        b2 {sf::CircleShape{20.0}, sf::Vector2{30.0, position_y}},

        c1{w1, b1},
        c2{b1, b2},
        c3{b2, w2} 
    {}

    void SetUp() override {
    }
    void TearDown() override {
    }
};

TEST_F(test_collision_1D, test_creation){
    EXPECT_EQ(c1.objL, &w1);
    EXPECT_EQ(c1.objR, &b1);
    EXPECT_EQ(c2.objL, &b1);
    EXPECT_EQ(c2.objR, &b2);

    EXPECT_EQ(0, c1.overlap);
    EXPECT_EQ(0, c1.ol_L);
    EXPECT_EQ(0, c1.ol_R);
    EXPECT_EQ(-1.0, c1.collision_dt);
    EXPECT_EQ(position_y, c1.position_y);
}

TEST_F(test_collision_1D, test_check_y_dimetion_neutral){
    double b1_right_x;
    double b2_left_x;
    double b1_left_x;
    bool c1_check;
    bool c2_check;
    bool c3_check;
    
    b1_left_x = b1.get_xL_size();
    b1.pos.x = b1_left_x + 1.0;
    b1.newpos.x = b1_left_x - 2.0;      //movement simulation
    // b1.speed.x = 10.0;               //not real in movement simulation, and not important here

    b1.newpos.y = 100.0;
    b1.pos.y = 100;
    EXPECT_EQ(100.0, b1.newpos.y);
    EXPECT_EQ(100.0, b1.pos.y);

    c1.is = false;
    c1.overlap = 0.0;
    EXPECT_EQ(0.0, c1.overlap);
    EXPECT_EQ(false, c1.is);
    
    c1_check = c1.check();

    EXPECT_EQ(2.0, c1.overlap);
    EXPECT_EQ(true, c1_check);
    EXPECT_EQ(true, c1.is);

    EXPECT_EQ(100.0, b1.newpos.y);
    EXPECT_EQ(100.0, b1.pos.y);
}

TEST_F(test_collision_1D, test_check){
    double b1_right_x;
    double b2_left_x;
    double b1_left_x;
    bool c1_check;
    bool c2_check;
    bool c3_check;

    //collision with left wall: not pass throught
    b1_left_x = b1.get_xL_size();
    b1.pos.x = b1_left_x + 1.0;
    b1.newpos.x = b1_left_x - 2.0;      //movement simulation
    // b1.speed.x = 10.0;               //not real in movement simulation, and not important here
    
    c1.is = false;
    c1.overlap = 0.0;
    EXPECT_EQ(0.0, c1.overlap);
    EXPECT_EQ(false, c1.is);
    
    c1_check = c1.check();

    EXPECT_EQ(2.0, c1.overlap);
    EXPECT_EQ(true, c1_check);
    EXPECT_EQ(true, c1.is);

    //collision with left wall: pass throught    ////////////////////////// TODO
    //TODO

    //collision two balls: not pass through
    b1_right_x = b1.get_xR_size();
    b2_left_x = b2.get_xL_size();    
    b1.pos.x = 10.0;                            //movement simuation  (opposite direction)  -> <-
    b1.newpos.x = 20.0;
    b2.pos.x = 20.0 + b1_right_x + b2_left_x + 10;
    b2.newpos.x = 20.0 + b1_right_x + b2_left_x - 4;
    // b1.speed.x = 30.0;                       //not real in movement simulation, and not important here
    // b2.speed.x = -10.0;

    c2.is = false;
    c2.overlap = 0.0;
    EXPECT_EQ(0.0, c2.overlap);    
    EXPECT_EQ(false, c2.is);

    c2_check = c2.check();

    EXPECT_EQ(4.0, c2.overlap);
    EXPECT_EQ(true, c2_check);
    EXPECT_EQ(true, c2.is);

    //collision two balls: pass through: little
    b1_right_x = b1.get_xR_size();
    b2_left_x = b2.get_xL_size();    
    b1.pos.x = 10.0;                            //movement simuation  (opposite direction)  -> <-
    b1.newpos.x = 20.0;
    b2.pos.x = 20.0 + b1_right_x + b2_left_x + 10;
    b2.newpos.x = 20.0 - 4;
    // b1.speed.x = 30.0;                       //not real in movement simulation, and not important here
    // b2.speed.x = -10.0;

    c2.is = false;
    c2.overlap = 0.0;
    EXPECT_EQ(0.0, c2.overlap);    
    EXPECT_EQ(false, c2.is);

    c2_check = c2.check();

    EXPECT_EQ(4.0 + b1_right_x + b2_left_x, c2.overlap);
    EXPECT_EQ(true, c2_check);
    EXPECT_EQ(true, c2.is);

    //collision two balls: pass through: much
    b1_right_x = b1.get_xR_size();
    b2_left_x = b2.get_xL_size();    
    b1.pos.x = 10.0;                            //movement simuation  (opposite direction)  -> <-
    b1.newpos.x = 20.0;
    b2.pos.x = 20.0 + b1_right_x + b2_left_x + 10;
    b2.newpos.x = 20.0 - b1.get_xL_size() - b2.get_xR_size() + 4;
    // b1.speed.x = 30.0;                       //not real in movement simulation, and not important here
    // b2.speed.x = -10.0;

    c2.is = false;
    c2.overlap = 0.0;
    EXPECT_EQ(0.0, c2.overlap);    
    EXPECT_EQ(false, c2.is);

    c2_check = c2.check();

    EXPECT_EQ(
        b1_right_x + b2_left_x + b1.get_xL_size() + b2.get_xR_size() - 4
        , c2.overlap);
    EXPECT_EQ(true, c2_check);
    EXPECT_EQ(true, c2.is);        
    
    //collision two balls: pass through: very much
    b1_right_x = b1.get_xR_size();
    b2_left_x = b2.get_xL_size();    
    b1.pos.x = 10.0;                            //movement simuation  (opposite direction)  -> <-
    b1.newpos.x = 20.0;
    b2.pos.x = 20.0 + b1_right_x + b2_left_x + 10;
    b2.newpos.x = 20.0 - b1.get_xL_size() - b2.get_xR_size() - 4;
    // b1.speed.x = 30.0;                       //not real in movement simulation, and not important here
    // b2.speed.x = -10.0;

    c2.is = false;
    c2.overlap = 0.0;
    EXPECT_EQ(0.0, c2.overlap);    
    EXPECT_EQ(false, c2.is);

    c2_check = c2.check();

    EXPECT_EQ(
        b1_right_x + b2_left_x + b1.get_xL_size() + b2.get_xR_size() + 4
        , c2.overlap);
    EXPECT_EQ(true, c2_check);
    EXPECT_EQ(true, c2.is);     


    //collision two balls: not pass through
    b1_right_x = b1.get_xR_size();
    b2_left_x = b2.get_xL_size();    
    b1.pos.x = 10.0;                          //movement simuation: the same direction   ->  -> 
    b1.newpos.x = 50.0;
    b2.pos.x = 30.0;
    b2.newpos.x = 50.0 + b1_right_x + b2_left_x - 4;
    // b1.speed.x = 30.0;                     //not real in movement simulation, and not important here
    // b2.speed.x = 10.0;

    c2.is = false;
    c2.overlap = 0.0;
    EXPECT_EQ(0.0, c2.overlap);    
    EXPECT_EQ(false, c2.is);

    c2_check = false;
    c2_check = c2.check();

    EXPECT_EQ(4.0, c2.overlap);
    EXPECT_EQ(true, c2_check);
    EXPECT_EQ(true, c2.is);

    //collision two balls: pass through  little
    b1_right_x = b1.get_xR_size();
    b2_left_x = b2.get_xL_size();    
    b1.pos.x = 10.0;                          //movement simuation: the same direction   ->  -> 
    b1.newpos.x = 50.0 + b2.get_xR_size() - 4;
    b2.pos.x = 30.0;
    b2.newpos.x = 50.0;
    // b1.speed.x = 30.0;                     //not real in movement simulation, and not important here
    // b2.speed.x = 10.0;

    c2.is = false;
    c2.overlap = 0.0;
    EXPECT_EQ(0.0, c2.overlap);    
    EXPECT_EQ(false, c2.is);

    c2_check = false;
    c2_check = c2.check();

    EXPECT_EQ(
        b1_right_x + b2_left_x + b2.get_xR_size() - 4
        , c2.overlap);
    EXPECT_EQ(true, c2_check);
    EXPECT_EQ(true, c2.is);

    //collision two balls: pass through  much
    b1_right_x = b1.get_xR_size();
    b2_left_x = b2.get_xL_size();    
    b1.pos.x = 10.0;                          //movement simuation: the same direction   ->  -> 
    b1.newpos.x = 50.0 + b2.get_xR_size() + b1.get_xL_size() - 4;
    b2.pos.x = 30.0;
    b2.newpos.x = 50.0;
    // b1.speed.x = 30.0;                     //not real in movement simulation, and not important here
    // b2.speed.x = 10.0;

    c2.is = false;
    c2.overlap = 0.0;
    EXPECT_EQ(0.0, c2.overlap);    
    EXPECT_EQ(false, c2.is);

    c2_check = false;
    c2_check = c2.check();

    EXPECT_EQ(
        b1_right_x + b2_left_x + b2.get_xR_size() + b1.get_xL_size() - 4
        , c2.overlap);
    EXPECT_EQ(true, c2_check);
    EXPECT_EQ(true, c2.is);


    //collision two balls: pass through  very much
    b1_right_x = b1.get_xR_size();
    b2_left_x = b2.get_xL_size();    
    b1.pos.x = 10.0;                          //movement simuation: the same direction   ->  -> 
    b1.newpos.x = 50.0 + b2.get_xR_size() + b1.get_xL_size() + 4;
    b2.pos.x = 30.0;
    b2.newpos.x = 50.0;
    // b1.speed.x = 30.0;                     //not real in movement simulation, and not important here
    // b2.speed.x = 10.0;

    c2.is = false;
    c2.overlap = 0.0;
    EXPECT_EQ(0.0, c2.overlap);    
    EXPECT_EQ(false, c2.is);

    c2_check = false;
    c2_check = c2.check();

    EXPECT_EQ(
        b1_right_x + b2_left_x + b2.get_xR_size() + b1.get_xL_size() + 4
        , c2.overlap);
    EXPECT_EQ(true, c2_check);
    EXPECT_EQ(true, c2.is);

    //collision with right wall : not pass through
    // b2.speed.x = 20.0;                   //not real in movement simulation, and not important here
    b2.pos.x = w2.pos.x - b2.get_xR_size() - 5;
    b2.newpos.x = w2.pos.x - b2.get_xR_size() + 5;
    
    c3.is = false;
    c3.overlap = 0.0;
    EXPECT_EQ(0.0, c3.overlap);    
    EXPECT_EQ(false, c3.is);

    c3_check = c3.check();

    EXPECT_EQ(5.0, c3.overlap);
    EXPECT_EQ(true, c3_check);
    EXPECT_EQ(true, c3.is);


    //collision with right wall : not pass through  /////////////////////// TODO
    //TODO    
}

TEST_F(test_collision_1D, test_overlap){
    double b1_left_x = b1.get_xL_size();
    b1.setPosition(b1_left_x - 2.0, position_y);
    b1.speed.x = 10.0;
    c1.overlap = 2.0;  //!!!  check sets this
    c1.calculate_overlap_proportion();
    EXPECT_EQ(0.0, c1.ol_L);
    EXPECT_EQ(2.0, c1.ol_R);  //100%

    double b1_right_x = b1.get_xR_size();
    double b2_left_x = b2.get_xL_size();    
    b1.setPosition(20.0, position_y);
    b2.setPosition(20.0 + b1_right_x + b2_left_x - 4, position_y);
    b1.speed.x = 30.0;
    b2.speed.x = -10.0;
    c2.overlap = 4.0;  //!!! check sets this
    c2.calculate_overlap_proportion();
    EXPECT_EQ(0.75 * 4.0, c2.ol_L);  //3/4 -> 0.75 * 4.0
    EXPECT_EQ(0.25 * 4.0, c2.ol_R);  //1/4 -> 0.25 * 4.0

    b2.speed.x = 20.0;
    c2.overlap = 6.0;  //!!! check sets this
    c2.calculate_overlap_proportion();
    EXPECT_EQ((3.0/5.0) * 6.0, c2.ol_L);  //3/5  * 6.0
    EXPECT_EQ((2.0/5.0) * 6.0, c2.ol_R);  //2/5  * 6.0

    b2.setPosition(w2.pos.x - b2.get_xR_size() - 5, position_y);
    c3.overlap = 5.0;
    c3.calculate_overlap_proportion();
    EXPECT_EQ(5.0, c3.ol_L);  //100%
    EXPECT_EQ(0.0, c3.ol_R);  


    //not moving object,  placed as overlapping
    b2.setPosition(w2.pos.x - b2.get_xR_size() - 5, position_y);
    b2.speed.x = 0.0;
    c3.overlap = 5.0;
    c3.calculate_overlap_proportion();
    EXPECT_EQ(0.0, c3.ol_L);
    EXPECT_EQ(0.0, c3.ol_R);
    //msg: objects doesn't move!!!...      
}

TEST_F(test_collision_1D, test_clear){    
    double b1_right_x = b1.get_xR_size();
    double b2_left_x = b2.get_xL_size();    
    b1.setPosition(20.0, position_y);
    b2.setPosition(20.0 + b1_right_x + b2_left_x - 4, position_y);
    b1.speed.x = 30.0;
    b2.speed.x = -10.0;
    c2.overlap = 4.0;   //!!! check sets this
    c2.calculate_overlap_proportion();
    c2.is = true;       //!!! check sets this
    c2.collision_dt = 11.5;    //!!! check sets this
    EXPECT_EQ(0.75 * 4.0, c2.ol_L); 
    EXPECT_EQ(0.25 * 4.0, c2.ol_R); 
    EXPECT_EQ(4.0, c2.overlap); 
    EXPECT_EQ(true, c2.is);  
    EXPECT_EQ(11.5, c2.collision_dt);  
    c2.clear();
    EXPECT_EQ(0.0, c2.ol_L); 
    EXPECT_EQ(0.0, c2.ol_R); 
    EXPECT_EQ(0.0, c2.overlap);  
    EXPECT_EQ(false, c2.is);  
    EXPECT_EQ(-1.0, c2.collision_dt);  
}


TEST_F(test_collision_1D, test_new_speed){

}



TEST(test_animation_1D, test_01) {

}
