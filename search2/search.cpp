#include "search.h"
#include "string"
#include <algorithm>
#include <string_view>
#include <unordered_map>
#include <map>
#include <math.h>
#include <cctype>
#include <functional>

void SearchEngine::BuildIndex(std::string_view text) {
    if (!text.empty()) {
        build_check_ = true;
        // text into lines
        size_t start = 0;
        size_t end = 0;
        while ((end = text.find('\n', start)) != std::string_view::npos) {
            text_to_lines_.emplace_back(text.substr(start, end - start));
            start = end + 1;
        }
        text_to_lines_.emplace_back(text.substr(start, text.size()));
        // lines to vector char
        for (size_t i = 0; i < text_to_lines_.size(); ++i) {
            std::string word;
            std::vector<std::string> words_in_line;
            for (char c : text_to_lines_[i]) {
                if (std::isalpha(c)) {
                    c = static_cast<char>(tolower(c));
                    word += c;
                } else if (!word.empty()) {
                    words_in_line.emplace_back(word);
                    word.clear();
                }
            }
            if (!word.empty()) {
                words_in_line.emplace_back(word);
                word.clear();
            }
            text_to_words_.emplace_back(words_in_line);
        }
    }
};

std::vector<std::string_view> SearchEngine::Search(std::string_view query, size_t results_count) const {
    if (build_check_) {
        std::vector<std::string_view> result;
        // query split into words
        std::string char_line;
        std::vector<std::string> search_request;
        for (std::size_t i = 0, j = 0; i < query.size(); i = j + 1) {
            while (i < query.size() && !std::isprint(query[i]) && !std::isspace(query[j])) {
                ++i;
            }
            j = i + 1;
            while (j < query.size() && std::isprint(query[j]) && !std::isspace(query[j])) {
                ++j;
            }
            if (i < query.size()) {
                char_line = query.substr(i, j - i);
                std::transform(char_line.begin(), char_line.end(), char_line.begin(), ::tolower);
                search_request.emplace_back(char_line);
            }
            search_request.erase(unique(search_request.begin(), search_request.end()), search_request.end());
        }
        std::vector<size_t> relevant_lines;
        std::unordered_map<std::string_view, size_t> word_counts;
        for (size_t i = 0; i < text_to_words_.size(); ++i) {
            for (const auto& word : search_request) {
                if (std::find(text_to_words_[i].begin(), text_to_words_[i].end(), word) != text_to_words_[i].end()) {
                    word_counts[word] += 1;
                    relevant_lines.emplace_back(i);
                }
            }
            relevant_lines.erase(unique(relevant_lines.begin(), relevant_lines.end()), relevant_lines.end());
        }
        // find TF-IDF for each relevant line
        std::map<size_t, long double> string_value;
        for (size_t i = 0; i < relevant_lines.size(); ++i) {
            for (const auto& word : search_request) {
                long double in_line = 0;
                in_line = std::count(text_to_words_[relevant_lines[i]].begin(), text_to_words_[relevant_lines[i]].end(),
                                     word);
                if (in_line != 0) {
                    if (log(text_to_lines_.size() / word_counts.count(word)) != 0) {
                        string_value[relevant_lines[i]] += ((in_line / text_to_words_[relevant_lines[i]].size()) *
                                                            (log(text_to_lines_.size() / word_counts.count(word))));
                    }
                }
            }
        }
        std::vector<std::pair<size_t, long double>> sorted_str(string_value.begin(), string_value.end());
        std::sort(sorted_str.begin(), sorted_str.end(),
                  [](const auto& a, const auto& b) { return a.second > b.second; });
        for (size_t i = 0; (i < results_count) && (i < sorted_str.size()); ++i) {
            result.emplace_back(text_to_lines_[sorted_str[i].first]);
        }
        return result;
    } else {
        return {};
    }
};