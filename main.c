#include <ncurses.h>
#include <stdlib.h>
#define startlenght 3
int main(int argc, char **argv)
{
  int y;
  int x;
  int xd;
  int yd;
  initscr();
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
refresh();
  return 0;
}
