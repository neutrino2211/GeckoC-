// SPDX-FileCopyrightText: 2022 <copyright holder> <email>
// SPDX-License-Identifier: Apache-2.0

#ifndef COMMANDER_H
#define COMMANDER_H

#include <functional>
#include <vector>
#include <string>
#include <map>
#include "keyword.h"

typedef std::function<bool(bool)> BooleanCommandable;
typedef std::function<bool(int)> NumberCommandable;
typedef std::function<bool(float)> FloatCommandable;
typedef std::function<bool(std::string)> StringCommandable;

enum OptionTypes {
    NumberOption,
    FloatOption,
    StringOption,
    BooleanOption,
};

struct OptionListener
{
    OptionTypes type;
    std::string help;
    void* optionListener;
    bool hasListener;
};

class Command {

    protected:
    
    std::string name = "";
    std::string usage = "";
    std::string description = "";

    public:
    std::map<std::string, OptionListener*> options;
    std::vector<std::string> positionals;
    std::map<std::string, std::string> values;

    std::string buildHelp();

    Command();
    void registerOption(std::string name, OptionListener* option);
    void registerPositionals(std::vector<std::string> positionals);
    virtual void run();
};

/**
 * @todo write docs
 */
class Commander
{

    std::vector<std::string> arguments;
    std::map<std::string, Command*> commands;
    std::map<std::string, OptionListener*> listeners;

    std::map<std::string, std::string> values;
public:
    Commander(int argc, char** args);
    void registerCommand(std::string name, Command* cmd);
    void registerOption(std::string name, OptionListener* listener);
    void parse();
};

#endif // COMMANDER_H
