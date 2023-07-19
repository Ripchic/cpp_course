#include "minesweeper.h"
#include <algorithm>
#include <random>
#include <queue>

void Minesweeper::MinesSurround() {
    for (auto [x, y] : mines_pos_) {
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                int64_t r = static_cast<int64_t>(y) + i;
                int64_t c = static_cast<int64_t>(x) + j;
                if (r >= 0 && r < height_ && c >= 0 && c < width_ && field_[r][c] != -1) {
                    field_[r][c]++;
                }
            }
        }
    }
}

Minesweeper::Minesweeper(size_t width, size_t height, size_t mines_count) {
    first_move_ = 1;
    width_ = width;
    height_ = height;
    mines_count_ = mines_count;
    game_status_ = GameStatus::NOT_STARTED;
    field_.assign(height_, std::vector<int>(width_, 0));
    rendered_field_.assign(height_, std::string(width_, '-'));
    std::vector<Cell> cells(width_ * height_);
    for (size_t y = 0; y < height_; ++y) {
        for (size_t x = 0; x < width_; ++x) {
            cells[y * width_ + x] = {x, y};
        }
    }
    std::shuffle(cells.begin(), cells.end(), std::mt19937(std::random_device()()));
    for (size_t i = 0; i < mines_count_; ++i) {
        field_[cells[i].y][cells[i].x] = -1;
    }
    mines_pos_ = cells;
    MinesSurround();
}

Minesweeper::Minesweeper(size_t width, size_t height, const std::vector<Cell>& cells_with_mines) {
    first_move_ = 1;
    width_ = width;
    height_ = height;
    cells_with_mines_ = cells_with_mines;
    mines_count_ = cells_with_mines_.size();
    game_status_ = GameStatus::NOT_STARTED;
    field_.assign(height_, std::vector<int>(width_, 0));
    rendered_field_.assign(height_, std::string(width_, '-'));
    for (const auto& cell : cells_with_mines) {
        field_[cell.y][cell.x] = -1;
    }
    mines_pos_ = cells_with_mines;
    MinesSurround();
}

void Minesweeper::NewGame(size_t width, size_t height, size_t mines_count) {
    Minesweeper(width, height, mines_count);
}

void Minesweeper::NewGame(size_t width, size_t height, const std::vector<Cell>& cells_with_mines) {
    Minesweeper(width, height, cells_with_mines);
}
void Minesweeper::OpenCell(const Cell& cell) {
    if (game_status_ == GameStatus::VICTORY || game_status_ == GameStatus::DEFEAT) {
        return;
    }
    if (rendered_field_[cell.y][cell.x] == '?') {
        return;
    }
    if (first_move_) {
        --first_move_;
        game_start_time_ = std::chrono::steady_clock::now();
        game_status_ = GameStatus::IN_PROGRESS;
        unopened_non_mine_count_ =
            static_cast<int64_t>(width_) * static_cast<int64_t>(height_) - static_cast<int64_t>(mines_count_);
    }

    std::queue<Cell> cells_to_open;
    cells_to_open.push(cell);
    while (!cells_to_open.empty()) {
        Cell current_cell = cells_to_open.front();
        cells_to_open.pop();
        if (field_[current_cell.y][current_cell.x] == -1) {
            game_end_time_ = std::chrono::steady_clock::now();
            game_status_ = GameStatus::DEFEAT;
            for (size_t y = 0; y < height_; ++y) {
                for (size_t x = 0; x < width_; ++x) {
                    if (field_[y][x] == -1) {
                        rendered_field_[y][x] = '*';
                    } else {
                        rendered_field_[y][x] = '.';
                    }
                }
            }
            return;
        } else if (field_[current_cell.y][current_cell.x] == 0) {
            for (int dx = -1; dx <= 1; ++dx) {
                for (int dy = -1; dy <= 1; ++dy) {
                    int64_t x = static_cast<int64_t>(current_cell.x) + dx;
                    int64_t y = static_cast<int64_t>(current_cell.y) + dy;
                    if (x >= 0 && x < width_ && y >= 0 && y < height_ && field_[y][x] != -1 &&
                        rendered_field_[y][x] == '-') {
                        cells_to_open.push({static_cast<size_t>(x), static_cast<size_t>(y)});
                        if (rendered_field_[y][x] == '-' && field_[y][x] == 0) {
                            rendered_field_[y][x] = '.';
                            --unopened_non_mine_count_;
                        }
                    }
                }
            }
        } else {
            std::string _ = std::to_string(field_[current_cell.y][current_cell.x]);
            if (rendered_field_[current_cell.y][current_cell.x] == '-') {
                rendered_field_[current_cell.y][current_cell.x] = _[0];
                --unopened_non_mine_count_;
            }
        }
    }

    if (unopened_non_mine_count_ == 0) {
        game_end_time_ = std::chrono::steady_clock::now();
        game_status_ = GameStatus::VICTORY;
    }
}

void Minesweeper::MarkCell(const Cell& cell) {
    if (rendered_field_[cell.y][cell.x] == '-') {
        rendered_field_[cell.y][cell.x] = '?';
    } else if (rendered_field_[cell.y][cell.x] == '?') {
        rendered_field_[cell.y][cell.x] = '-';
    }
}

time_t Minesweeper::GetGameTime() const {
    if (game_status_ == GameStatus::NOT_STARTED) {
        return 0;
    } else if (game_status_ == GameStatus::VICTORY || game_status_ == GameStatus::DEFEAT) {
        return std::chrono::duration_cast<std::chrono::seconds>(game_end_time_ - game_start_time_).count();
    } else {
        return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - game_start_time_)
            .count();
    }
}

Minesweeper::GameStatus Minesweeper::GetGameStatus() const {
    return game_status_;
}

Minesweeper::RenderedField Minesweeper::RenderField() const {
    return rendered_field_;
}