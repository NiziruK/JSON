#include <iostream>
#include "json.hpp"
#include <exception>
#include <stdexcept>
#include <string>
#include <filesystem>
#include <fstream>
#include "function.cpp"

namespace fs = std::filesystem;
using json = nlohmann::json;

void CheckArgumentsAmount(int arguments_amount);
void CheckInputPath (const fs::path& path_to_filesystem_object);
bool check_structure(const json& data, const json& template_json);
void ModifyJsonObject(json& json_object);
