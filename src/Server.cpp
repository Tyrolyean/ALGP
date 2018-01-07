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
 * File:   Server.cpp
 * Author: tyrolyean
 * 
 * Created on August 10, 2017, 8:03 PM
 */

#include "Server.h"

namespace ALGP {

    Server::Server(std::string address, long long int gpg_private_key_id_tmp, long long int gpg_public_key_id_tmp) 
    : ALGP(gpg_private_key_id_tmp, gpg_public_key_id_tmp) {
        this->server_address = address;
        
        return;
    }

    Server::Server(const Server& orig) : ALGP(orig) {
        this->server_address = orig.server_address;
        
        return;
    }

    Server::~Server() {
    }
    
    bool Server::start(){
        bool success = true;
        
        
        
        return success;
    }
}

