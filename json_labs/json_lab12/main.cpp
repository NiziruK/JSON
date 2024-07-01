#include <iostream>
#include "json.hpp"
#include <exception>
#include <stdexcept>
#include <string>
#include <filesystem>
#include <fstream>
#include "functions.h"

int main(int argc, char *argv[]){
    try{
        CheckArgumentsAmount(argc);
        CheckInputPath(fs::path(argv[1]));
        json template_json = R"({
            "string_0" : "some string",
            "number" : 10,
            "object" : {
                "boolean" : true,
                "array" : []
            },
            "string_1" : null,
            "array" : null
            })"_json;
        std::ifstream file(argv[argc - 1]);
        json data =  json::parse(file);

        if(check_structure(data, template_json)){
            std::cout << "Structure is correct" << std::endl;
        }else{
            std::cout << "Structure is not correct" << std::endl;
        }
        
    }catch(const std::exception& e){
        std::cerr<< "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}