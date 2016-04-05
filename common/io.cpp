// Copyright (c) 2015 Intel Corporation
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <iostream>
#include <fstream>
#include <streambuf>

#include "common/error.h"

const std::string readFile(const std::string& filepath) {
    std::ifstream f(filepath);
    if (!f.is_open()) {
        std::cerr << "Unable to open file " << filepath << std::endl;
        throw Exception("I/O Error");
    }
    std::string str((std::istreambuf_iterator<char>(f)),
                     std::istreambuf_iterator<char>());
    return str;
}

