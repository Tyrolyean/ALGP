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
 * File:   Connection.cpp
 * Author: tyrolyean
 * 
 * Created on July 27, 2017, 9:22 PM
 */

#include "Connection.h"
namespace ALGP {

    Connection::Connection(ALGP* a) {

        this->algp = a;
        this->connection_state = 0;
        this->sockfd = 0;

        return;

    }

    Connection::Connection(const Connection& orig) {

        this->algp = orig.algp;
        this->connection_state = 0;
        // Nope, still not gonna do that.
        this->sockfd = 0;
        // Neither that one

        return;

    }

    Connection::~Connection() {
    }
    
    bool Connection::println(std::string line){
        if(this->connection_state != 0 && this->connection_state < 5 ){
            int n = send(this->sockfd, line.data(), line.size(), 0);
            if(n < 0){
                return false;
            }else{
                return true;
            }
            
        }else{
            return false;
        }
        
        return false;
        
    }

}

