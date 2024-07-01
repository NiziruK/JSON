#include <iostream>
#include "json.hpp"
#include <exception>
#include <stdexcept>
#include <string>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;
using json = nlohmann::json;

void CheckArgumentsAmount(int arguments_amount){
    if(arguments_amount!= 2){
        throw std::invalid_argument("Invalid command line arguments amount: \ncurrent - " + std::to_string(arguments_amount) + "\nrequired - 2");
    }
}


void CheckInputPath (const fs::path& path_to_filesystem_object){
    if(!fs::exists(path_to_filesystem_object)){
        throw std::invalid_argument("Invalid input path: " + path_to_filesystem_object.string());
    }
    if(!fs::is_regular_file(path_to_filesystem_object)){
        throw std::invalid_argument("Not regular file: " + path_to_filesystem_object.string());
    }
    if(!(path_to_filesystem_object.extension() == fs::path(".json"))){
        throw std::invalid_argument("Not json file: " + path_to_filesystem_object.string());
    }
}

bool check_structure(const json& data, const json& template_json) {
    if (data.type() != template_json.type()) {
        return false;
    }

    if (data.is_object()) {
        for (const auto& item : template_json.items()) {
            auto key = item.key();
            if (!data.contains(key)) {
                return false;
            }
            if (!check_structure(data[key], template_json[key])) {
                return false;
            }
        }
        for (const auto& item : data.items()) {
            auto key = item.key();
            if (!template_json.contains(key)) {
                return false;
            }
        }
    } else if (data.is_array()) {
        if (!template_json.empty() && !data.empty()) {
            if(data.size()!= template_json.size()){
                return false;
            }
            for(int i=0; i<data.size(); i++){
                if(!check_structure(data[i], template_json[i])){
                    return false;
                }
            }
        }
    }

    return true;
}

void ModifyJsonObject(json& json_object){
    std::vector<std::string> keys_to_remove;

    for(const auto& item: json_object.items()){
        if(item.value().is_object()){
            ModifyJsonObject(item.value());
        } else if(!item.value().is_number_integer()){
            throw std::invalid_argument("Found non-integer number, wrong type!");
        } else {
            if(item.value().get<int>() % 2 != 0){
                keys_to_remove.push_back(item.key());
            }
        }
    }

    for(const auto& key : keys_to_remove){
        json_object.erase(key);
    }
}
