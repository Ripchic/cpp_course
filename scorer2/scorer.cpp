#include "scorer.h"

void Scorer::OnCheckSuccess(const StudentName& student_name, const TaskName& task_name) {
    score_table_[student_name][task_name].push_back(EventType::CheckSuccess);
}
void Scorer::OnCheckFailed(const StudentName& student_name, const TaskName& task_name) {
    score_table_[student_name][task_name].push_back(EventType::CheckFailed);
}
void Scorer::OnMergeRequestOpen(const StudentName& student_name, const TaskName& task_name) {
    score_table_[student_name][task_name].push_back(EventType::MergeRequestOpen);
}
void Scorer::OnMergeRequestClosed(const StudentName& student_name, const TaskName& task_name) {
    score_table_[student_name][task_name].push_back(EventType::MergeRequestClosed);
}
void Scorer::Reset() {
    score_table_.clear();
}

ScoreTable Scorer::GetScoreTable() const {
    ScoreTable result;
    for (const auto& [student, tasks] : score_table_) {
        for (const auto& [task, event_list] : tasks) {
            bool check_status = false;
            bool merge_status = true;
            for (const auto& event : event_list) {
                if (event == EventType::CheckFailed) {
                    check_status = false;
                } else if (event == EventType::CheckSuccess) {
                    check_status = true;
                } else if (event == EventType::MergeRequestOpen) {
                    merge_status = false;
                } else if (event == EventType::MergeRequestClosed) {
                    merge_status = true;
                }
            }
            if (merge_status && check_status) {
                result[student].insert(task);
            }
        }
    }
    return result;
}