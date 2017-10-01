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
        
        bool set_local_address(std::string laddr);
        std::string get_local_address();
        void force_set_local_address(std::string laddr);
        
        bool set_local_port(unsigned short int lport);
        unsigned short int get_local_port();
        
        /*
         * The connection state can't be updated from anywhere inside the program
         * to ensure it's accuracy.
         */
        unsigned short int get_connection_state();
    protected:
        bool set_connection_state(unsigned short int code);
        
    private:
        std::string gpg_base_dir;
        long long int gpg_private_key_id;
        long long int gpg_public_key_id;
        
        // This vector looks very complicated and indeed it is...
        // Refer to the Output class or the add function to see how it is 
        // structured
        std::vector<std::pair<std::ostream*,std::pair<std::vector<bool>,bool>>> outputs;
        
        /*
         * The connection state indicates how the client is connected to the
         * server. It may not be changed artificially. 
         * 
         * 0: No connection has been established.
         * 1: A connection has been established using the TCP/IP protocol
         * 2: A connection has been established using the UDP/IP protocol
         * 3: A connection is being established/destroyed. Stand by...
         * 4: Connections have been established using TCP and UDP
         * 5++ ERROR! IGNORE ALL.
         * 
         * If an error is found, please report it. Thank you.
         * 
         */
        unsigned short int connection_state;
        
        std::string local_addr;
        unsigned short int local_port;
        
    };
}

#endif /* ALGP_H */

