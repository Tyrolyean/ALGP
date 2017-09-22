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
#ifndef _WIN32
#include <unistd.h>
#endif
#include <stdio.h>
#include <stdlib.h>

#if defined _WIN32
// Windows includes and definitions
#include <winsock2.h>
#include <iphlpapi.h>
#pragma comment(lib, "IPHLPAPI.lib")


#define WORKING_BUFFER_SIZE 15000
#define MAX_TRIES 3

#define MALLOC(x) HeapAlloc(GetProcessHeap(), 0, (x))
#define FREE(x) HeapFree(GetProcessHeap(), 0, (x))

#else
// Unix includes
#include <arpa/inet.h>
#include <netdb.h>
#include <net/if.h>
#include <netinet/in.h>
#include <ifaddrs.h>
#include <sys/socket.h>
#include <sys/ioctl.h>

#endif


namespace ALGP {
    namespace Network {
        
        long int General::get_local_ip(ALGP* a) {
			long long int addr;
#ifndef _WIN32
            // Unix like
            struct ifaddrs *addrs, *tmp;
            getifaddrs(&addrs);
            tmp = addrs;
            int i = 0;
            long int addr;
            while (tmp) {
                if (tmp->ifa_addr && tmp->ifa_addr->sa_family == AF_PACKET) {

                    char *nameTmp = new char();
                    memcpy(nameTmp, tmp->ifa_name, strlen(tmp->ifa_name) + 1);

                    // Copy the name to another position of the RAM to prevent 
                    // segmentation faults! God it's annoying!
                    std::string name(nameTmp);
                    std::ifstream ifs("/sys/class/net/" + name + "/address");
                    std::string macAddress((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>())); // Read the MAC from the system file
                    //Because the file has an endl at the end this must be removed
                    macAddress.erase(remove(macAddress.begin(), macAddress.end(), '\n'), macAddress.end());

                    if (macAddress != "00:00:00:00:00:00") { // Throwing out loopback-addresses
                        if (!(macAddress[0] == '0' && macAddress[1] == '0')) { // Throw out local-managed addresses

                            int fd;
                            struct ifreq ifr;

                            fd = socket(AF_INET, SOCK_DGRAM, 0);

                            ifr.ifr_addr.sa_family = AF_INET;

                            strncpy(ifr.ifr_name, name.c_str(), IFNAMSIZ - 1);

                            ioctl(fd, SIOCGIFADDR, &ifr);

                            close(fd);

                            addr = ntohl(((struct sockaddr_in *) &ifr.ifr_addr)->sin_addr.s_addr);


                            break;

                        }
                    }


                }
                tmp = tmp->ifa_next;
            }

            freeifaddrs(addrs);
            return addr;
#else
            //Windows
				char szBuffer[1024];

#ifdef WIN32
				WSADATA wsaData;
				WORD wVersionRequested = MAKEWORD(2, 0);
				if (::WSAStartup(wVersionRequested, &wsaData) != 0)
					return false;
#endif


				if (gethostname(szBuffer, sizeof(szBuffer)) == SOCKET_ERROR)
				{
#ifdef WIN32
					WSACleanup();
#endif
					return false;
				}

				struct hostent *host = gethostbyname(szBuffer);
				if (host == NULL)
				{
#ifdef WIN32
					WSACleanup();
#endif
					return false;
				}

				//Obtain the computer's IP
				std::vector<std::string> v(host->h_addr_list, host->h_addr_list);

				for (std::string s : v) {
					Output::println(output_type::INFO, s, a);
				}

#ifdef WIN32
				WSACleanup();
#endif
				return 1;
#endif
        }

    }
}

