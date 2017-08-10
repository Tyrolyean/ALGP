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

#include "Entity.h"

Entity::Entity() {
    this->positions = {0,0,0};
    
    return;
}

Entity::Entity(long double pos_x, long double pos_y, long double pos_z){
    this->positions = {pos_x, pos_y, pos_z};
    
    return;
}

Entity::Entity(const Entity& orig) {
    for(int i = 0; i < orig.positions.size(); i++){
        this->positions[i] = orig[i];
    }
}

Entity::~Entity() {
}

