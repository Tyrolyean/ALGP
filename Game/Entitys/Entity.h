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

/*
 * -----------------------------------------------------------------------------
 * This class is only to be used as a base for other entities or for
 * static entities which cannot change position.
 * -----------------------------------------------------------------------------
 */

#ifndef ALGP_ENTITY_H
#define ALGP_ENTITY_H

#include <vector>
#include "../Area.h"
#include "../../ALGP.h"

namespace ALGP {

    class Entity {
    public:
        
        Entity(ALGP* a, long double width, long double length, long double height, int entity_id);
        
        Entity(ALGP* a, long double pos_x, long double pos_y, long double pos_z,
            long double width, long double length, long double height,
            double angle_x, double angle_y, double angle_z, Area* ar,
            int entity_id);
        
        
        Entity(const Entity& orig);
        virtual ~Entity();

        long double get_position_x();
        bool set_position_x(long double pos_x);

        long double get_position_y();
        bool set_position_y(long double pos_y);

        long double get_position_z();
        bool set_position_z(long double pos_z);
        
        double get_angle_x();
        bool set_angle_x(double ang_x);
        
        double get_angle_y();
        bool set_angle_y(double ang_y);
        
        double get_angle_z();
        bool set_angle_z(double ang_z);
        
        std::vector<long double> get_last_positions();
        
        bool set_collision_level(int level, bool collision);
        bool get_collision_levels();
        bool clear_collision_levels();

        bool tick();

    private:
        bool tick_lock;
        /*
         * The entity is identified by it's Unique ID.
         */
        long long int uid;
        /* 
         * The positions are saved in the following order:
         * 0: X
         * 1: Y
         * 2: Z
         * This is mostly consistent for all other arrays in this class, but is
         * definitely defined in the generals.h file.
         */
        
        std::vector<long double> positions;
        
        /*
         * The area, the entity is spawned in.
         * 
         */
        Area* player_area;
        
        /*
         * The entity is defined as a basic shape with a length in all 3 axes
         * and an angles the shape can be turned in. The shape is defined by the 
         * id.
         */
        std::vector<long double> object;
        std::vector<double> angles;
        int entity_id;

        /*
         * Collision detection is done in levels, so any object can interact
         * with anything else without disturbing each other, but the actual 
         */
        std::vector<std::pair<int,bool>> collision_layers;
        
    protected:
        /*
         * The last tick value is set when all calculations are over.
         * All updates are held back and all calculations are done with the time
         * when the function was called.
         */
        long long int last_tick_time;
        unsigned short int tick_attempts;
        
        /* Just a pointer to the ALGP object :D*/
        ALGP* algp;
    };

}

#endif /* ALGP_ENTITY_H */

