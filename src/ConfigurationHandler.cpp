#include "ConfigurationHandler.hpp"
#include <fstream>
#include <cstdlib>

ConfigurationHandler::ConfigurationHandler()
{
    resetFlags();
}

ConfigurationHandler::~ConfigurationHandler()
{
}

int ConfigurationHandler::loadFromFile(const std::string& filePath) {

    resetFlags();
    std::ifstream file(filePath);
    if (!file.is_open())
        return -1;   // file open error

    std::string line;
    while (std::getline(file, line)) {
        trim(line);
        if (line.empty() || line[0] == '#')
            continue;

        // parse a single key:value line
        auto pos = line.find(':');
        if (pos == std::string::npos)
            continue;   // malformed line, ignore

        std::string key = line.substr(0, pos);
        std::string val = line.substr(pos + 1);
        trim(key);
        trim(val);

        if (key == "host") {
            host = val;
            hasHost = true;
        }
        else if (key == "port") {
            // manual conversion – no exceptions
            char* end = nullptr;
            unsigned long p = std::strtoul(val.c_str(), &end, 10);
            if (end == val.c_str() || *end != '\0')
                return -3;   // not a valid number
            if (p > 65535)
                return -4;   // out of range
            port = static_cast<std::uint16_t>(p);
            hasPort = true;
        }
        else if (key == "comm") {
            comm = val;
            hasComm = true;
        }
        else if (key == "usage") {
            usage = val;
            hasUsage = true;
        }
        // unknown keys ignored
    }

    // After reading whole file, check that all required keys were present
    if (!hasHost)      return -5;
    if (!hasPort)      return -2;   // "missing port" (using distinct code)
    if (!hasComm) return -6;
    if (!hasUsage)     return -7;

    return 0;   // all good
}

const std::string& ConfigurationHandler::getHost() const { return host; }
std::uint16_t      ConfigurationHandler::getPort() const { return port; }
const std::string& ConfigurationHandler::getCommPipeName() const { return comm; }
const std::string& ConfigurationHandler::getMode() const { return usage; }

void ConfigurationHandler::trim(std::string& str){
        // Trim left
    std::size_t start = 0;
    while (start < str.size() && (str[start] == ' ' || str[start] == '\t'))
        ++start;

    // Trim right
    std::size_t end = str.size();
    while (end > start && (str[end - 1] == ' ' || str[end - 1] == '\t'))
        --end;

    str = str.substr(start, end - start);
}

void ConfigurationHandler::resetFlags() {
    hasHost      = false;
    hasPort      = false;
    hasComm = false;
    hasUsage     = false;
}

