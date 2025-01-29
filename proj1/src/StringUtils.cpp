#include "StringUtils.h"
#include <algorithm>
#include <cctype>
#include <sstream>
#include <vector>

namespace StringUtils {

std::string Slice(const std::string &str, ssize_t start, ssize_t end) noexcept {
    if (end == 0) end = str.length();
    if (start < 0) start += str.length();
    if (end < 0) end += str.length();
    return str.substr(start, end - start);
}

std::string Capitalize(const std::string &str) noexcept {
    if (str.empty()) return str;
    std::string result = str;
    result[0] = std::toupper(result[0]);
    return result;
}

std::string Upper(const std::string &str) noexcept {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

std::string Lower(const std::string &str) noexcept {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

std::string LStrip(const std::string &str) noexcept {
    size_t start = str.find_first_not_of(" \t\n\r");
    return (start == std::string::npos) ? "" : str.substr(start);
}

std::string RStrip(const std::string &str) noexcept {
    size_t end = str.find_last_not_of(" \t\n\r");
    return (end == std::string::npos) ? "" : str.substr(0, end + 1);
}

std::string Strip(const std::string &str) noexcept {
    return LStrip(RStrip(str));
}

std::string Center(const std::string &str, int width, char fill) noexcept {
    int padding = width - str.length();
    if (padding <= 0) return str;
    int left_pad = padding / 2;
    int right_pad = padding - left_pad;
    return std::string(left_pad, fill) + str + std::string(right_pad, fill);
}

std::string LJust(const std::string &str, int width, char fill) noexcept {
    return str + std::string(std::max(0, width - static_cast<int>(str.size())), fill);
}

std::string RJust(const std::string &str, int width, char fill) noexcept {
    return std::string(std::max(0, width - static_cast<int>(str.size())), fill) + str;
}

std::string Replace(const std::string &str, const std::string &old, const std::string &rep) noexcept {
    std::string result = str;
    size_t pos = 0;
    while ((pos = result.find(old, pos)) != std::string::npos) {
        result.replace(pos, old.length(), rep);
        pos += rep.length();
    }
    return result;
}

std::vector<std::string> Split(const std::string &str, const std::string &splt) noexcept {
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, splt.empty() ? ' ' : splt[0])) {
        if (!token.empty()) result.push_back(token);
    }
    return result;
}

std::string Join(const std::string &str, const std::vector<std::string> &vect) noexcept {
    std::string result;
    for (size_t i = 0; i < vect.size(); ++i) {
        result += vect[i];
        if (i < vect.size() - 1) result += str;
    }
    return result;
}

std::string ExpandTabs(const std::string &str, int tabsize) noexcept {
    std::string result;
    for (char ch : str) {
        if (ch == '\t') {
            result.append(tabsize, ' ');
        } else {
            result += ch;
        }
    }
    return result;
}

int EditDistance(const std::string &left, const std::string &right, bool ignorecase) noexcept {
    int m = left.size(), n = right.size();
    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1));

    for (int i = 0; i <= m; ++i) dp[i][0] = i;
    for (int j = 0; j <= n; ++j) dp[0][j] = j;

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            int cost = (ignorecase ? tolower(left[i - 1]) != tolower(right[j - 1]) : left[i - 1] != right[j - 1]);
            dp[i][j] = std::min({ dp[i - 1][j] + 1, dp[i][j - 1] + 1, dp[i - 1][j - 1] + cost });
        }
    }

    return dp[m][n];
}

}
