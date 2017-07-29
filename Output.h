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
 * File:   Output.h
 * Author: tyrolyean
 *
 * Created on July 24, 2017, 2:48 PM
 */

#ifndef OUTPUT_H
#define OUTPUT_H
#include "ALGP.h"
#include <string>

namespace ALGP {

    class Output {
    public:
        static void println(unsigned short int code, std::string line, ALGP* algp);
        
    private:
        static void insert_line(std::string line, std::ostream* stream);
        static std::string generate_prefix(unsigned short int code, bool color);
        static bool output_lock;
        
    };

    /* This enumeration is used to pass the type of output around*/
    enum output_type : unsigned short int {
        INTERNAL, INFO, WARNING, ERROR, CRITICAL_ERROR, PENETRATION, END_CALL
                // Please notice that END_CALL has to be the last value in the 
                // enum.
    };
}

#endif /* OUTPUT_H */

