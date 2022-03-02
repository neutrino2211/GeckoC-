// SPDX-FileCopyrightText: 2022 <copyright holder> <email>
// SPDX-License-Identifier: Apache-2.0

#ifndef COMMANDER_H
#define COMMANDER_H

#include <functional>
#include <vector>
#include <string>

typedef std::function<bool(bool)> BooleanCommandable;
typedef std::function<bool(std::string)> NumberCommandable;
typedef std::function<bool(std::string)> StringCommandable;

/**
 * @todo write docs
 */
class Commander
{

    std::vector<std::string> arguments;
public:
    Commander(int argc, char** args);
    void registerBooleanOption(std::string name, BooleanCommandable func);
    void registerNumberOption(std::string name, NumberCommandable func);
    void registerStringOption(std::string name, StringCommandable func);
    std::vector<std::string> parse();
};

#endif // COMMANDER_H
