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
 * File:   ALGP.cpp
 * Author: tyrolyean
 * 
 * Created on July 20, 2017, 1:17 PM
 */

#include "ALGP.h"
#include <stdlib.h>
#include "generals.h"
#include "Tools.h"

namespace ALGP {

    ALGP::ALGP(std::string username, std::string password, std::string server_hostname) {
        
        // Assign parameters to used variables
        this->username = username;
        this->passphrase = password;
        this->server_hostname = server_hostname;
        
        // Set all variables to the default values
#if defined _WIN32 || defined __CYGWIN__
        this->gpg_base_dir = getenv("APPDATA") + PATH_SEPARATOR + "gnupg" + PATH_SEPARATOR;
#else
        this->gpg_base_dir = getenv("HOME") + PATH_SEPARATOR + ".gnupg" + PATH_SEPARATOR;
#endif
        this->server_port = 4264;
        this->connection_state = 0;
        
        return;
    }

    ALGP::ALGP(const ALGP& orig) {
        
        this->username = orig.username;
        this->passphrase = orig.passphrase;
        this->server_hostname = orig.server_hostname;
        this->server_port = orig.server_port;
        this->outputs.insert(this->outputs.end(),orig.outputs.begin(),orig.outputs.end());
        this->connection_state = 0; // I'm not going to clone connections :|
        
        return;
    }

    ALGP::~ALGP() {
    }
    
    bool ALGP::set_server_port(unsigned int port){
        
        if(this->connection_state != 0){
            // I cannot change port while a connection is open...
            return false;
            
        }else{
            this->server_port = port;
            return true;
        }
        
        return false;// ;)
    }
    
    unsigned int ALGP::get_server_port(){
        
        return this->server_port;
        
    }
    
    bool ALGP::set_gpg_base_dir(std::string dir){
        
        if(Tools::check_for_directory(dir)){
            this->gpg_base_dir = dir;
            return true;
            
        }else{
            return false;
        }
        
        return false; // ;)
    }
    
    std::string ALGP::get_gpg_base_dir(){
        
        return this->gpg_base_dir;
    }

}