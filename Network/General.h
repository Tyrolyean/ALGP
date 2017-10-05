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
 * File:   General.h
 * Author: tyrolyean
 *
 * Created on July 23, 2017, 11:28 PM
 */

#ifndef GENERAL_H
#define GENERAL_H

#include "../Tools.h"
#include "../ALGP.h"
#include <string.h>
#include <vector>

namespace ALGP {
    namespace Network {

        class General {

        public:
            static std::vector<std::string> get_local_ips(ALGP* a);
            static int get_addr_type(std::string address, ALGP* a);
            
            
#ifndef _WIN32
            static bool check_for_internet(std::string local_address,ALGP* a);
            static int generate_sockfd(int type, int proto);
            static std::string get_local_internet_address(ALGP* a);
#else
            
#endif

        private:

        };

    }
}

#endif /* GENERAL_H */

