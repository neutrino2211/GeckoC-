// SPDX-FileCopyrightText: 2022 <copyright holder> <email>
// SPDX-License-Identifier: Apache-2.0

#include "./includes/errors.h"
#include "./includes/commander.h"
#include "includes/colors.h"
#include <cstdio>
#include <iostream>



void* getValue(OptionTypes type, std::string value, std::function<void(std::exception*)> onError = nullptr) {
    void* returnValue;

    switch (type)
    {
    case NumberOption:
        try
        {
            int result = std::stoi(value);
            returnValue = (void *) &result;
        }
        catch(std::exception& e)
        {
            std::cerr << "GetValue: " << e.what() << '\n';
            if (onError != nullptr) onError(&e);
            exit(Gecko::Error::CommandLineParseError);
        }
        
        break;

    case FloatOption:
        try
        {
            float result = std::stof(value);
            returnValue = (void *) &result;
        }
        catch(std::exception& e)
        {
            std::cerr << "GetValue: " << e.what() << '\n';
            if (onError != nullptr) onError(&e);
            exit(Gecko::Error::CommandLineParseError);
        }
        break;

    case StringOption:
        returnValue = (void*) &value;
        break;

    default:
        break;
    }

    return returnValue;
}

Commander::Commander(int argc, char** args) {
    arguments = std::vector<std::string>(args, args + argc);
}

void Commander::registerCommand(std::string name, Command* cmd) {
    commands[name] = cmd;
}

void Commander::registerOption(std::string name, OptionListener* listener) {
    listeners[name] = listener;
}

void Commander::parse() {
    std::string cmdName = "";
    Command* cmd = nullptr;

    if (arguments.size() > 1) {
        cmdName = arguments[1];
    }

    if (commands.find(cmdName) == commands.end()) {
        for (auto cmd : commands) {
            printf(
                "%s: no commands given\n%s\n\n%s\n",
                colors::fg::red(colors::style::bold("error:")).c_str(),
                colors::style::bold("Available commands").c_str(),
                cmd.second->buildHelp().c_str()
            );
        }
        return;
    } else {
        cmd = commands[cmdName];
    }

    std::vector<std::string> positionals;

    for (int i = 2; i < arguments.size(); i++) {
        auto arg = arguments[i];
        if (arg[1] != '-') {
            positionals.push_back(arg);
        } else if (arg.substr(0, 2) == "--") {
            auto option = arg.substr(2);

            if (cmd->options.find(option) != cmd->options.end()) {
                auto optional = cmd->options[option];

                if (optional->type == BooleanOption) {
                    if (optional->hasListener) {
                        BooleanCommandable* booleanMethod = (BooleanCommandable*) optional->optionListener;
                        (*booleanMethod)(true);
                    } else {
                        cmd->values[option] = "true";
                    }

                    continue;
                }

                if (optional->hasListener) {
                    if (optional->type == NumberOption) {
                        int* optionValue = (int*) getValue(optional->type, arguments[i + 1]);
                        NumberCommandable* optionalMethod = (NumberCommandable*) optional->optionListener;
                        (*optionalMethod)(*optionValue);
                    } else if (optional->type == StringOption) {
                        StringCommandable* optionalMethod = (StringCommandable*) optional->optionListener;
                        (*optionalMethod)(arguments[i + 1]);
                    } else if (optional->type == FloatOption) {
                        float* optionValue = (float*) getValue(optional->type, arguments[i + 1]);
                        FloatCommandable* optionalMethod = (FloatCommandable*) optional->optionListener;
                        (*optionalMethod)(*optionValue);
                    } 
                } else {
                    cmd->values[option] = arguments[i + 1];
                }

                i++;

                continue;
            }

            if (listeners.find(option) != listeners.end()) {
                auto listener = listeners[option];

                if (listener->type == BooleanOption) {
                    if (listener->hasListener) {
                        BooleanCommandable* booleanMethod = (BooleanCommandable*) listener->optionListener;
                        (*booleanMethod)(true);
                    } else {
                        values[option] = true;
                    }

                    continue;
                }

                if (listener->hasListener) {

                    if (listener->type == NumberOption) {
                        int* optionValue = (int*) getValue(listener->type, arguments[i + 1]);
                        NumberCommandable* listenerMethod = (NumberCommandable*) listener->optionListener;
                        (*listenerMethod)(*optionValue);
                    } else if (listener->type == StringOption) {
                        StringCommandable* listenerMethod = (StringCommandable*) listener->optionListener;
                        (*listenerMethod)(arguments[i + 1]);
                    } else if (listener->type == FloatOption) {
                        float* optionValue = (float*) getValue(listener->type, arguments[i + 1]);
                        FloatCommandable* listenerMethod = (FloatCommandable*) listener->optionListener;
                        (*listenerMethod)(*optionValue);
                    }
                } else {
                    values[option] = arguments[i + 1];
                }

                i++;
            }
        }
    }

    cmd->positionals = positionals;
    cmd->run();

    return;
}

// Command
Command::Command() {};
void Command::run() {};

std::string Command::buildHelp() {
    std::string helpString =  colors::fg::white(colors::style::bold(name)) + ": " + description + "\n\nUsage:\n\t" + usage + "\n";

    for (auto option : options) {
        helpString += "Options:" ;
        helpString += "\n\t--" + option.first + ": " + option.second->help;
    }

    return helpString;
}