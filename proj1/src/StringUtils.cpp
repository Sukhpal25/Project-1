#include "StringUtils.h"
#include <algorithm>
#include <cctype>
#include <sstream>
#include <vector>

namespace StringUtils {

// Give two variable that point ot the start and end of the string, return the substring between them 
std::string Slice(const std::string &str, ssize_t start, ssize_t end) noexcept {
    if (end == 0) end = str.length();
    if (start < 0) start += str.length();
    if (end < 0) end += str.length();
    if (start > end) return ""; // Return empty string if indices are invalid
    return str.substr(start, end - start);
}

// Capitalizes the first character of a string and makes the rest lowercase
std::string Capitalize(const std::string &str) noexcept {
    if (str.empty()) return str;
    std::string result = str;
    if (std::isalpha(result[0]))  // Ensure first character is a letter before modifying
        result[0] = std::toupper(result[0]);
    std::transform(result.begin() + 1, result.end(), result.begin() + 1, ::tolower);
    return result;
}

// Converts a string to uppercase
std::string Upper(const std::string &str) noexcept {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

// Converts a string to lowercase
std::string Lower(const std::string &str) noexcept {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

// Removes leading whitespace characters
std::string LStrip(const std::string &str) noexcept {
    size_t start = str.find_first_not_of(" \t\n\r");
    return (start == std::string::npos) ? "" : str.substr(start);
}

// Removes trailing whitespace characters
std::string RStrip(const std::string &str) noexcept {
    size_t end = str.find_last_not_of(" \t\n\r");
    return (end == std::string::npos) ? "" : str.substr(0, end + 1);
}

// Removes leading and trailing whitespace
std::string Strip(const std::string &str) noexcept {
    return LStrip(RStrip(str));
}

// Centers a string within a given width using a specified fill character
std::string Center(const std::string &str, int width, char fill) noexcept {
    int padding = width - str.length();
    if (padding <= 0) return str;
    int left_pad = padding / 2;
    int right_pad = padding - left_pad;
    return std::string(left_pad, fill) + str + std::string(right_pad, fill);
}

// Left justifies a string by padding it with a given character
std::string LJust(const std::string &str, int width, char fill) noexcept {
    return str + std::string(std::max(0, width - static_cast<int>(str.size())), fill);
}

// Right justifies a string by padding it with a given character
std::string RJust(const std::string &str, int width, char fill) noexcept {
    return std::string(std::max(0, width - static_cast<int>(str.size())), fill) + str;
}

// Replaces all occurrences of old with rep in a string
std::string Replace(const std::string &str, const std::string &old, const std::string &rep) noexcept {
    if (old.empty()) return str; // Prevent infinite loop
    std::string result = str;
    size_t pos = 0;
    while ((pos = result.find(old, pos)) != std::string::npos) {
        result.replace(pos, old.length(), rep);
        pos += rep.length();
    }
    return result;
}

// Splits a string based on a given delimiter. If the delimiter is empty, splits by whitespace
std::vector<std::string> Split(const std::string &str, const std::string &splt) noexcept {
    std::vector<std::string> result;
    if (str.empty()) return result;
    
    if (splt.empty()) { // Default behavior: split by whitespace
        std::istringstream iss(str);
        std::string token;
        while (iss >> token) {
            result.push_back(token);
        }
        return result;
    }

    size_t start = 0;
    size_t end = str.find(splt);
    while (end != std::string::npos) {
        result.push_back(str.substr(start, end - start));
        start = end + splt.length();
        end = str.find(splt, start);
    }
    result.push_back(str.substr(start));
    return result;
}

std::string Join(const std::string &str, const std::vector<std::string> &vect) noexcept {
    if (vect.empty()) return "";
    std::string result = vect[0];
    for (size_t i = 1; i < vect.size(); ++i) {
        result += str + vect[i];
    }
    return result;
}

// Expands tab characters into spaces, assuming a fixed tab size   
std::string ExpandTabs(const std::string &str, int tabsize) noexcept {
    std::string result;
    size_t column = 0;
    
    for (char c : str) {
        if (c == '\t') {
            size_t spaces = tabsize - (column % tabsize);
            result.append(spaces, ' ');
            column += spaces;
        } else {
            result += c;
            column++;
            if (c == '\n') {
                column = 0;
            }
        }
    }
    return result;
}

// Computes the Levenshtein edit distance between two strings
int EditDistance(const std::string &left, const std::string &right, bool ignorecase) noexcept {
    std::string l = ignorecase ? Lower(left) : left;
    std::string r = ignorecase ? Lower(right) : right;
    
    // Use dynamic programming with a 2D table
    std::vector<std::vector<int>> dp(l.length() + 1, std::vector<int>(r.length() + 1));
    
    for (size_t i = 0; i <= l.length(); i++) dp[i][0] = i;
    for (size_t j = 0; j <= r.length(); j++) dp[0][j] = j;
    
    for (size_t i = 1; i <= l.length(); i++) {
        for (size_t j = 1; j <= r.length(); j++) {
            dp[i][j] = std::min({
                dp[i-1][j] + 1,  // Deletion
                dp[i][j-1] + 1,  // Insertion
                dp[i-1][j-1] + (l[i-1] != r[j-1]) // Substitution
            });
        }
    }
    
    return dp[l.length()][r.length()];
}

} // namespace StringUtils 
 