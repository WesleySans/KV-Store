#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

static std::string trim(std::string s){
    auto notSpace = [](unsigned char c){ return !std::isspace(c);}; 

    s.erase(s.begin(), std::find_if(s.begin(),s.end(),notSpace));
    s.erase(std::find_if(s.rend(),s.rbegin(),notSpace).base(), s.end());
    return s;
}


static std::string toLower(std::string s){
    std::transform(s.begin(),s.end(),s.begin(),
                    [](unsigned char c){return (char)std::tolower(c);});
    return s;
}