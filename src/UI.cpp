#include "../header/UI.h"
#include <iostream>
#include <limits>

std::string getNewPath(){
    std::cout << "Enter the new Path. Keep in mind that either the path is absolute or, if relative, it is in relation to where the executable is.\n";
    std::string newPath;
    std::getline(std::cin, newPath);
    return newPath;
}
std::string getNewFileName(const std::string& name){
    std::cout << "Enter the new file name for the " << name << ".\n";
    std::string newFile;
    std::getline(std::cin, newFile);
    return newFile;
}

char getYesNoAnswer(){
    std::cout << "[y/n]: ";
    do{
        std::string value;
        std::cin >> value;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if(value.size() == 1 and (value[0] == 'y' or value[0] == 'n')) return value[0] == 'y';
        else{
            std::cout << "Invalid input, enter either 'y' or 'n': ";
        }
    } while (true);
}

void displayChooseDataSet(std::string& reservoirs, std::string& stations, std::string& cities, std::string& pipes, std::string& path){
    std::cout << "The default files names are the following?\n"
              << "\t Cities.csv, Reservoir.csv, Pipes.csv, Stations.csv\n";
    std::cout << "Do you pretend to use them?\n";
    bool answer = getYesNoAnswer();
    if (!answer){
        reservoirs = getNewFileName("Reservoirs");
        stations = getNewFileName("Stations");
        cities = getNewFileName("Cities");
        pipes = getNewFileName("Pipes");
    }
    std::cout << "Are the files in a different folder from the one where the executable is?\n";
    answer = getYesNoAnswer();
    if (answer){
        path = getNewPath();
        if (path.back() != '/') path += "/";
    }
}