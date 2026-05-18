#include "ConfigurationHandler.hpp"
#include <fstream>

int ConfigurationHandler::loadFromFile(const std::string& filePath)
{
    configMap.clear();
    
    std::ifstream file(filePath);
    if (!file.is_open())
        return -1;

    std::string line;
    while (std::getline(file, line))
    {
        trim(line);
        
        // Skip empty lines and comments
        if (line.empty() || line[0] == '#')
            continue;

        // Parse key:value pair
        auto pos = line.find(':');
        if (pos == std::string::npos)
            continue;  // Malformed line, ignore

        std::string key = line.substr(0, pos);
        std::string val = line.substr(pos + 1);
        trim(key);
        trim(val);
        
        if (!key.empty())
        {
            configMap[key] = val;
        }
    }

    return 0;
}

bool ConfigurationHandler::keyExists(const std::string& key) const
{
    return configMap.find(key) != configMap.end();
}

std::optional<std::string> ConfigurationHandler::getValue(const std::string& key) const
{
    auto it = configMap.find(key);
    if (it != configMap.end())
    {
        return it->second;
    }
    return std::nullopt;
}

std::string ConfigurationHandler::getValue(const std::string& key, const std::string& defaultValue) const
{
    auto it = configMap.find(key);
    if (it != configMap.end())
    {
        return it->second;
    }
    return defaultValue;
}

const std::unordered_map<std::string, std::string>& ConfigurationHandler::getAll() const
{
    return configMap;
}

std::vector<std::string> ConfigurationHandler::getAllKeys() const
{
    std::vector<std::string> keys;
    keys.reserve(configMap.size());
    for (const auto& pair : configMap)
    {
        keys.push_back(pair.first);
    }
    return keys;
}

size_t ConfigurationHandler::size() const
{
    return configMap.size();
}

void ConfigurationHandler::clear()
{
    configMap.clear();
}

void ConfigurationHandler::setValue(const std::string& key, const std::string& value)
{
    configMap[key] = value;
}

void ConfigurationHandler::trim(std::string& str)
{
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