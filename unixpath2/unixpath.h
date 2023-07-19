#pragma once

#include <string>
#include <string_view>
#include <stack>

class UnixPath {
public:
    explicit UnixPath(std::string_view initial_dir);

    void ChangeDirectory(std::string_view path);

    std::string GetAbsolutePath() const;
    std::string GetRelativePath() const;

private:
    static std::string NormalizePath(const std::string_view path);
    std::stack<std::string> components_;
    std::string initial_dir_;
    std::string current_dir_;
};
