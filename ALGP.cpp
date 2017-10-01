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
 * Created on August 11, 2017, 7:56 PM
 */

#include "ALGP.h"
#include "Output.h"
#include "Tools.h"

namespace ALGP {

    ALGP::ALGP(long long int gpg_private_key_id_tmp, long long int gpg_public_key_id_tmp) {
        this->gpg_private_key_id = gpg_private_key_id_tmp;
        this->gpg_public_key_id = gpg_public_key_id_tmp;

#if defined _WIN32 || defined __CYGWIN__
        this->gpg_base_dir = getenv("APPDATA") + ALGP_PATH_SEPARATOR + "gnupg" + ALGP_PATH_SEPARATOR;
#else
        this->gpg_base_dir = getenv("HOME") + ALGP_PATH_SEPARATOR + ".gnupg" + ALGP_PATH_SEPARATOR;
#endif
        // Add the default output way
        std::vector<bool> t = {false, true, true, true, true, true, true};
        std::pair < std::vector<bool>, bool> def(t, true);
        std::pair < std::ostream*, std::pair < std::vector<bool>, bool>> tmp(&std::cout, def);
        this->outputs.push_back(tmp);
        
        this->connection_state = 0;

        return;
    }

    ALGP::ALGP(const ALGP& orig) {
        this->gpg_private_key_id = orig.gpg_private_key_id;
        this->gpg_public_key_id = orig.gpg_public_key_id;
        this->gpg_base_dir = orig.gpg_base_dir;
        this->outputs = orig.outputs;
        
        this->connection_state = 0;
    }

    ALGP::~ALGP() {
    }

    bool ALGP::set_gpg_base_dir(std::string dir) {

        if (Tools::check_for_directory(dir)) {
            this->gpg_base_dir = dir;
            return true;

        } else {
            return false;
        }

        return false; // ;)
    }

    std::string ALGP::get_gpg_base_dir() {

        return this->gpg_base_dir;
    }

    bool ALGP::add_output(std::ostream* output, std::vector<bool> output_allow, bool color_allow) {
        bool success = true;

        if (output != NULL && output_allow.size() == (output_type::END_CALL + 1)) {

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

    bool ALGP::remove_output(std::ostream* output) {

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

    std::vector<std::pair<std::ostream*, std::pair<std::vector<bool>, bool>>> ALGP::get_outputs() {

        return this->outputs;
    }

    bool ALGP::set_local_address(std::string laddr) {

        if (get_connection_state() != 0) {
            return false;
        } else {
            this->local_addr = laddr;
            return true;
        }


        return false; // ;)
    }

    std::string ALGP::get_local_address() {
        return this->local_addr;
    }
    
    void ALGP::force_set_local_address(std::string laddr) {

        unsigned short int temp = get_connection_state();
        this->set_connection_state(0);
        if(!set_local_address(laddr)){
            Output::println(output_type::ERROR,"Failed to force set local address! HOW?!",this);
        }
        this->set_connection_state(temp);
        return;
    }
    
    bool ALGP::set_connection_state(unsigned short int code){
        this->connection_state = code;
        return true;
    }

    unsigned short int ALGP::get_connection_state() {
        return this->connection_state;
    }

}
