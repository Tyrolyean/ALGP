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
 * File:   Entity.h
 * Author: tyrolyean
 *
 * Created on August 10, 2017, 8:46 PM
 */

#ifndef ENTITY_H
#define ENTITY_H

#include <vector>

class Entity {
public:
    Entity();
    Entity(long double pos_x, long double pos_y, long double pos_z);
    Entity(const Entity& orig);
    virtual ~Entity();
    
    long double get_position_x();
    bool set_position_x(long double pos_x);
    
    long double get_position_y();
    bool set_position_y(long double pos_y);
    
    long double get_position_z();
    bool set_position_z(long double pos_z);
    
    long double get_velocity_x();
    bool set_velocity_x(long double vel_x); 
    
    long double get_velocity_y();
    bool set_velocity_x(long double vel_y);
    
    long double get_velocity_z();
    bool set_velocity_x(long double vel_z);
    
    bool add
    
    bool tick();
    
private:
    
    /* 
     * The positions are saved in the following order:
     * 0: X
     * 1: Y
     * 2: Z
     * This is mostly consistent for all other arrays in this class.
     */
    std::vector<long double> positions;
    
    // Velocitys are altered tick wise, so to give every entity the exact same
    // chance of moving, all changes to velocity are applied at the same time,
    // or at least that's the idea... I don't know how it'll be implemented.
    std::vector<long double> velocitys;
    std::vector<std::pair<std::vector<long double>,long double>> accelleration;

};

#endif /* ALGP_ENTITY_H */

