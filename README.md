# APS

## 1. APP MAZE
[!#maze/code/maze.svg](!#maze/code/maze.svg)

### data-structure
```
struct line 
{
    unsigned int x1;
    unsigned int y1;
    unsigned int x2;
    unsigned int y2;
};

struct maze 
{
    /* data */
    int width;
    int height;
    maze *left; 
    maze *right;
    line *line1;
    line *line2;
};

maze *maze_random(width, height){
  maze m = new maze()
  1. seaperate the space for the longer dimation (width or height) with a two lines leaving space for one dore.
  2. calcculate the new dimation of the two spaces
  m->left = maze_random(width_left, height_left)
  m->right = maze_random(width_right, height_right)
  return m
}
```
