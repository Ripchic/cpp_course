#include "scorer.h"
#include "map"
#include "algorithm"
std::vector<const Event*> SortEvents(const std::vector<Event>& event) {
    std::vector<const Event*> result(event.size());
    for (size_t i = 0; i < event.size(); ++i) {
        result[i] = &event[i];
    }
    std::sort(result.begin(), result.end(), [](const Event* left, const Event* right) {
        return std::tie(left->student_name, left->task_name, left->time) <
               std::tie(right->student_name, right->task_name, right->time);
    });
    return result;
}
ScoreTable GetScoredStudents(const Events& events, time_t score_time) {
    // maybe I'm a ltl bit crazy about logic operations
    std::vector<const Event*> sorted_in_time;
    std::map<std::string, std::set<std::string>> score_table;
    auto sorted_events = SortEvents(events);
    for (const auto& event : sorted_events) {
        if (event->time <= score_time) {
            sorted_in_time.push_back(event);
        }
    }
    bool test_status = false;
    bool merge_status = false;
    bool merge_not_open = true;
    for (size_t i = 0; i < sorted_in_time.size(); ++i) {
        if ((sorted_in_time[0]->student_name == sorted_in_time[i]->student_name &&
             sorted_in_time[0]->task_name == sorted_in_time[i]->task_name) ||
            (sorted_in_time[i - 1]->student_name == sorted_in_time[i]->student_name &&
             sorted_in_time[i - 1]->task_name == sorted_in_time[i]->task_name)) {
            if (sorted_in_time[i]->event_type == EventType::CheckFailed) {
                test_status = false;
            } else if (sorted_in_time[i]->event_type == EventType::CheckSuccess) {
                test_status = true;
            } else if (sorted_in_time[i]->event_type == EventType::MergeRequestOpen) {
                merge_status = false;
                merge_not_open = false;
            } else if (sorted_in_time[i]->event_type == EventType::MergeRequestClosed) {
                merge_status = true;
            }
        } else if (sorted_in_time[i - 1]->student_name == sorted_in_time[i]->student_name &&
                   sorted_in_time[i - 1]->task_name != sorted_in_time[i]->task_name) {
            if ((test_status && merge_not_open) || (test_status && merge_status)) {
                score_table[sorted_in_time[i]->student_name].insert(sorted_in_time[i - 1]->task_name);
            }
            test_status = false;
            merge_status = false;
            merge_not_open = true;
            if (sorted_in_time[i]->event_type == EventType::CheckFailed) {
                test_status = false;
            } else if (sorted_in_time[i]->event_type == EventType::CheckSuccess) {
                test_status = true;
            } else if (sorted_in_time[i]->event_type == EventType::MergeRequestOpen) {
                merge_status = false;
                merge_not_open = false;
            } else if (sorted_in_time[i]->event_type == EventType::MergeRequestClosed) {
                merge_status = true;
            }
        } else if (sorted_in_time[i - 1]->student_name != sorted_in_time[i]->student_name) {
            if ((test_status && merge_not_open) || (test_status && merge_status)) {
                score_table[sorted_in_time[i - 1]->student_name].insert(sorted_in_time[i - 1]->task_name);
            }
            test_status = false;
            merge_status = false;
            merge_not_open = true;
            if (sorted_in_time[i]->event_type == EventType::CheckFailed) {
                test_status = false;
            } else if (sorted_in_time[i]->event_type == EventType::CheckSuccess) {
                test_status = true;
            } else if (sorted_in_time[i]->event_type == EventType::MergeRequestOpen) {
                merge_status = false;
                merge_not_open = false;
            } else if (sorted_in_time[i]->event_type == EventType::MergeRequestClosed) {
                merge_status = true;
            }
        }
    }
    if ((test_status && merge_not_open) || (test_status && merge_status)) {
        score_table[sorted_in_time.back()->student_name].insert(sorted_in_time.back()->task_name);
    }
    return score_table;
}