#include "sort_students.h"

bool DateSort(const Student &first, const Student &second) {
    if (first.birth_date.year != second.birth_date.year) {
        return first.birth_date.year < second.birth_date.year;
    } else if (first.birth_date.month != second.birth_date.month) {
        return first.birth_date.month < second.birth_date.month;
    } else if (first.birth_date.day != second.birth_date.day) {
        return first.birth_date.day < second.birth_date.day;
    } else if (first.last_name != second.last_name) {
        return first.last_name < second.last_name;
    } else {
        return first.name < second.name;
    }
}

bool NameSort(const Student &first, const Student &second) {
    if (first.last_name != second.last_name) {
        return first.last_name < second.last_name;
    } else if (first.name != second.name) {
        return first.name < second.name;
    } else if (first.birth_date.year != second.birth_date.year) {
        return first.birth_date.year < second.birth_date.year;
    } else if (first.birth_date.month != second.birth_date.month) {
        return first.birth_date.month < second.birth_date.month;
    } else {
        return first.birth_date.day < second.birth_date.day;
    }
}

void SortStudents(std::vector<Student> &students, SortKind sortKind) {
    switch (sortKind) {
        case SortKind::Date:
            return std::sort(students.begin(), students.end(), DateSort);
        case SortKind::Name:
            return std::sort(students.begin(), students.end(), NameSort);
    }
}