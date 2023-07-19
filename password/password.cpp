#include "password.h"
#include "string"

bool ValidatePassword(const std::string& password = "") {
    unsigned int len = 0;
    const int min_len = 8;
    const int max_len = 14;
    bool capital = false;
    bool small = false;
    bool number = false;
    bool special_symbols = false;
    for (char current_symbol : password) {
        ++len;
        if (isgraph(current_symbol)) {  // ASCII 33-126 check
            if (not capital && isupper(current_symbol)) {
                capital = true;
            } else if (not small && islower(current_symbol)) {
                small = true;
            } else if (not number && isdigit(current_symbol)) {
                number = true;
            } else if (not special_symbols && ispunct(current_symbol)) {
                special_symbols = true;
            }
        } else {
            return false;
        }
    }
    if (len >= min_len && len <= max_len && (static_cast<int>(capital) + small + number + special_symbols) >= 3) {
        return true;
    } else {
        return false;
    }
}
