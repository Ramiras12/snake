#include <stdlib.h>
#include <curses.h>
int main(void)
{
initscr();
refresh();
printw("Hello, World!");
getch();
endwin();
return 0;
}
