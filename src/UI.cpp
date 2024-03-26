#include "../header/UI.h"
#include <iostream>
#include <limits>
#include <iomanip>

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
        if (!path.empty() and path.back() != '/') path += "/";
    }
}

void displayDomain(){
    std::cout << "Choose one of the following options:\n"
              << "\t1. Basic Service Metrics;\n"
              << "\t2. Reliability and Sensitivity Failures;\n"
              << "\t9. Close the app.\n";
    std::cout << "[1..9]: ";
}

uint32_t askNumber(uint32_t upperLimit){
    do{
        std::string value;
        std::cin >> value;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if(value.size() == 1 and value.front() >= '1' and value.front() <= '0' + upperLimit){
            return value[0] - '0';
        }
        else std::cout << "Invalid input. The number must be between 1 and " << upperLimit << ": ";
    } while (true);
}
std::pair<int,std::string> askCityCodeNameId(){
    std::cout << "Choose the city by: \n"
                << "\t 1. Id; \n"
                << "\t 2. Code; \n"
                << "\t 3. Name; \n";
    std::cout << "[1..3]:";
    std::pair<int,std::string> p;
    int option = askNumber(3);
    std::string input;
    switch(option){
        case 1:
            std::cout << "Enter ID: ";
            break;
        case 2:
            std::cout << "Enter CODE: ";
            break;
        case 3:
            std::cout << "Enter NAME: ";
            break;
    }
    std::cin >> input;
    p.first = option;
    p.second = input;
    return p;
}
void displayBasicMetrics(){
    std::cout << "Choose one of the following options:\n"
              << "\t1. Amount of water that can reach a specific city;\n"
              << "\t2. Water deficit by city;\n"
              << "\t3. Balance the load across the network;\n"
              << "\t9. Return to previous menu.\n";
    std::cout << "[1..9]: ";
}
void displayAllOrSpecific (){
    std::cout << "Do you want to know about all cities or about an specific?\n"
              << "\t1. All;\n"
              << "\t2. Specific;\n"
              << "\t9. Return to previous menu;\n";
    std::cout << "[1..9]: ";

}
void printCity(City* city, double water){
    std:: cout << "("  << city->getCode() << ", " << water << ")\n";
}

std::pair<uint32_t , std::string> askReservoirCodeNameID(){
    std::cout << "Choose the reservoir by: \n"
              << "\t 1. Id; \n"
              << "\t 2. Code; \n"
              << "\t 3. Name; \n";
    std::cout << "[1..3]: ";
    std::pair<uint32_t ,std::string> p;
    p.first = askNumber(3);
    switch(p.first){
        case 1:
            std::cout << "Enter ID: ";
            break;
        case 2:
            std::cout << "Enter CODE: ";
            break;
        case 3:
            std::cout << "Enter NAME: ";
            break;
    }
    std::cin >> p.second;
    return p;
}

void displayReliabilitySensitivity(){
    std::cout << "The following options will allow to test the reliability and sensitivity to failures of the network system.\n"
              << "Choose one of the following options:\n"
              << "\t1. Remove a certain reservoir;\n"
              << "\t2. Remove one or more pumping stations;\n"
              << "\t3. Remove the pipelines;\n"
              << "\t9. Return to previous menu;\n";
    std::cout << "[1..3]: ";
}

void displayMetrics(metrics m){
    std::cout << std::left
              << std::setw(9) << "Average:" << std::setw(12) << std::left << m.avg
              << std::setw(16) << "Max difference:" << std::setw(12) << std::left << m.maxDiff
              << std::setw(10) << "Variance:" << std::setw(12) << std::left << m.variance << "\n";
}

void printMap(std::unordered_map<std::string , std::set<std::pair<Edge*,double>>> &map){
    for(auto set : map){
        std::cout << "For city: " << set.first << ".\n";
        for(auto pair : set.second){
            std::cout << "(" << pair.first->getOrig()->getNode()->getCode() << ", " << pair.first->getDest()->getNode()->getCode() << ")" <<
            " --> DEFICIT: " << pair.second << '\n';
        }
        std::cout << "\n\n";
    }

}