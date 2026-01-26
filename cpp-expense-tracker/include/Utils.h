#pragma once
#include <string>
#include <vector>

namespace utils {
    std::string trim(const std::string& s);
    bool is_valid_date(const std::string& date);  // YYYY-MM-DD basic validation
    bool to_double(const std::string& s, double& out);
    std::vector<std::string> split_csv_line(const std::string& line);
    std::string escape_csv(const std::string& s);
}
