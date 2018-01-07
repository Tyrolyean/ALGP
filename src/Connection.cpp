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
 * File:   Connection.cpp
 * Author: tyrolyean
 * 
 * Created on July 27, 2017, 9:22 PM
 */

#include "Network/Connection.h"
#include "Output.h"
#include <unistd.h>
#include "generals.h"

#include <sys/types.h>
#include <sys/socket.h>

namespace ALGP {

    namespace Network {

        Connection::Connection(ALGP* a, std::string laddr, unsigned short int lport) {

            this->algp = a;
            this->connection_state = 0;
            this->sockfd = 0;
            this->command_lock = false;
            this->laddr = laddr;
            this->lport = lport;
            return;

        }

        Connection::Connection(const Connection& orig) {

            this->algp = orig.algp;
            this->connection_state = 0;
            // Nope, still not gonna do that.
            this->sockfd = 0;
            // Neither that one
            this->command_lock = false;
            // Neither this one
            
            this->laddr = orig.laddr;
            this->lport = orig.lport;
            // But those ones
            
            return;

        }

        Connection::~Connection() {
            if (this->sockfd != 0 && this->connection_state != 0) {
                close(sockfd);
            }

            return;
        }

        bool Connection::println(std::string line) {
            if (sizeof (line.c_str()) < ALGP_BUFFER_SIZE) {
                // BUFFER LENGTH EXCEEDED!
                Output::println(output_type::WARNING, "Unable to send messages which exceed the maximum buffer length:", this->algp);
                Output::println(output_type::WARNING, line, this->algp);
                return false;

            } else {
                if (this->connection_state != 0 && this->connection_state < 5) {
                    int n = send(this->sockfd, line.data(), line.size(), 0);
                    if (n < 0) {
                        return false;
                    } else {
                        // Register the command into the databse
                        return register_command(line);
                    }

                } else {
                    // SOCKET NOT CONNECTED!
                    return false;
                }
            }


            return false;

        }

        std::vector<std::string> Connection::get_command_buffer() {

            while (this->command_lock) {
            }
            return this->command_buffer;
        }

        bool Connection::register_command(std::string com) {

            while (this->command_lock) {
            }

            this->command_lock = true;

            for (std::ostream* str : this->registered_streams) {
                if (str == NULL) {
                    Output::println(output_type::ERROR, "Found NULL-pointer as stream for connection!", this->algp);
                    this->command_lock = false;
                    return false;

                } else {
                    *str << com << std::endl;
                }

            }

            // If all went as planned, add the command to the cache
            if (this->command_buffer.size() > ALGP_COMMAND_BUFFER_SIZE) {

                // Delete the oldest command in the vector to make room
                this->command_buffer.erase(this->command_buffer.begin());
            }

            this->command_buffer.push_back(com);

            this->command_lock = false;

            return true;

        }
    }
}

