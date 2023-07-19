#pragma once

#include <vector>
#include <string>

struct Date {
    int day = 0;
    int month = 0;
    int year = 0;
};

struct Student {
    std::string name;
    std::string last_name;
    Date birth_date;
};

enum class SortKind {
    Name,
    Date
};

void SortStudents(std::vector<Student>& students, SortKind sortKind);

