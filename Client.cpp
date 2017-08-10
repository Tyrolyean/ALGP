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
#include <stdlib.h>
#include <algorithm>
#include "generals.h"
#include "Tools.h"
#include "Encryption.h"

namespace ALGP {

    Client::Client(std::string username, std::string password, std::string server_hostname) {

        // Assign parameters to used variables
        this->username = username;
        this->passphrase = password;
        this->server_hostname = server_hostname;

        // Set all variables to the default values
#if defined _WIN32 || defined __CYGWIN__
        this->gpg_base_dir = getenv("APPDATA") + ALGP_PATH_SEPARATOR + "gnupg" + ALGP_PATH_SEPARATOR;
#else
        this->gpg_base_dir = getenv("HOME") + ALGP_PATH_SEPARATOR + ".gnupg" + ALGP_PATH_SEPARATOR;
#endif

        std::vector<bool> t = {false, true, true, true, true, true, true};
        std::pair < std::vector<bool>, bool> def(t, true);
        std::pair < std::ostream*, std::pair < std::vector<bool>, bool>> tmp(&std::cout, def);
        this->outputs.push_back(tmp);

        this->server_port = 4264;
        this->connection_state = 0;

        return;
    }

    Client::Client(const Client& orig) {

        this->username = orig.username;
        this->passphrase = orig.passphrase;
        this->server_hostname = orig.server_hostname;
        this->server_port = orig.server_port;
        this->outputs.insert(this->outputs.end(), orig.outputs.begin(), orig.outputs.end());
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

    bool Client::set_gpg_base_dir(std::string dir) {

        if (Tools::check_for_directory(dir)) {
            this->gpg_base_dir = dir;
            return true;

        } else {
            return false;
        }

        return false; // ;)
    }

    std::string Client::get_gpg_base_dir() {

        return this->gpg_base_dir;
    }

    bool Client::add_output(std::ostream* output, std::vector<bool> output_allow, bool color_allow) {
        bool success = true;

        if (output != NULL && output_allow.size() == (output_type::END_CALL+1)) {

            for (int i = 0; i < outputs.size(); i++) {
                if (outputs[i].first == output) {
                    success = false;
                    // No double entries
                    break;
                }
            }

            if (success == true) {
                std::pair < std::vector<bool>, bool> tmp(output_allow, color_allow);
                // Please note that colors are only supported in linux at this point in time.
                std::pair < std::ostream*, std::pair < std::vector<bool>, bool>> fin(output, tmp);
                outputs.push_back(fin);
            }

        } else {
            success = false;
        }

        return success;
    }

    bool Client::remove_output(std::ostream* output) {

        bool success = false;

        for (int i = 0; i < outputs.size(); i++) {

            if (outputs[i].first == output) {
                success = true;
                outputs.erase(outputs.begin() + i);

                break;
            }

        }
        return success;
    }

    std::vector<std::pair<std::ostream*, std::pair<std::vector<bool>, bool>>> Client::get_outputs() {

        return this->outputs;
    }
    
    bool Client::connect(){
        Output::println(output_type::INTERNAL,"Attempting connection to server...",this);
        Encryption encr(this->gpg_base_dir,this);
        Output::println(output_type::INTERNAL,encr.get_info(),this);
        return false;
    }

}