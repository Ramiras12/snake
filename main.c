#include <ncurses.h>
#include <stdlib.h>
#define startlenght 3
typedef enum {
  R,
  D,
  L,
  U
} dir1;
typedef struct body {
  int x;
  int y;
  struct body *next;
} body1;
typedef struct {
  dir1 dir;
  int length;
  body1 *head;
} players;


int main(int argc, char **argv)
{
  int y;
  int x;
  int xd;
  int yd;
  players player;
  struct body *bod;
  initscr();
  clear();
  noecho();
  curs_set(FALSE);
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);
  getmaxyx(stdscr, y, x);
  srand(time(NULL));
  for (xd = 0; xd < x; xd++) {
    mvaddstr(1, xd, "#");
    mvaddstr(y - 1, xd, "#");
  }
  for (yd = 1; yd < y - 1; yd++) {
    mvaddstr(yd, 0, "#");
    mvaddstr(yd, x - 1, "#");
  }
mvaddstr(0, 0, "Score: 0");
player.length = startlenght;
player.dir = RIGHT;
player.head = (body1*) malloc(sizeof(body1));
bod = player.head;
refresh();
  return 0;
}
