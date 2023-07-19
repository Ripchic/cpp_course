#pragma once

#include <string>
#include <vector>
#include <chrono>

class Minesweeper {
public:
    struct Cell {
        size_t x = 0;
        size_t y = 0;
    };

    enum class GameStatus {
        NOT_STARTED,
        IN_PROGRESS,
        VICTORY,
        DEFEAT,
    };

    using RenderedField = std::vector<std::string>;

    Minesweeper(size_t width, size_t height, size_t mines_count);
    Minesweeper(size_t width, size_t height, const std::vector<Cell>& cells_with_mines);

    void NewGame(size_t width, size_t height, size_t mines_count);
    void NewGame(size_t width, size_t height, const std::vector<Cell>& cells_with_mines);

    void OpenCell(const Cell& cell);
    void MarkCell(const Cell& cell);

    GameStatus GetGameStatus() const;
    time_t GetGameTime() const;

    RenderedField RenderField() const;

private:
    size_t width_;
    size_t height_;
    size_t mines_count_;
    int64_t unopened_non_mine_count_;
    std::vector<Cell> mines_pos_;
    int first_move_;
    std::vector<std::vector<int>> field_;
    std::vector<Cell> cells_with_mines_;
    std::vector<std::string> rendered_field_;
    GameStatus game_status_;
    std::chrono::steady_clock::time_point game_start_time_;
    std::chrono::steady_clock::time_point game_end_time_;
    void MinesSurround();
};
