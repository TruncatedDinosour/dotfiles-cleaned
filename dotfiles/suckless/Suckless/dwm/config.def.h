/* See LICENSE file for copyright and license details. */

#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int gappx = 2;    /* gaps */
static const unsigned int borderpx = 2; /* border pixel of windows */
static const unsigned int snap = 32;    /* snap pixel */
static const int showbar = 1;           /* 0 means no bar */
static const int topbar = 1;            /* 0 means bottom bar */
static const char *fonts[] = {"sans:size=15.5"};

static const char col_gray1[] = "#262220"; /* #222222; background colour */
static const char col_gray2[] =
    "#262220"; /* #444444; inactive window border colour */
static const char col_gray3[] = "#f9f6e8"; /* #BBBBBB; font colour */
static const char col_gray4[] =
    "#383838"; /* #EEEEEE; current tag and current window colour */
static const char col_cyan[] =
    "#f9f0c2"; /* #005577; second bar colour and active window border colour */
static const char *colors[][3] = {
    /*               fg         bg         border   */
    [SchemeNorm] = {col_gray3, col_gray1, col_gray2}, /* innnactive bar */
    [SchemeSel] = {col_gray4, col_cyan, col_cyan},    /* active bar */
};

/* tagging */
static const char *tags[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};

static const Rule rules[] = {
    /* xprop(1):
     *      WM_CLASS(STRING) = instance, class
     *      WM_NAME(STRING) = title
     */
    /* class        instance   title       tags mask   monitor */
    /*                                     (1 << tag - 1) */
    /* all tags */
    {"st", NULL, NULL, 0, -1},
    {"Alacritty", NULL, NULL, 0, -1},

    /* tag 2 */
    {"Firefox", NULL, NULL, 1 << 1, -1},
    {"firefox", NULL, NULL, 1 << 1, -1},

    {"Pale moon", NULL, NULL, 1 << 1, -1},
    {"Tor Browser", NULL, NULL, 1 << 1, -1},
    {"LibreWolf", NULL, NULL, 1 << 1, -1},
    {"chromium", NULL, NULL, 1 << 1, -1},
    {"qBittorrent", NULL, NULL, 1 << 1, -1},
    {"kristall", NULL, NULL, 1 << 1, -1},
    {"Thunderbird", NULL, NULL, 1 << 1, -1},
    {"FreeTube", NULL, NULL, 1 << 1, -1},

    /* tag 3 */
    {"Code", NULL, NULL, 1 << 2, -1},
    {"VSCodium", NULL, NULL, 1 << 2, -1},
    {"jetbrains-pycharm-ce", NULL, NULL, 1 << 2, -1},

    /* tag 4 */
    {"discord", NULL, NULL, 1 << 3, -1},
    {"Bitwarden", NULL, NULL, 1 << 3, -1},
    {"TelegramDesktop", NULL, NULL, 1 << 3, -1},
    {"KotatogramDesktop", NULL, NULL, 1 << 3, -1},

    /* tag 5 */
    {"Microsoft Teams - Preview", NULL, NULL, 1 << 4, -1},
    {"teams-for-linux", NULL, NULL, 1 << 4, -1},
    {"zoom", NULL, NULL, 1 << 4, -1},

    /* tag 6 */
    {"VirtualBox Manager", NULL, NULL, 1 << 5, -1},
    {NULL, "qemu", NULL, 1 << 5, -1},

    /* tag 7 */
    {"libreoffice", NULL, NULL, 1 << 6, -1},
};

/* layout(s) */
static const float mfact = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster = 1;   /* number of clients in master area */
static const int resizehints =
    1; /* 1 means respect size hints in tiled resizals */

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY, TAG)                                                      \
    {MODKEY, KEY, view, {.ui = 1 << TAG}},                                     \
        {MODKEY | ControlMask, KEY, toggleview, {.ui = 1 << TAG}},             \
        {MODKEY | ShiftMask, KEY, tag, {.ui = 1 << TAG}},                      \
        {MODKEY | ControlMask | ShiftMask, KEY, toggletag, {.ui = 1 << TAG}},

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd)                                                             \
    {                                                                          \
        .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL }                   \
    }

/* commands */
static char dmenumon[2] =
    "0"; /* component of dmenucmd, manipulated in spawn() */
// static const char *dmenucmd[] = { "rofi", "-show", "run", NULL };
static const char *dmenucmd[] = {"dmenu_run", NULL};

static const char *mutecmd[] = {"amixer", "-q",     "set",
                                "Master", "toggle", NULL};
static const char *volupcmd[] = {"amixer", "-q",     "set", "Master",
                                 "5%+",    "unmute", NULL};
static const char *voldowncmd[] = {"amixer", "-q",     "set", "Master",
                                   "5%-",    "unmute", NULL};

static const char *brupcmd[] = {"xbacklight", "-inc", "10", NULL};
static const char *brdowncmd[] = {"xbacklight", "-dec", "10", NULL};

static const char *editorcmd[] = {"st", "-e", "vim", NULL};
static const char *calandarcmd[] = {"st", "-e", "calcurse", NULL};

static const char *lockercmd[] = {"xautolock", "-locknow", NULL};
static const char *browser[] = {"firefox", NULL};
static const char *emojicmd[] = {"emoji", NULL};
static const char *redshifttoggle[] = {"redshifttoggle", "eDP1", NULL};

static const char *quitdwmcmd[] = {"quitdwm", NULL};
static const char *dwmmenucmd[] = {"dwmmenu", NULL};

static const char *termcmd[] = {"st", NULL};
static const char *extrakbcmd[] = {"extrakb", NULL};
static const char *weathercmd[] = {"st", "-e", "dweather", NULL};

static Key keys[] = {
    /* modifier                     key        function        argument */
    {MODKEY, XK_d, spawn, {.v = dmenucmd}},
    {MODKEY, XK_Return, spawn, {.v = termcmd}},

    // make a window master
    {MODKEY | ShiftMask, XK_Return, zoom, {0}},

    // toggle bar
    {MODKEY, XK_b, togglebar, {0}},

    // cycle through the stack clockwise
    {MODKEY, XK_j, focusstack, {.i = +1}},

    // cycle thtough the stack anti-clockwise
    {MODKEY, XK_k, focusstack, {.i = -1}},

    // increases number of windows on master
    {MODKEY | ShiftMask, XK_i, incnmaster, {.i = +1}},

    // decreases number of windows on master
    {MODKEY | ShiftMask, XK_d, incnmaster, {.i = -1}},

    // make master smaller
    {MODKEY, XK_h, setmfact, {.f = -0.05}},

    // make master larger
    {MODKEY, XK_l, setmfact, {.f = +0.05}},

    // switch to a used tag
    {MODKEY, XK_Tab, view, {0}},

    // kill a window
    {MODKEY | ShiftMask, XK_q, killclient, {0}},

    // gap control
    {MODKEY, XK_minus, setgaps, {.i = -1}},
    {MODKEY, XK_equal, setgaps, {.i = +1}},
    {MODKEY | ShiftMask, XK_equal, setgaps, {.i = 0}},

    // switch to tags
    TAGKEYS(XK_1, 0) TAGKEYS(XK_2, 1) TAGKEYS(XK_3, 2) TAGKEYS(XK_4, 3)
        TAGKEYS(XK_5, 4) TAGKEYS(XK_6, 5) TAGKEYS(XK_7, 6) TAGKEYS(XK_8, 7)
            TAGKEYS(XK_9, 8)

    // exit dwm
    {MODKEY | ShiftMask, XK_e, spawn, {.v = quitdwmcmd}},

    // dwm menu
    {MODKEY | ShiftMask, XK_m, spawn, {.v = dwmmenucmd}},

    // media keys
    {0, XF86XK_AudioMute, spawn, {.v = mutecmd}},
    {0, XF86XK_AudioLowerVolume, spawn, {.v = voldowncmd}},
    {0, XF86XK_AudioRaiseVolume, spawn, {.v = volupcmd}},
    {0, XF86XK_MonBrightnessUp, spawn, {.v = brupcmd}},
    {0, XF86XK_MonBrightnessDown, spawn, {.v = brdowncmd}},

    // vim
    {MODKEY | ControlMask, XK_e, spawn, {.v = editorcmd}},

    // locker
    {MODKEY, XK_x, spawn, {.v = lockercmd}},

    // actual full screen patch
    {MODKEY | ShiftMask, XK_f, togglefullscr, {0}},

    // browser
    {MODKEY, XK_i, spawn, {.v = browser}},

    // Emoji selector
    {MODKEY, XK_e, spawn, {.v = emojicmd}},

    // Notes/TODOs/etc.
    {MODKEY, XK_n, spawn, {.v = calandarcmd}},

    // Toggle redshift
    {MODKEY | ShiftMask, XK_r, spawn, {.v = redshifttoggle}},

    // Extra keyboard characters
    {MODKEY | ShiftMask, XK_k, spawn, {.v = extrakbcmd}},

    // Weather
    {MODKEY, XK_w, spawn, {.v = weathercmd}},
};
