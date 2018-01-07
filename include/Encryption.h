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
 * File:   Encryption.h
 * Author: tyrolyean
 *
 * Created on July 27, 2017, 9:56 PM
 */

#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <vector>
#include <string>
#include "Client.h"
#include <gpgme.h>

namespace ALGP {

    class Encryption {
    public:
        Encryption(std::string base_directory,ALGP* algp_pt);
        Encryption(const Encryption& orig);
        virtual ~Encryption();
        std::string get_info();
    private:
        std::string base_directory;
        // All keys in here will be freed at object destruction
        std::vector<gpgme_key_t> key_store;
        ALGP* algp;
    };
}

#endif /* ENCRYPTION_H */

