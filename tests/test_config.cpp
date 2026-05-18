#include "ConfigurationHandler.hpp"
#include <iostream>
#include <cstdlib>

int main() {
    ConfigurationHandler cfg;

    int err = cfg.loadFromFile("config.cfg");
    if (err != 0) {
        std::cerr << "FAIL: loadFromFile returned error " << err << std::endl;
        system("pause");
        return 1;
    }

    bool ok = true;

    if (cfg.getHost() != "127.0.0.1") {
        std::cerr << "FAIL: host mismatch. Expected 127.0.0.1, got: " << cfg.getHost() << std::endl;
        ok = false;
    }
    if (cfg.getPort() != 5555) {
        std::cerr << "FAIL: port mismatch. Expected 5555, got: " << cfg.getPort() << std::endl;
        ok = false;
    }
    if (cfg.getCommPipeName() != "intercomm") {
        std::cerr << "FAIL: pipe name mismatch. Expected interComm, got: " << cfg.getCommPipeName() << std::endl;
        ok = false;
    }
    if (cfg.getMode() != "aggresive") {
        std::cerr << "FAIL: mode mismatch. Expected aggresive, got: " << cfg.getMode() << std::endl;
        ok = false;
    }

    if (ok)
        std::cout << "All tests passed!" << std::endl;

    system("pause");
    return ok ? 0 : 1;
}