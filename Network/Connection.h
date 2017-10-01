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
 * File:   Connection.h
 * Author: tyrolyean
 *
 * Created on July 27, 2017, 9:22 PM
 */

#ifndef CONNECTION_H
#define CONNECTION_H

#include <string>
#include <vector>
#include <iostream>
#include "../ALGP.h"
#ifdef _WIN32
#include <windows.h>
#include <winsock2.h>
#endif

/*
 * This is a skeleton class for a real connection. It will include all functions
 * feasible for all children such as println or 
 */

namespace ALGP {

    class Connection {
    public:
        Connection(ALGP* a);
        Connection(const Connection& orig);
        virtual ~Connection();
        
        /*
         * This writes an encrypted line to the server. The encryption keys are
         * provided by the child class. The ALGP command Syntax has to be used.
         */
        bool println(std::string line);

    protected:
        
        #ifndef _WIN32
        // The socket file descriptor
        int sockfd;
#else
        // Winsock
        SOCKET sock;
#endif
        
        /*
         * If a client is provided, the two states will sync up, otherwise
         * it will be completely independent.
         *
         * 0: No connection has been established.
         * 1: A connection has been established using the TCP/IP protocol
         * 2: A connection has been established using the UDP/IP protocol
         * 3: A connection is being established/destroyed. Stand by...
         * 4: Connections have been established using TCP and UDP
         * 5++ ERROR! IGNORE ALL. 
         * 
         * If an error is found, please report it. Thank you.
         */
        unsigned short int connection_state;
        
        
        ALGP* algp;
        
        bool register_command(std::string com);
        
    private:
        /*
         * This stores the last commands received/sent from/to the client.
         * A copy of this vector can be received from the public method, new
         * lines may only be added in clear text by the responsible children
         * via the protected method.
         */
        std::vector<std::string> command_buffer;
        
        /*
         * Every message received will be echoed to all of these streams
         * additionally to being added to the command buffer.
         */
        std::vector<std::ostream> registered_streams;

    };
}
#endif /* CONNECTION_H */

