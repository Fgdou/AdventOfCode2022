//
// Created by fgdou on 12/1/22.
//
#include "abstract.h"
#include <iostream>
#include <filesystem>
#include <vector>
#include <fstream>
#include "1.h"

int main(int argc, char** argv){
    std::vector<std::unique_ptr<Abstract>> classes;
    classes.emplace_back(std::make_unique<Day1>());

    if(argc > 2){
        throw std::runtime_error("Usage : ./progam <#day>");
    }

    std::time_t t = std::time(0);   // get time now
    std::tm* now = std::localtime(&t);
    int nday = now->tm_mday;
    if(argc == 2)
        nday = std::stoi(argv[1]);

    std::string pathInput = "../input/" + std::to_string(nday) + "/";
    std::vector<std::string> pathInputs;

    if(!std::filesystem::exists(pathInput)){
        throw runtime_error("Path " + pathInput + " does no exist");
    }

    for(const auto& entry : std::filesystem::directory_iterator(pathInput)){
        pathInputs.emplace_back(entry.path());
    }

    if(pathInputs.empty())
        throw std::runtime_error("Input day " + std::to_string(nday) + " not found");
    if(nday > classes.size())
        throw std::runtime_error("Class Day" + std::to_string(nday) + " not found");

    auto& c = *classes[nday-1];

    for(const auto& path : pathInputs){
        std::cout << "\n---------------------- " + path + " ----------------------------------\n";

        std::ifstream file;
        file.open(path);

        c.parse(file);
        c.solve();
    }
}