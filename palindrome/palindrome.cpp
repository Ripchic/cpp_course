#include "palindrome.h"
#include "string"
bool IsPalindrome(const std::string& str = "") {
    std::string str_no_space;
    std::string str_copy;
    for (char symbol : str) {
        if (symbol != ' ') {
            str_no_space += symbol;
        }
    }
    str_copy = str_no_space.substr(0, -1);
    std::reverse(str_no_space.begin(), str_no_space.end());
    return str_no_space == str_copy;
}
