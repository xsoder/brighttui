#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <ncurses.h>
#include <X11/Xlib.h>
#include <X11/extensions/Xrandr.h>

#include "log.h"

typedef struct {
    char* title;
    char* options;
    int pos_x;
    int pos_y;
} TUi;

typedef struct {
    Display *dis;
    Window root;
    int scr;
    XRRCrtcGamma *gamma;
    RRCrtc crtc;
} Roots;

void init_tui(TUi *ui)
{
    ui->title = "BRIGHTNESS-TUI";
    ui->options = "Press M for options UI";
    ui->pos_x = 0;
    ui->pos_y = 0;
}

void init_x11(Roots *win)
{
    win->dis = XOpenDisplay(NULL);
    if (win->dis == NULL)
    {
        fprintf(stderr, "[ERROR] Root display is NULL\n");
        return;
    }
    win->scr = DefaultScreen(win->dis);
    win->root = RootWindow(win->dis, win->scr);
    //win->gamma = XRRGetCrtcGamma (win->dis, win->crtc);
}

// TODO: Implementation of the Xlib xrandr
void set_brightness(Roots *win)
{
    TODO("Implement the logic here");
    XRRSetCrtcGamma(win->dis, win->crtc, win->gamma);
}

int main(void)
{
    TUi ui = {0};
    Roots win = {0};

    int c = 0;

    init_x11(&win);
    init_tui(&ui);

    initscr();
    noecho();

    getmaxyx(stdscr, ui.pos_x, ui.pos_y);
    mvprintw(0, 40,"[INFO] %s\n", ui.title);
    printw("[INFO] %s\n", ui.options);

    while (true)
    {
        if (c == 'q' || c == 27) break; // 27: is Escapce

        if(ui.pos_x == -1 || ui.pos_y == -1)
        {
            fprintf(stdout, "[ERROR]: X coordinate is invalid\n");
            fprintf(stdout, "[ERROR]: Y coordinate is invalid\n");
            endwin();
            return 1;
        }

        refresh();

        c = getch();

        if (c == 'h')
        {
            printf("[INFO] The Key Pressed is  %d\n", c);
            printf("[INFO] X coordinate        %d\n", ui.pos_x);
            printf("[INFO] Y coordinate        %d\n", ui.pos_y);
            //set_brightness(&win);
        }

        else if (c == 'l')
        {
            printw("[INFO] The Key Pressed is  %d\n", c);
            printw("[INFO] X coordinate        %d\n", ui.pos_x);
            printw("[INFO] Y coordinate        %d\n", ui.pos_y);
        }

        else
        {
            continue;
        }

    }

    endwin();
    return 0;
}
