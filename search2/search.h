#pragma once

#include <string_view>
#include <vector>

class SearchEngine {
public:
    void BuildIndex(std::string_view text);
    std::vector<std::string_view> Search(std::string_view query, size_t results_count) const;

private:
    std::vector<std::string_view> text_to_lines_;
    std::vector<std::vector<std::string>> text_to_words_;
    bool build_check_ = false;
};
