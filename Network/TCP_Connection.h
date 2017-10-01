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
 * File:   TCP_Connection.h
 * Author: tyrolyean
 *
 * Created on September 29, 2017, 8:47 PM
 */

#include "Connection.h"

#ifndef ALGP_TCP_CONNECTION_H
#define ALGP_TCP_CONNECTION_H

namespace ALGP {

    class TCP_Connection : public Connection{
    public:
        TCP_Connection();
        TCP_Connection(const TCP_Connection& orig);
        virtual ~TCP_Connection();
        // This will connect to the server and, if not already happened
        bool connect_to_server(std::string remote_address, unsigned short int remote_port);
        bool await_connect(int accept_socket);
        
    private:
        std::string remote_address;
        unsigned short int remote_port;

    };

}

#endif /* ALGP_TCP_CONNECTION_H */

