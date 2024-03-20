#ifndef DA_FIRSTPROJECT_UI_H
#define DA_FIRSTPROJECT_UI_H

#include <string>

std::string getNewPath();
std::string getNewFileName(const std::string& name);
char getYesNoAnswer();
void displayChooseDataSet(std::string& reservoirs, std::string& stations, std::string& cities, std::string& pipes, std::string& path);


#endif
