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
 * File:   Server.h
 * Author: tyrolyean
 *
 * Created on August 10, 2017, 8:03 PM
 */

#ifndef ALGP_SERVER_H
#define ALGP_SERVER_H

#include "ALGP.h"
#include <string>

namespace ALGP {

    class Server : public ALGP {
    public:
        Server(std::string    address, std::string gpg_private_key_id_tmp, std::string gpg_public_key_id_tmp);
        Server(const Server& orig);
        virtual ~Server();
    private:
        std::string server_address;

    };
}

#endif /* ALGP_SERVER_H */

