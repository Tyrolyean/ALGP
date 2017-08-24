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
 * File:   Area.h
 * Author: tyrolyean
 *
 * Created on August 11, 2017, 7:52 PM
 */

/*
 * -----------------------------------------------------------------------------
 * An area is a 3-dimensional space within all players can see each other
 * (to some extent). A map may consist out of several areas/
 * ----------------------------------------------------------------------------- 
 */

#ifndef ALGP_AREA_H
#define ALGP_AREA_H

namespace ALGP {

    class Area {
    public:
        Area();
        Area(const Area& orig);
        virtual ~Area();
    private:

    };
}
#endif /* ALGP_AREA_H */

