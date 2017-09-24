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
 * Created on July 20, 2017, 1:17 PM
 */

#ifndef ALGP_CLIENT_H
#define ALGP_CLIENT_H

#include "ALGP.h"
#include <string>
#include <iostream>
#include <vector>
#include <utility>

namespace ALGP {

    class Client : public ALGP {
    public:
        Client(std::string username, std::string password, std::string server_hostname,unsigned int server_port,long long int gpg_private_key_id_tmp, long long int gpg_public_key_id_tmp);
        Client(const Client& orig);
        
        virtual ~Client();
        
        bool set_server_port(unsigned int port);
        unsigned int get_server_port();
        
        bool set_server_hostname(std::string address);
        std::string get_server_hostname();
        
        bool set_client_address(std::string client_addr);
        std::string get_client_address();
        
        bool connect();
        
    private:
        
        std::string username;
        std::string passphrase;
        std::string server_hostname;
        std::string client_address;
        unsigned int server_port;

        /*
         * The connection state indicates how the client is connected to the
         * server. It may not be changed artificially. 
         * 
         * 0: No connection has been established.
         * 1: A connection has been established using the TCP/IP protocol
         * 2: A connection has been established using the UDP/IP protocol
         * 3: A connection is being established/destroyed. Stand by
         * 4++ ERROR! IGNORE ALL. 
         * 
         * If an error is found, please report it. Thank you.
         * 
         */
        unsigned short int connection_state;
        
    };
}
#endif /* ALGP_CLIENT_H */

