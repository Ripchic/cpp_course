#include "tests_checking.h"
#include "deque"
std::vector<std::string> StudentsOrder(const std::vector<StudentAction>& student_actions,
                                       const std::vector<size_t>& queries) {
    std::deque<std::string> dq;
    for (auto& actions : student_actions) {
        switch (actions.side) {
            case Side::Top:
                dq.push_front(actions.name);
                break;
            case Side::Bottom:
                dq.push_back(actions.name);
                break;
        }
    }
    std::vector<std::string> answer;
    for (auto& position : queries) {
        answer.push_back(dq[position - 1]);
    }
    return answer;
}