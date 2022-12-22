#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <queue>
#include <assert.h>
#include <pthread.h>
#include <unistd.h>

#include "raylib.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define GRID_SIDE_LENGTH 20 
#define GRID_COUNT_VERTICAL SCREEN_HEIGHT / GRID_SIDE_LENGTH 
#define GRID_COUNT_HORIZONTAL SCREEN_WIDTH / GRID_SIDE_LENGTH 
#define GRID_COUNT GRID_COUNT_VERTICAL * GRID_COUNT_HORIZONTAL

#include "Grid.h"

pthread_t bfs_thread;
void* BFS(void* args);

Grid* grid[GRID_COUNT] = {};
Grid* target = NULL;
Grid* start = NULL;

int main(void)
{
    for(int i = 0; i < GRID_COUNT; i++) { // Initialize grids;
        grid[i] = new Grid(i, GRID_SIDE_LENGTH, GRID_COUNT_HORIZONTAL);
    }

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Shortest path visualizer");
    SetTargetFPS(60);       

    while (!WindowShouldClose())   
    {
        BeginDrawing();

        for(int i = 0; i < GRID_COUNT; i++) { // Draws all grids
            grid[i]->Draw();
        }

        if(IsMouseButtonPressed(0)) { // Get selected grid
            Vector2 mouse_pos = GetMousePosition();
            for(int i = 0; i < GRID_COUNT; i++) {
                if(CheckCollisionPointRec(mouse_pos, grid[i]->rectangle)) {
                    if(start == NULL) {
                        grid[i]->Select();
                        start = grid[i];
                        break;
                    }
                    else if(target == NULL) {
                        grid[i]->Select();
                        target = grid[i];
                        break;
                    }
                }
            }
        }

        if(IsMouseButtonDown(1)) {
            Vector2 mouse_pos = GetMousePosition();
            for(int i = 0; i < GRID_COUNT; i++) {
                if(CheckCollisionPointRec(mouse_pos, grid[i]->rectangle)) {
                    grid[i]->Wall();
                    break;
                }
            }
        }

        if(IsKeyPressed(KEY_SPACE) && target != NULL && start != NULL) {
            pthread_create(&bfs_thread, NULL, BFS, NULL);
        }

        EndDrawing();
    }

    CloseWindow();       
    return 0;
}


void* BFS(void* args) {
    std::queue<Grid*> que;
    que.push(start);

    while(que.empty() == false) {
        Grid* g = que.front();
        que.pop();
        g->Visit();

        if(g == target) {
            break;
        }

        Grid* next_grid = Grid::GetGrid(grid, GRID_COUNT, g->x_offset - 1, g->y_offset); // left grid
        
        if(next_grid != NULL && next_grid->CanBeVisited()) {
            que.push(next_grid);
            next_grid->Visit();
            next_grid->prev = g;
            if(next_grid == target) {
                break;
            }
        }

        next_grid = Grid::GetGrid(grid, GRID_COUNT, g->x_offset + 1, g->y_offset); // right grid

        if(next_grid != NULL && next_grid->CanBeVisited()) {
            que.push(next_grid);
            next_grid->Visit();
            next_grid->prev = g;
            if(next_grid == target) {
                break;
            }
        }

        next_grid = Grid::GetGrid(grid, GRID_COUNT, g->x_offset, g->y_offset - 1); // top grid

        if(next_grid != NULL && next_grid->CanBeVisited()) {
            que.push(next_grid);
            next_grid->Visit();
            next_grid->prev = g;
            if(next_grid == target) {
                break;
            }
        }

        next_grid = Grid::GetGrid(grid, GRID_COUNT, g->x_offset, g->y_offset + 1); // bot grid

        if(next_grid != NULL && next_grid->CanBeVisited()) {
            que.push(next_grid);
            next_grid->Visit();
            next_grid->prev = g;
            if(next_grid == target) {
                break;
            }
        }
        usleep(600);
    }

    // Mark path
    Grid* curr;
    for(curr = target; curr->prev != NULL; curr = curr->prev) {
        curr->Path();
        usleep(1500);
    }
    curr->Path();
    return NULL;
}
