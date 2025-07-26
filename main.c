#include "brighttui.h"
#include <stdio.h>
#include <stdbool.h>
#include <ncurses.h>

#define SLIDER_HEIGHT 20
#define SLIDER_WIDTH  5

void init_colors()
{
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_CYAN);
    init_pair(2, COLOR_WHITE, COLOR_BLACK);
    bkgd(COLOR_PAIR(2));
    refresh();
}


void draw_slider(WINDOW *win, int brightness_percent)
{
    werase(win);
    box(win, 0, 0);
    int filled = (brightness_percent * SLIDER_HEIGHT) / 100;

    for (int i = 0; i < SLIDER_HEIGHT; ++i) {
        if (i >= SLIDER_HEIGHT - filled) {
            wattron(win, COLOR_PAIR(1));
            mvwprintw(win, i + 1, 2, "^");
            wattroff(win, COLOR_PAIR(1));
        }
    }
    wrefresh(win);
}

int handle_mouse_event(MEVENT event, int slider_y, int slider_x, int current)
{
    if (event.y >= slider_y + 1 && event.y <= slider_y + SLIDER_HEIGHT &&
        event.x >= slider_x && event.x < slider_x + SLIDER_WIDTH) {
        int click_level = SLIDER_HEIGHT - (event.y - slider_y - 1);
        current = click_level * 100 / SLIDER_HEIGHT;
    } else if (event.bstate & BUTTON4_PRESSED) { // scroll up
        current += 5;
    } else if (event.bstate & BUTTON5_PRESSED) { // scroll down
        current -= 5;
    }
    if (current < 0) current = 0;
    if (current > 100) current = 100;
    return current;
}


int read_sysfs_value(const char *path)
{
    FILE *fp = fopen(path, "r");
    if (!fp) {
        printf("[ERROR]: Failed to open sysfs file");
        return -1;
    }

    int value;
    if (fscanf(fp, "%d", &value) != 1) {
        printf("[ERROR]: Failed to read value");
        fclose(fp);
        return -1;
    }

    fclose(fp);
    return value;
}

int write_sysfs_value(const char *path, int value)
{
    FILE *fp = fopen(path, "w");
    if (!fp) {
        perror("Failed to open sysfs file for writing");
        return -1;
    }
    fprintf(fp, "%d", value);
    fclose(fp);
    return 0;
}

int set_brightness_percentage(int percent)
{
    int max = read_sysfs_value(MAX_BRIGHTNESS_PATH);
    if (max <= 0) return -1;

    int new_brightness = max * percent / 100;
    return write_sysfs_value(BRIGHTNESS_PATH, new_brightness);
}

int get_current_brightness_percentage()
{
    int current = read_sysfs_value(BRIGHTNESS_PATH);
    int max = read_sysfs_value(MAX_BRIGHTNESS_PATH);

    if (current < 0 || max <= 0) return -1;

    return (current * 100) / max;
}


void init_tui(TUi *ui)
{
    ui->title = "BRIGHTNESS-TUI";
    ui->options = "Press M for options UI";
    ui->pos_x = 0;
    ui->pos_y = 0;
}


int main(void) {
    TUi ui = {0};
    int c = 0;
    init_tui(&ui);

    initscr();
    noecho();
    cbreak();
    curs_set(0);
    keypad(stdscr, TRUE);
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
    mouseinterval(0);

    init_colors();

    int screen_y, screen_x;
    getmaxyx(stdscr, screen_y, screen_x);
    int slider_y = (screen_y - SLIDER_HEIGHT - 2) / 2;
    int slider_x = (screen_x - SLIDER_WIDTH) / 2;

    WINDOW *slider_win = newwin(SLIDER_HEIGHT + 2, SLIDER_WIDTH, slider_y, slider_x);

    int current = get_current_brightness_percentage();
    draw_slider(slider_win, current);
    mvprintw(1, (screen_x - 24) / 2, "Brightness: %d%%", current);
    mvprintw(3, (screen_x - 40) / 2, "Use Arrow Up of Down, h or l(q to quit)");
    refresh();

    while (1) {
        c = getch();
        if (c == 'q' || c == 27) break;

        if (c == KEY_UP || c == 'l') {
            if (current < 100) current += 5;
        }
        else if (c == KEY_DOWN || c == 'h') {
            if(current > 0) current -= 5;
        }
        else if (c == KEY_MOUSE) {
            MEVENT event;
            if (getmouse(&event) == OK) {
                current = handle_mouse_event(event, slider_y, slider_x, current);
            }
        }

        if (set_brightness_percentage(current) != 0) {
            endwin();
            fprintf(stderr, "Failed to set brightness.\n");
            return 1;
        }

        draw_slider(slider_win, current);
        mvprintw(1, (screen_x - 24) / 2, "Brightness: %3d%%", current);
        refresh();
    }

    delwin(slider_win);
    endwin();
    return 0;
}
