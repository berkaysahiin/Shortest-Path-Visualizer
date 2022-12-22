#include "Grid.h"
#include "raylib.h"
#include <cstddef>

void Grid::Draw() {
    DrawRectangleRec(this->rectangle, this->color);
}

void Grid::NotVisited() {
    this->state = State::NOT_VISITED;
    this->color = NOT_VISITED_COLOR;
}

void Grid::Select() {
    this->state = State::SELECTED;
    this->color = SELECTED_COLOR;
}

void Grid::Wall() {
    this->state = State::WALL;
    this->color = WALL_COLOR;
}

void Grid::Path() {
    this->state = State::PATH;
    this->color = PATH_COLOR;
}

void Grid::Visit() {
    this->state = State::VISITED;
    this->color = VISITED_COLOR;
}

bool Grid::IsVisited() {
    return this->state == State::VISITED;
}

bool Grid::IsWall() {
    return this->state == State::WALL;
}

bool Grid::CanBeVisited() {
    return this->IsWall() == false && this->IsVisited() == false;
}

Grid* Grid::GetGrid(Grid* grid[], int gridSize,  int x_offset, int y_offset) {
    for(int i = 0; i < gridSize; i++) {
        if(grid[i]->x_offset == x_offset && grid[i]->y_offset == y_offset) {
            return grid[i];
        }
    }
    return NULL;
}
