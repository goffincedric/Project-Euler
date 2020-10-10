//
// Created by Cédric Goffin on 2020-10-09.
//

#include <vector>
#include <string>

#ifndef PROJECT_EULER_FILES_H
#define PROJECT_EULER_FILES_H

void readCSVFile(std::vector<std::string> &vector, const std::string &path,
                 const std::string &delimiter = ",", const std::string &valueWrapper = "\"");

#endif //PROJECT_EULER_FILES_H
