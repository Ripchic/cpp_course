#include "associative_operation.h"
bool IsAssociative(const std::vector<std::vector<size_t>>& table) {
    const size_t mat_dimension = table.size();
    for (size_t i = 0; i < mat_dimension; ++i) {
        for (size_t j = 0; j < mat_dimension; ++j) {
            for (size_t k = 0; k < mat_dimension; ++k) {
                if (table[table[i][j]][k] != table[i][table[j][k]]) {
                    return false;
                }
            }
        }
    }
    return true;
}
