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
 * File:   ALGP.h
 * Author: tyrolyean
 *
 * Created on August 11, 2017, 7:56 PM
 */

#ifndef ALGP_H
#define ALGP_H

#include <string>
#include <vector>
#include <utility>
#include <iostream>
#include "generals.h"

/*
 * This class provides the base for the client and server objects.
 * As both client and server need to store various objects the same way,
 * I thought this would be the most appropriate way.
 * At this point in time it mostly handles encryption tasks.
 */
namespace ALGP {

    class ALGP {
    public:
        ALGP(long long int gpg_private_key_id_tmp, long long int gpg_public_key_id_tmp);
        ALGP(const ALGP& orig);
        virtual ~ALGP();
        
        bool set_gpg_base_dir(std::string dir);
        std::string get_gpg_base_dir();
        
        bool add_output(std::ostream* output, std::vector<bool> output_allow, bool color_allow);
        bool remove_output(std::ostream *output);
        std::vector<std::pair<std::ostream*,std::pair<std::vector<bool>,bool>>> get_outputs();
        
    private:
        std::string gpg_base_dir;
        long long int gpg_private_key_id;
        long long int gpg_public_key_id;
        
        // This vector looks very complicated and indeed it is...
        // Refer to the Output class or the add function to see how it is 
        // structured
        std::vector<std::pair<std::ostream*,std::pair<std::vector<bool>,bool>>> outputs;
        
    };
}

#endif /* ALGP_H */

