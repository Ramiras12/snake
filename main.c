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

void death(int length, body *head)
{
  body *tmp_ptr;
  while (head) {
    tmp_ptr = head;
    head = head->next;
    free(tmp_ptr);
  }
  tmp_ptr = NULL;
  clear();
  mvaddstr(0, 0, "YOU DIED");
  mvprintw(1, 0, "Score: %d\n", length - startlenght);
  refresh();
  sleep(10);
  endwin();
}

int main(int argc, char **argv)
{
  int y;
  int x;
  int xd;
  int yd;
  int i;
  char add_one = 0;
  int xy[2];
  int x1,y1;
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
player.dir = R;
player.head = (body1*) malloc(sizeof(body1));
bod = player.head;
for (i = 0; i < startlenght; i++) {
  bod->x = x / 2 - i;
  bod->y = y / 2;

  if (i < startlenght - 1) {
    bod->next = (body1 *) malloc(sizeof(body1));
  } else {
    bod->next = 0;
  }

  bod = bod->next;
  }
bod = player.head;
while (1) {
  prev_x = player.head->x;
  prev_y = player.head->y;

  if ((ch = getch()) != ERR) {
    switch (ch) {
    case KEY_UP:
    case 'w':
      player.dir = U;
      break;
    case KEY_DOWN:
    case 's':
      player.dir = D;
      break;
    case KEY_LEFT:
    case 'a':
      player.dir = L;
      break;
    case KEY_RIGHT:
    case 'd':
      player.dir = R;
      break;
    }
  }

  switch (player.dir) {
    case U:
    --y1;
    break;
    case D:
    ++y1;
    break;
    case L:
    --x1;
    break;
    case R:
    ++x2;
    break;
  }
  // проверка на  конец игры
  if (y1 <= 1 || x1 == 0 || y1 == y - 1 || x1 == x - 1) {
    death(player.length, player.head); 
    player.head = NULL;
    bod = NULL;
    exit 0;
  } else 
  if ( y1 == xy[1] && x2 == xy[0]) {
    add_one = 1;
  }
  }
refresh();
  return 0;
}
