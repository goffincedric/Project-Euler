//
// Created by Cédric Goffin on 2020-10-09.
//

#include "files.h"

#include <vector>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

void readCSVFile(std::vector<std::string> &vector, const std::string &path, const std::string &delimiter,
                 const std::string &valueWrapper) {
    // Read from the text file
    std::ifstream MyReadFile(std::__fs::filesystem::relative(path));

    // Use getLine() to read file line by line
    std::string line, token;
    while (getline(MyReadFile, line)) {
        // Loop over tokens in line
        size_t pos = 0;
        while (!line.empty()) {
            // Get first token from line
            pos = line.find(delimiter);
            if (pos != std::string::npos)
                token = line.substr(0, pos);
            else
                token = line;

            // Check if token is wrapped with valueWrapper
            if (!valueWrapper.empty() && token[0] == valueWrapper[0] && token[token.length() - 1] == valueWrapper[0]) {
                token = token.substr(valueWrapper.length(), token.length() - valueWrapper.length() - 1);
            }

            // Add token to vector
            vector.push_back(token);

            // Delete token from string
            if (pos != std::string::npos)
                line.erase(0, pos + delimiter.length());
            else
                line = "";
        }
    }

    // Close the file
    MyReadFile.close();
}