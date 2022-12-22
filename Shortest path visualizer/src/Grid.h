#include "raylib.h"
#include <cstddef>

#define NOT_VISITED_COLOR BLACK
#define VISITED_COLOR BLUE
#define SELECTED_COLOR YELLOW
#define WALL_COLOR GRAY
#define PATH_COLOR GREEN

class Grid {
    public: 
        enum State {
            NOT_VISITED,
            VISITED,
            TO_BE_VISITED,
            WALL,
            SELECTED,
            PATH,
        };

        Rectangle rectangle;

        Grid* prev = NULL;

        State state;
        Color color;

        int index;
        int x_offset;
        int y_offset;

        Grid(int index, int sideLength, int grid_count_horizontal) {
            int x_offset = index % grid_count_horizontal;
            int y_offset = index / grid_count_horizontal;
            int pos_x = x_offset * sideLength;
            int pos_y = y_offset * sideLength;

            this->rectangle = {
                .x = (float)pos_x,
                .y = (float)pos_y,
                .width = (float)sideLength,
                .height = (float)sideLength,
            };

            this->index = index;
            this->state = State::NOT_VISITED;
            this->x_offset = x_offset;
            this->y_offset = y_offset;
        }

        void Draw();
        void Select();
        void Wall();
        void Path();
        void Visit();
        void NotVisited();
        void LongVisited();
        bool IsVisited();
        bool IsWall();
        bool CanBeVisited();
        static Grid* GetGrid(Grid* grid[], int gridSize, int x_offset, int y_offset);
};
