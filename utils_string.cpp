#include "utils_string.h"
#include <string>
#include <vector>
#include <sstream>

std::string preprocess_ipv4(const std::string& ip_address) {
    std::string reversed;
    std::istringstream iss(ip_address);
    std::string token;
    std::vector<std::string> parts;
    while (std::getline(iss, token, '.')) {
        parts.push_back(token);
    }
    std::reverse(parts.begin(), parts.end());
    for (const auto& part : parts) {
        if (!reversed.empty()) reversed += ".";
        reversed += part;
    }

    return reversed + ".in-addr.arpa";
}

void dns_format(unsigned char* dns, const char* host) {
    int lock = 0;
    strcat((char*)host, ".");
    for (int i = 0; i < strlen((char*)host); i++) {
        if (host[i] == '.') {
            *dns++ = i - lock;
            for (; lock < i; lock++) {
                *dns++ = host[lock];
            }
            lock++;
        }
    }
    *dns++ = '\0';
}
