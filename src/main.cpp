#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <cctype>

// Commando Exec: g++ -std=c++17 -Wall -Wextra -O2 main.cpp -o kvstore

// ### WARNING
// printf/scanf no usable 
// std::cin.tie = false

static std::string trim(std::string s){
    auto notSpace = [](unsigned char c){ return !std::isspace(c);}; 

    s.erase(s.begin(), std::find_if(s.begin(),s.end(),notSpace));
    s.erase(std::find_if(s.rbegin(),s.rend(),notSpace).base(), s.end());
    return s;
}


static std::string toLower(std::string s){
    std::transform(s.begin(),s.end(),s.begin(),
                    [](unsigned char c){return (char)std::tolower(c);});
    return s;
}

// get the commands
static std::vector<std::string> splitSpaces(const std::string& line){
    std::istringstream iss(line); // split it
    std::vector<std::string> parts;
    std::string tok;
    while(iss >> tok) parts.push_back(tok);
    return parts;
}

static void printHelp(){
    std::cout << 
    R"(Commands:
  put <key> <value>     - store value (value can contain spaces)
  get <key>             - get value
  del <key>             - delete key
  help                  - show this help
  exit                  - quit

Examples:
  put name Wesley Santos
  get name
  del name
)" << std::endl;
}

static bool parsePutValue(const std::string& line,
                    const std::string& cmdToken,
                    const std::string& keyToken,
                    std::string& outValue){

    auto posCmd = line.find(cmdToken);
    if(posCmd == std::string::npos) return false;

    auto posKey = line.find(keyToken,posCmd + cmdToken.size());
    if(posKey == std::string::npos) return false;

    auto posValueStart = posKey + keyToken.size();
    std::string value = line.substr(posValueStart);
    value = trim(value);
    if(!value.empty() && value[0] == ' ') value.erase(0,1);
    outValue = trim(value); 
    return true;

}

int main (){
    // optimization 
    std::ios::sync_with_stdio(false); 
    std::cin.tie(nullptr);

    std::unordered_map<std::string , std::string> kv;

    std::cout << "KVStore V1 (CLI only) Type 'help' for commands. \n";

    std::string line; // commands line

    while(true){
        std::cout << "> " << std::flush;
        if(!std::getline(std::cin, line)) break;

        line = trim(line);
        if(line.empty()) continue;

        auto parts = splitSpaces(line);
        std::string cmd = toLower(parts[0]);

        if(cmd == "exit" || cmd == "quit"){
            std::cout << "Bye!\n";
            break;
        }

        if(cmd == "help"){
            printHelp();
            continue;
        }

        if(cmd =="status"){
            std::cout << "OK keys=" << kv.size() << "\n";
            continue;
        }


        if(cmd == "put"){
            // put <key> <value>
            if(parts.size() < 3 ){
                std::cout << "ERR usage: put <key> <value>\n";
                continue;
            }
            const std::string key = parts[1];
            std::string value;

            if(!parsePutValue(line,parts[0], parts[1],value)){
                std::cout << "ERR usage: put <key> <value>\n";
                continue;
            }

            kv[key] = value;
            std:: cout << "OK\n";
            continue;
        }

        if(cmd == "get"){
            //get <key>
            if(parts.size() != 2){
                std::cout << "ERR usage: get <key>\n";
                continue;
            }
            const std::string key = parts[1];
            auto it = kv.find(key);
            if(it == kv.end()){
                std::cout << "NOT_FOUND\n";
            }else{
                std::cout << "OK " << it->second << "\n";
            }
            continue;
        }

        if(cmd == "del"){
            if(parts.size() != 2){
                std::cout << "ERR usage: del <key>\n";
                continue;
            }
            const std::string key = parts[1];
            auto removed = kv.erase(key);
            if(removed == 0){
                std::cout << "NOT_FOUND\n";
            } else{
                std::cout << "OK\n";
            }
            continue;
        }

        std::cout << "ERR unknown command: " << cmd << " (type 'help')\n";
    }
    return 0;

}   