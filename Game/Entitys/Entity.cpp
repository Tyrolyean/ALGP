/*
 * Copyright 2017 tyrolyean.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/* 
 * File:   Entity.cpp
 * Author: tyrolyean
 * 
 * Created on August 10, 2017, 8:46 PM
 */

#include <vector>
#include <string.h>

#include "Entity.h"
#include "../../Tools.h"
#include "../../Output.h"

#include "../../generals.h"


namespace ALGP {

    Entity::Entity(ALGP* algp, long double width, long double length, long double height, int entity_id)
    : Entity(algp,  0, 0, 0, width, length, height, 0, 0, 0, NULL, entity_id) {}

    Entity::Entity(ALGP* algp, long double pos_x, long double pos_y, long double pos_z,
            long double width, long double length, long double height,
            double angle_x, double angle_y, double angle_z, Area* a, int
            entity_id) {

        this->positions = {pos_x, pos_y, pos_z};
        this->object = {width, length, height};
        this->player_area = a;
        this->angles = {angle_x, angle_y, angle_z};
        this->entity_id = entity_id;
        this->algp = algp;
        this->last_tick_time = Tools::get_unix_time_millis();
        this->tick_attempts = 0;
        
        this->tick_lock = false;
        
        tick();

        return;
    }

    Entity::Entity(const Entity& orig) {
        // Copying all vectors
        this->positions.clear();
        for (int i = 0; i < orig.positions.size(); i++) {
            this->positions[i] = orig.positions[i];
        }

        this->object.clear();
        for (int i = 0; i < orig.object.size(); i++) {
            this->object[i] = orig.object[i];
        }

        this->angles.clear();
        for (int i = 0; i < orig.angles.size(); i++) {
            this->angles[i] = orig.angles[i];
        }

        this->player_area = orig.player_area;
        this->entity_id = orig.entity_id;
        this->uid = orig.uid;
        
        this->last_tick_time = Tools::get_unix_time_millis();
        this->tick_attempts = 0;
        
        tick();

        return;
    }

    Entity::~Entity() {
    }

    /*
     * Properties. Windows, Linux and MacOS cross compatible, I think...
     * If not, please explain to me, why not...
     */
    
    // Position properties
    long double Entity::get_position_x(){
        return this->positions[ALGP_X_ARRAY_POSITION];
    }
    bool Entity::set_position_x(long double pos_x){
        
        while(this->tick_lock){}
        this->positions[ALGP_X_ARRAY_POSITION] = pos_x;
        
        return true;
    }
    
    long double Entity::get_position_y(){
        return this->positions[ALGP_Y_ARRAY_POSITION];
    }
    bool Entity::set_position_y(long double pos_y){
        
        while(this->tick_lock){}
        this->positions[ALGP_Y_ARRAY_POSITION] = pos_y;
        
        return true;
    }

    long double Entity::get_position_z(){
        return this->positions[ALGP_Z_ARRAY_POSITION];
    }
    bool Entity::set_position_z(long double pos_z){
        
        while(this->tick_lock){}
        this->positions[ALGP_Z_ARRAY_POSITION] = pos_z;
        
        return true;
    }
    
    // Angle properties

    double Entity::get_angle_x(){
        return this->angles[ALGP_X_ARRAY_POSITION];
    }
    
    bool Entity::set_angle_x(double ang_x){
        
        while(this->tick_lock){}
        this->angles[ALGP_X_ARRAY_POSITION] = ang_x;
        
        return true;
    }

    
    
    double Entity::get_angle_y(){
        return this->angles[ALGP_Y_ARRAY_POSITION];
    }
    
    bool Entity::set_angle_y(double ang_y){
        
        while(this->tick_lock){}
        this->angles[ALGP_Y_ARRAY_POSITION] = ang_y;
        
        return true;
    }
    
    

    double Entity::get_angle_z(){
        return this->angles[ALGP_Z_ARRAY_POSITION];
    }
    
    bool Entity::set_angle_z(double ang_z){
        
        while(this->tick_lock){}
        this->angles[ALGP_Z_ARRAY_POSITION] = ang_z;
        
        return true;
    }
    
    /*
     * Functions.
     */

    bool Entity::clear_collision_levels() {

        this->collision_layers.clear();

        return true;

    }
    
    bool Entity::tick(){
        
        if(this->tick_lock){
            /*
             * If the tick lock is still active, when another tick is tried to
             * be executed, the tick may be stuck...
             * This is indeed not good.
             */
            Output::println(output_type::WARNING, "Tick stuck for " + std::to_string(this->uid)
                    +" for " + std::to_string((Tools::get_unix_time_millis() - this->last_tick_time))
                    + "ms! Attempt Nr. " + std::to_string(this->tick_attempts),this->algp);
            
            if(this->tick_attempts > 10){
                // I will force the lock out of place so normal operation can
                // continue and the entity isn't stuck forever.
                Output::println(output_type::ERROR,(std::string)"Tick lock forced out of " +
                        " place on entity " + std::to_string(this->last_tick_time)
                        + "! Attempt threshold exceeded!",this->algp);
                this->tick_lock = false;
                // Please note that this is only a safety measure!
                
            }
            
            return false;
            
        }else{
            this->tick_lock = true;
            long long int actual_tick_start = Tools::get_unix_time_millis();
            // Do ticky things
            
            
            this->last_tick_time = actual_tick_start;
            this->tick_lock = false;
            
            return true;
        }
        
        return false; // ;)
    }



}

