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

#include "Client.h"
#include "Output.h"
#include <stdlib.h>
#include <algorithm>
#include "generals.h"
#include "Tools.h"
#include "Encryption.h"
#include "Network/General.h"

namespace ALGP {

    Client::Client(std::string username, std::string password,
            std::string server_hostname,unsigned int server_port,
            long long int gpg_private_key_id_tmp,long long int gpg_public_key_id_tmp)
            : ALGP(gpg_private_key_id_tmp,gpg_public_key_id_tmp){

        // Assign parameters to used variables
        this->username = username;
        this->passphrase = password;
        this->server_hostname = server_hostname;
        this->server_port = server_port;

        // Set variables to the default values
        this->connection_state = 0;

        return;
    }

    Client::Client(const Client& orig) : ALGP(orig){

        this->username = orig.username;
        this->passphrase = orig.passphrase;
        this->server_hostname = orig.server_hostname;
        this->server_port = orig.server_port;
        this->connection_state = 0; // I'm not going to clone connections :|

        return;
    }

    Client::~Client() {
    }

    bool Client::set_server_port(unsigned int port) {

        if (this->connection_state != 0) {
            // I cannot change port while a connection is open...
            return false;

        } else {
            this->server_port = port;
            return true;
        }

        return false; // ;)
    }

    unsigned int Client::get_server_port() {

        return this->server_port;

    }

    bool Client::set_server_hostname(std::string address) {

        if (this->connection_state != 0) {
            return false;
        } else {
            this->server_hostname = address;
            return true;
        }

        return false; // ;)

    }

    std::string Client::get_server_hostname() {
        return this->server_hostname;
    }

    
    
    bool Client::connect(){
        Output::println(output_type::INTERNAL,"Attempting connection to server...",this);
        Encryption encr(this->get_gpg_base_dir(),this);
        Output::println(output_type::INTERNAL,encr.get_info(),this);
        
        Output::println(output_type::INTERNAL,"Available IP addresses: ",this);
        std::vector<std::string> ifs = Network::General::get_local_ips(this);
        for(std::string line : ifs){
            Output::println(output_type::INTERNAL,"  "+line,this);
        }
        
        return false;
    }

}