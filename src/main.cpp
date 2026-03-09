#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

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

int main (){
    // optimization 
    std::ios::sync_with_stdio(false); 
    std::cin.tie(nullptr);

    std::cout << "KVStore V0 (CLI only) Type 'help' for commands. \n";

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


        // V0: syntax validation and simulate the response
        if(cmd == "put"){
            // put <key> <value>
            if(parts.size() < 3 ){
                std::cout << "ERR usage: put <key> <value>\n";
                continue;
            }
            std::string key = parts[1];

            // get the position of eatch part
            auto posCmd = line.find(parts[0]);
            auto posKey = line.find(parts[1], posCmd + parts[0].size());
            auto posValueStart = posKey + parts[1].size();

            std::string value = trim(line.substr(posValueStart));

            if(!value.empty() && value[0] == ' ') value.erase(0,1);
            value = trim(value);

            std::cout << "OK (V0 simulated) put key= '" << key << "' value='" << value << "'\n";
            continue;
        }

        if(cmd == "get"){
            //get <key>
            if(parts.size() != 2){
                std::cout << "ERR usage: get <key>\n";
                continue;
            }
            std::string key = parts[1];

            // V0 doesn't has data yet - always NOT_FOUND
            std::cout << "NOT_FOUND (V0 simulated) key =='" << key << "'\n";
            continue;
        }

        if(cmd == "del"){
            if(parts.size() != 2){
                std::cout << "ERR usage: del <key>\n";
                continue;
            }
            std::string key = parts[1];

            // V0 no delete yet -- just confirm
            std::cout << "OK (V0 simulated) del key='" << key << "'\n)";
            continue;
        }

        std::cout << "ERR unknown command: " << cmd << " (type 'help')\n";
    }
    return 0;

}