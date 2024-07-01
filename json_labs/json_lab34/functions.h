#include <iostream>
#include "json.hpp"
#include <exception>
#include <stdexcept>
#include <string>
#include <filesystem>
#include <fstream>
#include <vector>
#include <time.h>
#include <ctime>


namespace fs = std::filesystem;
using json = nlohmann::json;

void CheckArgumentsAmount(int arguments_amount);

void CheckInputPath();

tm GetRequiredDateTime(const tm* current_time);
json TmToJson(tm time_struct);

tm JsonToTm(json time_json);
