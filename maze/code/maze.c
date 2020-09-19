#include <stdio.h>
#include <stdlib.h>
#include "maze.h"
#include "svg.h"

struct _line {
    unsigned int x1;
    unsigned int y1;
    unsigned int x2;
    unsigned int y2;
};
struct _maze
{
    /* data */
    int width;
    int height;
    maze *left; 
    maze *right;
    line *line1;
    line *line2;
};



maze *maze_random (int width, int height){
    if (width == 1 || height == 1){
        return NULL;
    }
    
    int is_x = (width > height);
    int exit = 0;
    int wl = width, wr=width, hl=height, hr=height;
    maze *ptr_maze;
    ptr_maze = malloc(sizeof(maze));
    ptr_maze->line1 = malloc(sizeof(line));
    ptr_maze->line2 = malloc(sizeof(line));
    if (is_x) {
        wr = width/2; 
        wl = width - wr;
        exit = rand() % height;
        ptr_maze->line1->x1 = wr;
        ptr_maze->line1->y1 = 0;
        ptr_maze->line1->x2 = wr;
        ptr_maze->line1->y2 = exit;
        ptr_maze->line2->x1 = wr;
        ptr_maze->line2->y1 = exit+1;
        ptr_maze->line2->x2 = wr;
        ptr_maze->line2->y2 = height;
    } else
    {
        hr = height/2; 
        hl = height - hr;
        exit = rand() % width;
        ptr_maze->line1->y1 = hr;
        ptr_maze->line1->x1 = 0;
        ptr_maze->line1->y2 = hr;
        ptr_maze->line1->x2 = exit;
        ptr_maze->line2->y1 = hr;
        ptr_maze->line2->x1 = exit+1;
        ptr_maze->line2->y2 = hr;
        ptr_maze->line2->x2 = width;
    }
    //printf("w,h: %d, %d. ex: %d %d %d ", width, height, exit, hr, hl);
    ptr_maze->width=width;
    ptr_maze->height=height;
    
    ptr_maze->left = maze_random(wl, hl);
    ptr_maze->right = maze_random(wr, hr);
    
    return ptr_maze;
}

void maze_svg (maze *maze1, char *filename){
    FILE *file = fopen(filename,"w");
    unsigned int width = maze1->width, height=maze1->height;
    //line *l1 = maze1->line1;
    //line *l2 = maze1->line2;
    svg_header(file, width, height);
    svg_line(file,0,0,width,0);
    svg_line(file,0,0,0,height);
    svg_line(file,width,0,width,height);
    svg_line(file,0,height,width,height);
    svg_line(file, maze1->line1->x1, maze1->line1->y1, maze1->line1->x2, maze1->line1->y2);
    svg_line(file, maze1->line2->x1, maze1->line2->y1, maze1->line2->x2, maze1->line2->y2);
    
    svg_maze_recursion(file, maze1, 0, 0);
    unsigned int x, y; 
    x = rand() % width; 
    y = rand() % height;
    printf("%d, %d ", x, y);
    svg_rect(file, x, y, x+1, y+1);
    //free(maze);
    svg_footer(file);
}

void svg_maze_recursion(FILE *f, maze *m, int x, int y){
    if(m){
        svg_line(f, m->line1->x1+x, m->line1->y1+y, m->line1->x2+x, m->line1->y2+y);
        svg_line(f, m->line2->x1+x, m->line2->y1+y, m->line2->x2+x, m->line2->y2+y);
        svg_maze_recursion(f,m->right, x, y);
        svg_maze_recursion(f,m->left, m->line1->x1+x, m->line1->y1+y);
        free(m->line1);
        free(m->line2);
        free(m);
    }
}

void svg_line_unpack(FILE *file, line *l){
    svg_line(file, l->x1, l->y1, l->x2, l->y2);
}