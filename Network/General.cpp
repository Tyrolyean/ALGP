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
 * File:   General.cpp
 * Author: tyrolyean
 * 
 * Created on July 23, 2017, 11:28 PM
 */

#include "General.h"
#include "../Output.h"
// Includes on all OS
#include <string.h>
#include <string>
#include <algorithm>
#include <sys/types.h>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#if defined _WIN32
// Windows includes and definitions
#include <winsock2.h>
#else
// Unix includes
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <net/if.h>
#include <netinet/in.h>
#include <ifaddrs.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/ip.h>

#endif


namespace ALGP {
    namespace Network {

        std::vector<std::string> General::get_local_ips(ALGP* a) {

            std::vector<std::string> addrs;

#ifndef _WIN32

            struct ifaddrs * ifAddrStruct = NULL;
            struct ifaddrs * ifa = NULL;
            void * tmpAddrPtr = NULL;


            getifaddrs(&ifAddrStruct);

            for (ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next) {
                if (!ifa->ifa_addr) {
                    continue;
                }
                if (ifa->ifa_addr->sa_family == AF_INET) { // check it is IP4
                    // is a valid IP4 Address
                    tmpAddrPtr = &((struct sockaddr_in *) ifa->ifa_addr)->sin_addr;
                    char addressBuffer[INET_ADDRSTRLEN];
                    inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
                    addrs.push_back(Tools::from_c_str(addressBuffer));
                } else if (ifa->ifa_addr->sa_family == AF_INET6) { // check it is IP6
                    // is a valid IP6 Address
                    tmpAddrPtr = &((struct sockaddr_in6 *) ifa->ifa_addr)->sin6_addr;
                    char addressBuffer[INET6_ADDRSTRLEN];
                    inet_ntop(AF_INET6, tmpAddrPtr, addressBuffer, INET6_ADDRSTRLEN);
                    addrs.push_back(Tools::from_c_str(addressBuffer));
                }
            }
            if (ifAddrStruct != NULL) freeifaddrs(ifAddrStruct);

#else
            //Windows APIs
            WSADATA WSAData;

            // Initialize winsock dll
            if (::WSAStartup(MAKEWORD(1, 0), &WSAData)) {
                // Error handling
            }

            // Get local host name
            char szHostName[128] = "";

            if (::gethostname(szHostName, sizeof (szHostName))) {
                // Error handling -> call 'WSAGetLastError()'
            }

            // Get local IP addresses
            struct sockaddr_in SocketAddress;
            struct hostent *pHost = 0;

            pHost = ::gethostbyname(szHostName);
            if (!pHost) {
                // Error handling -> call 'WSAGetLastError()'
                Output::println(output_type::WARNING, "", a);
            }

            for (int iCnt = 0; ((pHost->h_addr_list[iCnt]) && (iCnt < 10)); ++iCnt) {
                memcpy(&SocketAddress.sin_addr, pHost->h_addr_list[iCnt], pHost->h_length);
                addrs.push_back(Tools::from_c_str(inet_ntoa(SocketAddress.sin_addr)));
            }

            // Cleanup
            WSACleanup();
#endif
            return addrs;
        }
#ifndef _WIN32
        bool General::check_for_internet(std::string local_address, ALGP* a) {

            // Throw out local-only and loopback addresses
            std::vector<std::string> local_blacklist = {"127", "fe80", "::1"};

            for (std::string t : local_blacklist) {

                if (local_address.compare(0, t.length(), t) == 0) {
                    // The address is using an invalid prefix as defined above
                    return false;
                }

            }

            // Check if the address is capable of reaching the internet.
            struct hostent *server;

            server = gethostbyname(ALGP_CHECK_ONLINE_ADDRESS);

            if (server == NULL) {
                Output::println(output_type::ERROR, "DNS seems to be unavailable. LINE: " + std::to_string(__LINE__), a);
                return false;
            }

            struct sockaddr_in serv_addr, localaddr;

            inet_pton(server->h_addrtype, local_address.c_str(), &(localaddr.sin_addr));
            localaddr.sin_addr.s_addr = htons(4264);
            localaddr.sin_family = server->h_addrtype;

            int sockfd = socket(server->h_addrtype, SOCK_STREAM, 0);
            
            
            bind(sockfd, (struct sockaddr *) &localaddr, sizeof (localaddr));
            // Look if an error occured at binding
            int error_code;
            unsigned int error_code_size = sizeof(error_code);
            getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &error_code, &error_code_size);
            
            if(error_code < 0){
                Output::println(output_type::INTERNAL, "Unable to bind to address " + local_address+". ERROR CODE "+std::to_string(error_code), a);
                close(sockfd);
                return false;
            }
            
            bzero((char *) &serv_addr, sizeof (serv_addr));
            serv_addr.sin_family = server->h_addrtype;
            bcopy((char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr,
                    server->h_length);
            serv_addr.sin_port = htons(ALGP_CHECK_ONLINE_PORT);

            if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof (serv_addr)) < 0) {
                Output::println(output_type::INTERNAL, "Unable to connect via local address " + local_address, a);
                //free(server);
                close(sockfd);
                return false;
            } else {
                std::string request = "\
GET / HTTP/1.1\n\
Host: www.gstatic.com\n\
User-Agent: Googlebot/2.1 (+http://www.google.com/bot.html)\n\
Accept: text/html\n\
Accept-Language: en\n\
DNT: 1\n\
Connection: keep-alive\n\
Upgrade-Insecure-Requests: 0\n\n";
                
                write(sockfd,request.c_str(),strlen(request.c_str()));
                
                char buf[1024];
                
                if(read(sockfd, buf, 1024) < 0){
                    Output::println(output_type::INTERNAL, "Unable to receive something for " + local_address, a);
                    //free(server);
                    close(sockfd);
                    return false;
                }else{
                    // Everything has been successful so far.
                    if(Tools::from_c_str(buf).empty()){
                        Output::println(output_type::INTERNAL, "Received garbage for " + local_address, a);
                        close(sockfd);
                        return false;
                    }
                }
                
            }
            
            close(sockfd);
            //free(server);
            return true;

        }
#else
        
#endif

    }
}

