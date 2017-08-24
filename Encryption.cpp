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
 * File:   Encryption.cpp
 * Author: tyrolyean
 * 
 * Created on July 27, 2017, 9:56 PM
 */

#include "Encryption.h"
#include "Output.h"
#include "Tools.h"
#include <gpgme.h>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>

namespace ALGP {

    Encryption::Encryption(std::string base_directory,ALGP* algp_pt) {

        static bool started;

        if (!Tools::check_for_directory(base_directory)) {

        }
        this->base_directory = base_directory;
        this->algp = algp_pt;

        // Startup sequence
        if (!started) {
            gpgme_check_version(NULL);
            /* Initialize the locale environment.  */
            setlocale(LC_ALL, "");
            gpgme_set_locale(NULL, LC_CTYPE, setlocale(LC_CTYPE, NULL));
#ifdef LC_MESSAGES
            gpgme_set_locale(NULL, LC_MESSAGES, setlocale(LC_MESSAGES, NULL));
#endif
            started = true;
        }
        return;

    }

    Encryption::Encryption(const Encryption& orig) {
        this->base_directory = orig.base_directory;
        // I'm not going to copy the key store.
        // These are literarily too much pointers to handle
        this->algp = orig.algp;
        return;
    }

    Encryption::~Encryption() {

        for (int i = 0; i < key_store.size(); i++) {

            if (key_store[i] != NULL) {

                gpgme_key_release(key_store[i]);

            } else {
                // Someone might have had stupid ideas...
                Output::println(output_type::INTERNAL, "GPG key externally freed! LINE:" + std::to_string(__LINE__), this->algp);
            }

        }

        return;
    }

    std::string Encryption::get_info() {

        gpgme_engine_info_t info;
        gpgme_error_t err;
        std::string out;
        bool success = true;

        err = gpgme_engine_check_version(GPGME_PROTOCOL_OpenPGP);
        if (err) {
            success = false;
        }

        err = gpgme_get_engine_info(&info);
        if (!err) {

            out = "GPGME Version " + Tools::from_c_str(info->version) + " installed at " + Tools::from_c_str(info->file_name) + " using protocol " + Tools::from_c_str(gpgme_get_protocol_name(info->protocol));

        } else {
            out = "ERROR at get_engine_info: " + Tools::from_c_str(gpgme_strsource(err)) + Tools::from_c_str(gpgme_strerror(err));
        }

        return out;
    }

}

