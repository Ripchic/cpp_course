#include "unixpath.h"
#include <string>
#include <vector>

std::string NormalizePath(std::string_view current_working_dir, std::string_view path) {
    if (path.empty()) {
        return static_cast<std::string>(current_working_dir);
    }
    if (path[0] == '/') {
        current_working_dir = path;

        std::vector<std::string_view> current_comp;
        for (size_t begin = 0; begin < current_working_dir.size(); ++begin) {
            size_t end = current_working_dir.find('/', begin);
            if (end == std::string::npos) {
                end = current_working_dir.size();
            }
            if (end > begin) {
                current_comp.push_back(current_working_dir.substr(begin, end - begin));
            }
            begin = end;
        }
        std::string result;
        for (const auto& component : current_comp) {
            if (component == ".") {
            } else if (component == "..") {
                if (!result.empty()) {
                    result.pop_back();
                }
            } else {
                result += "/" + std::string(component);
            }
        }
        if (result.empty()) {
            return "/";
        } else {
            return result;
        }
    }
    std::vector<std::string_view> current_comp;
    for (size_t begin = 0; begin < current_working_dir.size(); ++begin) {
        size_t end = current_working_dir.find('/', begin);
        if (end == std::string::npos) {
            end = current_working_dir.size();
        }
        if (end > begin) {
            current_comp.push_back(current_working_dir.substr(begin, end - begin));
        }
        begin = end;
    }

    std::vector<std::string_view> path_comp;
    for (size_t begin = 0; begin < path.size(); ++begin) {
        size_t end = path.find('/', begin);
        if (end == std::string::npos) {
            end = path.size();
        }
        if (end > begin) {
            path_comp.push_back(path.substr(begin, end - begin));
        }
        begin = end;
    }

    for (const auto& component : path_comp) {
        if (component == ".") {
        } else if (component == "..") {
            if (!current_comp.empty()) {
                current_comp.pop_back();
            }
        } else {
            current_comp.push_back(component);
        }
    }
    std::string result;
    for (const auto& word : current_comp) {
        result += "/";
        result += std::string(word);
    }
    if (result.empty()) {
        return "/";
    } else {
        return result;
    }
}