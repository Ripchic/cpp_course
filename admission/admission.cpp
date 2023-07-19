#include "admission.h"
#include "algorithm"

std::vector<const Applicant*> SortApplicants(const std::vector<Applicant>& student) {
    std::vector<const Applicant*> result(student.size());
    for (size_t i = 0; i < student.size(); ++i) {
        result[i] = &student[i];
    }
    std::sort(result.begin(), result.end(), [](const Applicant* left, const Applicant* right) {
        return std::tie(left->points, left->student.birth_date.year, left->student.birth_date.month,
                        left->student.birth_date.day, left->student.name) >
               std::tie(right->points, right->student.birth_date.year, right->student.birth_date.month,
                        right->student.birth_date.day, right->student.name);
    });
    return result;
}
AdmissionTable FillUniversities(const std::vector<University>& universities, const std::vector<Applicant>& applicants) {
    std::unordered_map<std::string, std::vector<const Student*>> answer;
    std::unordered_map<std::string, size_t> universities_capacity;
    auto sorted_applicants = SortApplicants(applicants);
    for (const auto& university : universities) {
        universities_capacity[university.name] = university.max_students;
    }
    for (const auto& applicant : sorted_applicants) {
        for (const auto& wish : applicant->wish_list) {
            if (universities_capacity[wish] > 0) {
                answer[wish].push_back(&applicant->student);
                --universities_capacity[wish];
                break;
            }
        }
    }
    return answer;
}