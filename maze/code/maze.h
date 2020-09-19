typedef struct _tree tree;
typedef struct _maze maze;
typedef struct _line line;

maze *maze_random (int width, int height);
void maze_svg (maze *maze, char *filename);
void svg_maze_recursion(FILE *file, maze *maze, int x, int y);
