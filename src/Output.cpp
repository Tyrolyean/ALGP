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
 * File:   Output.cpp
 * Author: tyrolyean
 * 
 * Created on July 24, 2017, 2:48 PM
 */

#include "Output.h"
#include "Tools.h"

/* Terminal color codes. LINUX only!*/
#define COLOR_RESET   "\033[0m"
#define COLOR_BLACK   "\033[30m"      /* Black */
#define COLOR_RED     "\033[31m"      /* Red */
#define COLOR_GREEN   "\033[32m"      /* Green */
#define COLOR_YELLOW  "\033[33m"      /* Yellow */
#define COLOR_BLUE    "\033[34m"      /* Blue */
#define COLOR_MAGENTA "\033[35m"      /* Magenta */
#define COLOR_CYAN    "\033[36m"      /* Cyan */
#define COLOR_WHITE   "\033[37m"      /* White */
#define COLOR_BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define COLOR_BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define COLOR_BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define COLOR_BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define COLOR_BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define COLOR_BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define COLOR_BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define COLOR_BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

namespace ALGP {

    bool Output::output_lock = false;

    void Output::println(unsigned short int code, std::string line, ALGP* algp) {

        std::vector<std::pair<std::ostream*,std::pair<std::vector<bool>,bool>>> outs = algp->get_outputs();
        
        for(unsigned int i = 0;i < outs.size(); i++){
            
            if(outs[i].second.first[code]){
                insert_line(generate_prefix(code,outs[i].second.second)+line,outs[i].first);
            }
            
        }

        return;
    }

    void Output::insert_line(std::string line, std::ostream* stream) {
        while(output_lock){
            Tools::wait_milliseconds(10);
        }
        
        output_lock = true;
        
        if(stream != NULL){
            
            if(stream->good()){
                *stream << line.c_str() << std::endl;
            }
            
        }

        output_lock = false;
        return;
    }

    std::string Output::generate_prefix(unsigned short int code, bool color) {
        std::string prefix = "[ " + Tools::get_time_printable() + " ";

#ifdef _WIN32
        color = false;
#endif
        if (color) {


            //Color codes are only supported on linux!
            switch (code) {

                case output_type::INTERNAL:
                    prefix = prefix + COLOR_BLUE + "internal\t    " + COLOR_RESET +      "] ";
                    break;

                case output_type::INFO:
                    prefix = prefix + COLOR_GREEN + "information   " + COLOR_RESET +     "] ";
                    break;
                case output_type::WARNING:
                    prefix = prefix + COLOR_YELLOW + "warning\t    " + COLOR_RESET +     "] ";
                    break;
                case output_type::ERROR:
                    prefix = prefix + COLOR_RED + "error\t    " + COLOR_RESET +          "] ";
                    break;
                case output_type::CRITICAL_ERROR:
                    prefix = prefix + COLOR_BOLDRED + "critical error" + COLOR_RESET +   "] ";
                    break;
                case output_type::END_CALL:
                    prefix = prefix + COLOR_BOLDBLUE + "end call\t    " + COLOR_RESET +  "] ";
                    break;
                case output_type::PENETRATION:
                    prefix = prefix + COLOR_BOLDBLACK + "penetration   " + COLOR_RESET + "] ";
                    break;
                default: // I'm probably going to face idiotic programmers.
                    prefix = prefix + COLOR_MAGENTA + "unknown\t    " + COLOR_RESET +    "] ";
                    break;
            }
        } else {
            switch (code) {

                case output_type::INTERNAL:
                    prefix = prefix + "internal\t    " + "] ";
                    break;

                case output_type::INFO:
                    prefix = prefix + "information   " + "] ";
                    break;
                case output_type::WARNING:
                    prefix = prefix + "warning\t    " +  "] ";
                    break;
                case output_type::ERROR:
                    prefix = prefix + "error\t    " +    "] ";
                    break;
                case output_type::CRITICAL_ERROR:
                    prefix = prefix + "critical error" + "] ";
                    break;
                case output_type::END_CALL:
                    prefix = prefix + "end call\t    " + "] ";
                    break;
                case output_type::PENETRATION:
                    prefix = prefix + "penetration   " + "] ";
                    break;
                default: // I'm probably going to face idiotic programmers.
                    prefix = prefix + "unknown\t    " +  "] ";
                    break;
            }
        }

        return prefix;
    }
}
