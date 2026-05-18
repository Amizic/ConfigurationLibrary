#pragma once

#include <string>
#include <cstdint>

#if defined(CONFIGLIB_DYNAMIC)
    #if defined(CONFIGLIB_BUILD)
        #define CONFIGLIB_API __declspec(dllexport)
    #else
        #define CONFIGLIB_API __declspec(dllimport)
    #endif
#else
    #define CONFIGLIB_API
#endif

class CONFIGLIB_API ConfigurationHandler
{
public:
    ConfigurationHandler();
    ~ConfigurationHandler();

    int loadFromFile(const std::string& filePath);
    const std::string& getHost() const;
    std::uint16_t getPort() const;
    const std::string& getCommPipeName() const;
    const std::string& getMode() const;
    
    private:
    static void trim(std::string& str);
    void parseLine(const std::string& line);
    void resetFlags();

    std::string   host;
    std::uint16_t port;
    std::string   comm;
    std::string   usage;
    
    bool hasHost;
    bool hasPort;
    bool hasComm;
    bool hasUsage;
};

