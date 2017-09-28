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
            std::string server_hostname, unsigned int server_port,
            long long int gpg_private_key_id_tmp, long long int gpg_public_key_id_tmp)
    : ALGP(gpg_private_key_id_tmp, gpg_public_key_id_tmp) {

        // Assign parameters to used variables
        this->username = username;
        this->passphrase = password;
        this->server_hostname = server_hostname;
        this->server_port = server_port;
        this->client_address = "";

        // Set variables to the default values
        this->connection_state = 0;

        return;
    }

    Client::Client(const Client& orig) : ALGP(orig) {

        this->username = orig.username;
        this->passphrase = orig.passphrase;
        this->server_hostname = orig.server_hostname;
        this->server_port = orig.server_port;
        this->connection_state = 0; // I'm not going to clone connections :|
        this->client_address = orig.client_address;

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

    bool Client::set_client_address(std::string client_addr) {

        if (this->connection_state != 0) {
            return false;
        } else {
            this->client_address = client_addr;
            return true;
        }

        return false; // ;)
    }

    std::string Client::get_client_address() {
        return this->client_address;
    }

    bool Client::connect() {

        this->connection_state = 3;

        Output::println(output_type::INTERNAL, "Attempting connection to server...", this);
        Encryption encr(this->get_gpg_base_dir(), this);
        Output::println(output_type::INTERNAL, encr.get_info(), this);

        if (this->client_address == "") {
            // If no local address has been forced auto-detect one
            // This doesn't force the connection to be established over the
            // Internet, it is just to get a valid interface.
            
            
            std::vector<std::string> local_ips = Network::General::get_local_ips(this);
            
            int iterator = 0;
            
            do{
                
                if(!Network::General::check_for_internet(local_ips[iterator],this)){
                    // Remove the element because it is not capable of reaching
                    // the Internet.
                    
                    local_ips.erase(local_ips.begin() + iterator);
                    
                }else{
                    iterator++;
                }
                
            } while(iterator < local_ips.size());
            
            
            if(local_ips.size() == 0){
                // Oops there are no devices left :O
                Output::println(output_type::ERROR,"No internet connections were detected!",this);
                Output::println(output_type::ERROR,"Please manually assign an IP! Line: " + std::to_string(__LINE__),this);
                this->connection_state = 0;
                return false;
                
            }else{
                Output::println(output_type::INTERNAL,"Detected internet connections over IPs:",this);
                
                for(std::string addr :  local_ips){
                    Output::println(output_type::INTERNAL,"  " + addr,this);
                }
                
                this->client_address = local_ips[0];
                
                Output::println(output_type::INTERNAL,"Using " + this->client_address + " to connect to the Internet",this);
            }
            

        }


        return false;
    }

}