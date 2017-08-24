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
 * File:   Movable_entity.h
 * Author: tyrolyean
 *
 * Created on August 11, 2017, 3:43 PM
 */

#ifndef ALGP_MOVABLE_ENTITY_H
#define ALGP_MOVABLE_ENTITY_H

#include <vector>
#include <utility>

#include "Entity.h"

namespace ALGP {

    class Movable_entity : public Entity {
    public:

        using Entity::Entity;

        long double get_velocity_x();
        bool set_velocity_x(long double vel_x);

        long double get_velocity_y();
        bool set_velocity_y(long double vel_y);

        long double get_velocity_z();
        bool set_velocity_z(long double vel_z);
        
        bool stop();
        
    private:

        // Velocities are altered tick wise, so to give every entity the exact same
        // chance of moving, all changes to velocity are applied at the same time,
        // or at least that's the idea... I don't know how it'll be implemented.
        std::vector<long double> velocitys;
        std::vector<std::pair<std::vector<long double>, long double>> accelleration;
        std::vector<std::pair<long double, int>> accelleration_targets;
        
    };
}

#endif /* ALGP_MOVABLE_ENTITY_H */

