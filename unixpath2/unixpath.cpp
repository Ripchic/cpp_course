#include "unixpath.h"
#include "string"
#include "vector"

UnixPath::UnixPath(std::string_view initial_dir) {
    initial_dir_ = NormalizePath(initial_dir);
    current_dir_ = initial_dir_;
}
std::string UnixPath::NormalizePath(const std::string_view path) {
    std::vector<std::string_view> components;
    for (size_t begin = 0; begin < path.size(); ++begin) {
        size_t end = path.find('/', begin);
        if (end == std::string::npos) {
            end = path.size();
        }
        if (end > begin) {
            components.push_back(path.substr(begin, end - begin));
        }
        begin = end;
    }
    std::string result;
    std::vector<std::string> current_comp;
    for (const auto& component : components) {
        if (component == ".") {
        } else if (component == "..") {
            if (!current_comp.empty()) {
                current_comp.pop_back();
            }
        } else {
            current_comp.push_back(static_cast<std::string>(component));
        }
    }
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

std::string UnixPath::GetAbsolutePath() const {
    return current_dir_;
}

void UnixPath::ChangeDirectory(std::string_view path) {
    if (!path.empty()) {
        if (path.front() == '/') {
            current_dir_ = NormalizePath(path);
        } else {
            std::vector<std::string> current_components;
            for (size_t begin = 0; begin < current_dir_.size(); ++begin) {
                size_t end = current_dir_.find('/', begin);
                if (end == std::string::npos) {
                    end = current_dir_.size();
                }
                if (end > begin) {
                    current_components.push_back(current_dir_.substr(begin, end - begin));
                }
                begin = end;
            }
            std::vector<std::string_view> components;
            for (size_t begin = 0; begin < path.size(); ++begin) {
                size_t end = path.find('/', begin);
                if (end == std::string::npos) {
                    end = path.size();
                }
                if (end > begin) {
                    components.push_back(path.substr(begin, end - begin));
                }
                begin = end;
            }
            for (const auto& component : components) {
                if (component == ".") {
                } else if (component == "..") {
                    if (!current_components.empty()) {
                        current_components.pop_back();
                    }
                } else {
                    current_components.push_back(static_cast<std::string>(component));
                }
            }
            std::string result;
            for (const auto& word : current_components) {
                result += "/";
                result += std::string(word);
            }
            if (result.empty()) {
                current_dir_ = "/";
            } else {
                current_dir_ = result;
            }
        }

    } else {
        current_dir_ = "/";
    }
}
std::string UnixPath::GetRelativePath() const {
    std::string result;
    std::vector<std::string> current_components;
    for (size_t begin = 0; begin < current_dir_.size(); ++begin) {
        size_t end = current_dir_.find('/', begin);
        if (end == std::string::npos) {
            end = current_dir_.size();
        }
        if (end > begin) {
            current_components.push_back(current_dir_.substr(begin, end - begin));
        }
        begin = end;
    }
    std::vector<std::string> initial_components;
    for (size_t begin = 0; begin < initial_dir_.size(); ++begin) {
        size_t end = initial_dir_.find('/', begin);
        if (end == std::string::npos) {
            end = initial_dir_.size();
        }
        if (end > begin) {
            initial_components.push_back(initial_dir_.substr(begin, end - begin));
        }
        begin = end;
    }

    size_t i = 0;
    while (i < initial_components.size() && i < current_components.size() &&
           initial_components[i] == current_components[i]) {
        ++i;
    }
    if (i == initial_components.size() && i == current_components.size()) {
        return ".";
    } else if (i == initial_components.size()) {
        result += "./";
        for (size_t j = i; j < current_components.size(); ++j) {
            result += current_components[j];
            if (j < current_components.size() - 1) {
                result += '/';
            }
        }
        return result;
    } else {
        for (size_t j = i; j < initial_components.size(); ++j) {
            result += "../";
        }
        for (size_t j = i; j < current_components.size(); ++j) {
            result += current_components[j];
            if (j < current_components.size() - 1) {
                result += '/';
            }
        }
        return result;
    }
}