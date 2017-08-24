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
 * File:   Tools.h
 * Author: tyrolyean
 *
 * Created on July 20, 2017, 3:30 PM
 */
#include <string.h>
#include <string>

#ifndef ALGP_TOOLS_H
#define ALGP_TOOLS_H

namespace ALGP {

    class Tools {
    public:
        static std::string from_c_str(const char* input);
        static std::string* rtrim(std::string *s);
        static bool check_for_directory(std::string dir);
        static long long int get_unix_time_millis();
        static std::string get_time_printable();
        static void wait_milliseconds(int milliseconds);
    private:

    };
}

#endif /* ALGP_TOOLS_H */

