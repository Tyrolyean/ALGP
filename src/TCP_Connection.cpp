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
 * File:   TCP_Connection.cpp
 * Author: tyrolyean
 * 
 * Created on September 29, 2017, 8:47 PM
 */

#include "Network/TCP_Connection.h"
#include "ALGP.h"
#include "Network/General.h"
#include "Output.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>


namespace ALGP {
    namespace Network {

        TCP_Connection::TCP_Connection(ALGP* a, std::string laddr, unsigned short int lport) : 
		Connection(a,laddr,lport) {
        }

        TCP_Connection::TCP_Connection(const TCP_Connection& orig) : Connection(orig) {
        }

        TCP_Connection::~TCP_Connection() {
        }

        bool TCP_Connection::connect_to_server(std::string remote_address, unsigned short int remote_port) {
            bool success = false;
            this->remote_address = remote_address;
            this->remote_port = remote_port;

            if (this->get_connection_type() == AF_INET) {
                // IPv4
                struct sockaddr_in serv_addr, l_addr;
                struct hostent *server;
                struct hostent *local;

                server = gethostbyname(remote_address.c_str());
                local = gethostbyname(this->get_local_address().c_str());
                if (server == NULL) {
                    success = false;
                    Output::println(output_type::ERROR, "Failed to resolve remote address: " + remote_address, this->algp);
                    // ERROR finding host
                } else {

                    //Initialize Client and server
                    memset((char *) &serv_addr, 0, sizeof (serv_addr));
                    serv_addr.sin_family = AF_INET;
                    bcopy((char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr, server->h_length);
                    serv_addr.sin_port = htons(remote_port);

                    memset((char *) &l_addr, 0, sizeof (l_addr));
                    l_addr.sin_family = AF_INET;
                    bcopy((char *) local->h_addr, (char *) &l_addr.sin_addr.s_addr, local->h_length);
                    l_addr.sin_port = htons(this->get_local_port());

                    this->sockfd = General::generate_sockfd(SOCK_STREAM,AF_INET);

                    if (bind(sockfd, (struct sockaddr *) &l_addr, sizeof (l_addr)) < 0) {
                        // Failed to bind
                        Output::println(output_type::ERROR, "Failed binding to address " +
                                this->get_local_address() + " whilst connecting to server at " +
                                remote_address, this->algp);
                        success = false;
                        close(this->sockfd);
                        this->sockfd = 0;

                    } else {
                        // Try to connect to remote
                        if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof (serv_addr)) < 0) {
                            // Failed to connect to remote
                            Output::println(output_type::ERROR, "Failed to connect to server via TCP: " +
                                    remote_address + ":" + std::to_string(remote_port), this->algp);
                            success = false;
                            close(this->sockfd);
                            this->sockfd = 0;
                        }else{
                            Output::println(output_type::INTERNAL,"Successfully connected to server via TCP: " +
                                   remote_address + ":" + std::to_string(remote_port),this->algp);
                            success =true;
                        }

                    }

                }


            } else if (this->get_connection_type() == AF_INET6) {
                // IPv6
                struct sockaddr_in6 serv_addr, l_addr;
                struct hostent *server;
                struct hostent *local;

                server = gethostbyname(remote_address.c_str());
                local = gethostbyname(this->get_local_address().c_str());
                if (server == NULL) {
                    success = false;
                    Output::println(output_type::ERROR, "Failed to resolve remote address: " + remote_address, this->algp);
                    // ERROR finding host
                } else {

                    //Initialize Client and server
                    memset((char *) &serv_addr, 0, sizeof (serv_addr));
                    serv_addr.sin6_family = AF_INET6;
                    bcopy((char *) server->h_addr, (char *) &serv_addr.sin6_addr, server->h_length);
                    serv_addr.sin6_port = htons(remote_port);

                    memset((char *) &l_addr, 0, sizeof (l_addr));
                    l_addr.sin6_family = AF_INET;
                    bcopy((char *) local->h_addr, (char *) &l_addr.sin6_addr, local->h_length);
                    l_addr.sin6_port = htons(this->get_local_port());

                    this->sockfd = General::generate_sockfd(SOCK_STREAM,AF_INET6);

                    if (bind(sockfd, (struct sockaddr *) &l_addr, sizeof (l_addr)) < 0) {
                        // Failed to bind
                        Output::println(output_type::ERROR, "Failed binding to address " +
                                this->get_local_address() + " whilst connecting to server at " +
                                remote_address, this->algp);
                        success = false;
                        close(this->sockfd);
                        this->sockfd = 0;

                    } else {
                        // Try to connect to remote
                        if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof (serv_addr)) < 0) {
                            // Failed to connect to remote
                            Output::println(output_type::ERROR, "Failed to connect to server via TCP: " +
                                    remote_address + ":" + std::to_string(remote_port), this->algp);
                            success = false;
                            close(this->sockfd);
                            this->sockfd = 0;
                        }else{
                            Output::println(output_type::INTERNAL,"Successfully connected to server via TCP: " +
                                    remote_address + ":" + std::to_string(remote_port),this->algp);
                            success =true;
                        }

                    }

                }

            } else {
                // Exception Handling at it's best
                Output::println(output_type::WARNING, "Trying to connect with unknown IP sub-protocol: " + std::to_string(this->get_connection_type()), this->algp);
                success = false;

            }

            // Cleanup
            if (success) {
                this->connection_state = connection_type::TCP;
            } else {
                this->connection_state = connection_type::DISCONNECTED;
            }

            return success;
        }
    }
}
