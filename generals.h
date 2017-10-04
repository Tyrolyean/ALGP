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
 * File:   generals.h
 * Author: tyrolyean
 *
 * Created on July 20, 2017, 1:19 PM
 */

#ifndef ALGP_GENERALS_H
#define ALGP_GENERALS_H

#if defined _WIN32 || defined __CYGWIN__
    #define ALGP_PATH_SEPARATOR '\\';
#else
    #define ALGP_PATH_SEPARATOR '/';
#endif

#define ALGP_X_ARRAY_POSITION 0
#define ALGP_Y_ARRAY_POSITION 0
#define ALGP_Z_ARRAY_POSITION 0

// If you are asking, yes I am literarily doing a plain HTTP request to a google
// server to test the internet connection.
#define ALGP_CHECK_ONLINE_ADDRESS "www.gstatic.com"
#define ALGP_CHECK_ONLINE_PORT    80
#define ALGP_CHECK_ONLINE_TIMEOUT 5

// This is just a limit at which it doesn't make any sense to go higher up.
#define ALGP_BUFFER_SIZE 4096

#define ALGP_COMMAND_BUFFER_SIZE 1024

#endif /* GENERALS_H */

