#include <catch.hpp>
#include "sort_students.h"

namespace {

struct TestData {
    std::vector<Student> students;
    SortKind sort_kind = SortKind::Name;
    std::vector<Student> result;
};

const std::vector<TestData> TESTS = {
    {
        .students = {
            { .name = "Petr", .last_name = "Petrov", .birth_date = { .day = 2, .month = 2, .year = 1902 }},
            { .name = "Ivan", .last_name = "Ivanov", .birth_date = { .day = 1, .month = 1, .year = 1901 }},
            { .name = "Alexander", .last_name = "Sidorov", .birth_date = { .day = 3, .month = 3, .year = 1903 }}
        },
        .sort_kind = SortKind::Date,
        .result = {
            { .name = "Ivan", .last_name = "Ivanov", .birth_date = { .day = 1, .month = 1, .year = 1901 }},
            { .name = "Petr", .last_name = "Petrov", .birth_date = { .day = 2, .month = 2, .year = 1902 }},
            { .name = "Alexander", .last_name = "Sidorov", .birth_date = { .day = 3, .month = 3, .year = 1903 }}
        }
    },
    {
        .students = {
            { .name = "Petr", .last_name = "Petrov", .birth_date = { .day = 2, .month = 2, .year = 1902 }},
            { .name = "Alexander", .last_name = "Sidorov", .birth_date = { .day = 3, .month = 3, .year = 1903 }},
            { .name = "Ivan", .last_name = "Ivanov", .birth_date = { .day = 1, .month = 1, .year = 1901 }}
        },
        .sort_kind = SortKind::Name,
        .result = {
            { .name = "Ivan", .last_name = "Ivanov", .birth_date = { .day = 1, .month = 1, .year = 1901 }},
            { .name = "Petr", .last_name = "Petrov", .birth_date = { .day = 2, .month = 2, .year = 1902 }},
            { .name = "Alexander", .last_name = "Sidorov", .birth_date = { .day = 3, .month = 3, .year = 1903 }}
        }
    },
};

bool AreDatesEqual(const Date& date1, const Date& date2) {
    return std::tie(date1.day, date1.month, date1.year) ==
           std::tie(date2.day, date2.month, date2.year);
}

bool AreStudentsEqual(const Student& student1, const Student& student2) {
    return (std::tie(student1.name, student1.last_name) ==
           std::tie(student2.name, student2.last_name)) &&
           AreDatesEqual(student1.birth_date, student2.birth_date);
}

} // anonymous

TEST_CASE("SortStudents") {
    for (TestData test : TESTS) {
        SortStudents(test.students, test.sort_kind);
        REQUIRE(std::equal(test.students.begin(), test.students.end(),
                           test.result.begin(), test.result.end(), AreStudentsEqual));
    }
}
