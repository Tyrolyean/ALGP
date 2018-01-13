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
#include <sys/types.h>
#include <sys/stat.h>
#include <chrono>
#include <cctype>
#include <locale>
#include <thread>
#ifdef _WIN32
#include <windows.h>
#endif

namespace ALGP {

    /* Convert C-style strings into c++ strings.
     * They will be trimmed from the right side as well.
     */
    std::string Tools::from_c_str(const char* input) {

        std::string tmp(input);

        return *rtrim(&tmp);

    }

#ifndef _WIN32

    /* This trims a string from the right hand side. For Unix systems*/
    inline std::string* Tools::rtrim(std::string *s) {
        s->erase(std::find_if(s->rbegin(), s->rend(),
                std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s->end());
        return s;
    }
#else

	inline std::string* Tools::rtrim(std::string* s) {
		
	}


#endif

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

    //
    // Time related functions.
    //

    long long int Tools::get_unix_time_millis() {
        std::chrono::milliseconds ms = std::chrono::duration_cast< std::chrono::milliseconds >(std::chrono::system_clock::now().time_since_epoch());
        return ms.count();
    }

    /* This returns a printable version of the actual time.
     * It is formatted like this: %Y-%m-%d %I:%M:%S
     */
    std::string Tools::get_time_printable() {
        time_t rawtime;
        struct tm * timeinfo;
        char buffer[80];

        time(&rawtime);
        timeinfo = localtime(&rawtime);

        strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", timeinfo);
        return Tools::from_c_str(buffer);
    }
    
    void Tools::wait_milliseconds(int milliseconds) {
#ifdef _WIN32
        Sleep(milliseconds);
#else
        std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
#endif
    return;
}

}
