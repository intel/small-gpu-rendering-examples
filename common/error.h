/* Copyright 2015 Martina Kollarova
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// Convenience functions for printing errors.

#ifndef ERROR_H
#define ERROR_H

#include <stdexcept>
#include <stdio.h>

// Internal, use the macro "printGlErrors" instead.
void printGlErrors_(const char* where="", const int line=0);

// Print the errors reported by glGetError on stderr, in addition to the current
// line number and function name.
#define printGlErrors() printGlErrors_(__func__, __LINE__)

// Can be used the same way as printf. It will additionally print "[ERROR]" and
// the function name and line number where the error occurred, and it will print
// it on stderr instead of stdout. Exits the program with code 1.
// Example:
//   fail("this thing failed with value %d", variable);
#define fail(...) { fprintf(stderr, "[ERROR] (%s:%d) ", __FILE__, __LINE__); \
                    fprintf(stderr, __VA_ARGS__); \
                    exit(1); }

// Base exception.
class Exception : public std::runtime_error
{
public:
    explicit Exception(const std::string& msg="")
        : runtime_error(msg) {}
};

#endif /* end of include guard: ERROR_H */
