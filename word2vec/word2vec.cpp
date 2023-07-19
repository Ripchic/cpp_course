#include "word2vec.h"
#include <vector>

std::vector<std::string> FindClosestWords(const std::vector<std::string>& words,
                                          const std::vector<std::vector<int>>& vectors) {
    std::vector<int64_t> closetivity;
    std::vector<std::string> answer;
    int64_t temp_result = 0;
    int64_t max_val = INT64_MIN;
    for (size_t i = 1; i < vectors.size(); ++i) {
        temp_result = 0;
        for (size_t j = 0; j < vectors[0].size(); ++j) {
            temp_result += static_cast<int64_t>(vectors[0][j]) * static_cast<int64_t>(vectors[i][j]);
        }
        if (max_val < temp_result) {
            max_val = temp_result;
        }
        closetivity.push_back(temp_result);
    }
    for (size_t i = 0; i < closetivity.size(); ++i) {
        if (closetivity[i] == max_val) {
            answer.push_back(words[i + 1]);
        }
    }
    return answer;
}
