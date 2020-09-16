#ifndef CONFIG_H_
#define CONFIG_H_
#include <iostream>
#include <vector>
class Config
{
    public:
    Config();
    std::string model;
    std::vector<std::string> classes;
    float confidenceThreshold;
};

#endif
