#ifndef BRIGHT_TUI
#define BRIGHT_TUI

#define BRIGHTNESS_PATH "/sys/class/backlight/intel_backlight/brightness"
#define MAX_BRIGHTNESS_PATH "/sys/class/backlight/intel_backlight/max_brightness"

#define MIN 0
#define MAX 100

enum Theme {
    THEME_DEFAULT = -1,
    THEME_HIGH_CONTRAST,
    THEME_DARK,
    THEME_COUNT = 2,
};

typedef struct {
    char* title;
    char* options;
    int pos_x;
    int pos_y;
} TUi;

void init_tui(TUi *);
int write_sys_value(const char*, int);
int set_brightness(int);

#endif //BRIGHT_TUI
