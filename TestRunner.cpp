#include "TestRunner.h"


int TestRunner::Test() {
    std::ifstream file("test_cases.txt");
    if (!file.is_open()) {
        std::cerr << "Test dosyası açılamadı!\n";
        return 1;
    }

    std::string line;
    int total = 0, passed = 0;
    while (std::getline(file, line)) {
        // Yorum veya boş satır atla
        if (line.empty() || line[0] == '#') continue;

        std::istringstream ss(line);
        std::string pattern, text, expected_str;

        if (!std::getline(ss, pattern, '|')) continue;
        if (!std::getline(ss, text, '|')) continue;
        if (!std::getline(ss, expected_str)) continue;

        // Trim baştaki/sondaki boşluklar
        auto trim = [](std::string& s) {
            size_t start = s.find_first_not_of(" \t");
            size_t end = s.find_last_not_of(" \t");
            s = (start == std::string::npos) ? "" : s.substr(start, end - start + 1);
        };
        trim(pattern);
        trim(text);
        trim(expected_str);

        bool expected = expected_str == "1";
        bool result = m.match(pattern, text);
        total++;

        if (result == expected) {
            std::cout << "[+] " << pattern << " | " << text << "\n";
            passed++;
        }
        else {
            std::cout << "[-] " << pattern << " | " << text
                << "  (Beklenen: " << expected << ", Gercek: " << result << ")\n";
        }
    }

    std::cout << "\n" << passed << "/" << total << " test gecti.\n";
    return 0;
}