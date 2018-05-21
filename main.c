#include <ncurses.h>
#include <stdlib.h>
#define startlenght 3
typedef enum {
  R,D, L, U
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

void death(int length, body1 *head)
{
  body1 *tmp_ptr;
   while (head) {
    tmp_ptr = head;
    head = head->next;
    free(tmp_ptr);
  }
  tmp_ptr = NULL;
  clear();
color_set(6,NULL);
  mvaddstr(0, 0, "YOU DIED");
  mvprintw(1, 0, "Score: %d\n", length - startlenght);
  refresh();
  sleep(10);
  endwin();
  curs_set(TRUE);
}
void addmark(int *xy, body1 *head, int x, int y)
{
  int fx,fy;

  body1 *bod;

  fx = rand() % (x - 2) + 1;
  fy = rand() % (y - 3) + 2;
  bod = head;
  while (bod) {
    if (fx == bod->x && fy == bod->y) {
      fx = rand() % (x - 2) + 1;
      fy = rand() % (y - 3) + 2;
      bod = head;
    } else {
      bod = bod->next;
    }
  }
 init_pair(13, COLOR_BLACK,   COLOR_YELLOW);
color_set(13,NULL);
  mvaddstr(fy, fx, " ");
color_set(1,NULL);
  xy[0] = fx;
  xy[1] = fy;
  bod = NULL;
}

int main(int argc, char **argv)
{
  char score[5] = { '0', '\0', '\0', '\0', '\0' };
  int y;
  int x;
  int xd;
  int yd;
  int i;
  char add_one = 0;
  int xy[2];
  int x1,y1;
  int x2,y2;
  int ch = ERR;
  players player;
  body1 *bod;
  initscr();
erase();
  start_color();
  init_pair(12, COLOR_WHITE,   COLOR_MAGENTA);
 curs_set(FALSE);

   noecho();
if (has_colors == false) 
{
 printf("error");
 return 0;
}
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);
 getmaxyx(stdscr, y, x);
  srand(time(NULL));
int ns; 
int sn;
for (ns = 1; ns<x;ns++){
	for (sn = 1; sn<y;sn++)
		{
			color_set(1,NULL);
			mvaddstr(sn, ns, " ");
		}
}
  init_pair(9,  COLOR_BLACK,   COLOR_GREEN);
  for (xd = 0; xd < x; xd++) {
   color_set(9, NULL);
    mvaddstr(1, xd, " ");
    color_set(9, NULL);
   mvaddstr(y - 1, xd, " ");
  }
  for (yd = 1; yd < y - 1; yd++) {
     color_set(9, NULL);
    mvaddstr(yd, 0, " ");
	color_set(9, NULL);
    mvaddstr(yd, x - 1, " ");
  }
 init_pair(6,  COLOR_CYAN,    COLOR_BLACK);
color_set(6, NULL);

  mvaddstr(0, 0, "Score: 0");
color_set(1, NULL);

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
addmark(xy, player.head, x, y);
while (1) {
  x1 = player.head->x;
  y1 = player.head->y;

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
    ++x1;
    break;
  }
  if (y1 <= 1 || x1 == 0 || y1 == y - 1 || x1 == x - 1) {
    death(player.length, player.head); 
    player.head = NULL;
    bod = NULL;
    exit(EXIT_SUCCESS);
  } else if ( y1 == xy[1] && x1 == xy[0]) {
    add_one = 1;
  }
  bod = player.head;
  while (bod) {
    x2 = bod->x;
    y2 = bod->y;

    bod->x = x1;
    bod->y = y1;
    if (bod != player.head && bod->x == player.head->x && bod->y == player.head->y) {
    death(player.length, player.head);
    player.head = NULL;
    bod = NULL;
    exit(EXIT_SUCCESS);
    }
    x1 = x2;
    y1 = y2;
	init_pair(7,  COLOR_BLUE,    COLOR_WHITE);
	color_set(7,NULL);
    mvaddstr(bod->y, bod->x, " ");
	color_set(6,NULL);
   // mvaddstr(player.head->y, player.	head->x, "*");
    if (!bod->next && add_one) {
      bod->next = (body1 *) malloc(sizeof(body1));
      bod->next->x = x1;
      bod->next->y = y1;
      bod->next->next = 0;
      ++player.length;
      snprintf(score, 5, "%d", player.length - startlenght);
      mvaddstr(0, 7, score);
      addmark(xy, player.head, x, y);
      add_one = 0;
    }
    bod= bod->next;
  }
    if ((player.head->x != x1 || player.head->y != y1) &&
    (y1 != xy[1] || x1 != xy[0])) {
	color_set(1,NULL);
    mvaddstr(y1, x1, " ");
 color_set(1,NULL);

  }
  refresh();
    if (player.dir == U || player.dir == D) {
    usleep(160000);
  } else {
    usleep(100000);
  }
}

  return 0;
}
