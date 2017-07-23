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
 * File:   Tools.cpp
 * Author: tyrolyean
 * 
 * Created on July 20, 2017, 3:30 PM
 */

#include "Tools.h"
#include <algorithm>

namespace ALGP {

    /* Convert C-style strings into c++ strings.
     * They will be trimmed from the right side as well.
     */
    std::string Tools::from_c_str(const char* input) {

        std::string tmp(input);

        return *rtrim(&tmp);

    }

    /* This trims a string from the right hand side.*/
    inline std::string* Tools::rtrim(std::string *s) {
        s->erase(std::find_if(s->rbegin(), s->rend(),
                std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s->end());
        return s;
    }

    bool Tools::check_for_directory(std::string dir) {

        struct stat info;

        if (stat(dir.c_str(), &info) != 0) {
            return false;
        } else if (info.st_mode & S_IFDIR) { // S_ISDIR() doesn't exist on my windows 
            return true;
        } else {
            return false;
        }

    }

}