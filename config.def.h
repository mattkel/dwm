/* Constants */
#define TERMINAL "alacritty"
#define TERMCLASS "Alacritty"
#define ICONSIZE 16                         /* icon size */
#define ICONSPACING 5                       /* space between icon and title */

/* appearance */
static unsigned int borderpx          = 2;  /* border pixel of windows */
static unsigned int snap              = 32; /* snap pixel */
static unsigned int gappih            = 20; /* 10 horiz inner gap between windows */
static unsigned int gappiv            = 40; /* 10 vert inner gap between windows */
static unsigned int gappoh            = 37; /* 16 horiz outer gap between windows and screen edge */
static unsigned int gappov            = 77; /* 17 vert outer gap between windows and screen edge */
static int swallowfloating            = 0;  /* 1 means swallow floating windows by default */
static int smartgaps                  = 0;  /* 1 means no outer gap when there is only one window */
static unsigned int systraypinning    = 0;  /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static unsigned int systrayonleft     = 0;  /* 0: systray in the right corner, >0: systray on left of status text */
static unsigned int systrayspacing    = 4;  /* systray spacing */
static int systraypinningfailfirst    = 1;  /* 1: systray on the first monitor, 0: display systray on the last monitor*/
static int showsystray                = 1;  /* 0 means no systray */
static int showbar                    = 1;  /* 0 means no bar */
static int topbar                     = 0;  /* 0 means bottom bar */
static int user_bh                    = 22; /* 0 - default     | 20, 22, 25, 27 */
static char *fonts[] = {
  "GoMono Nerd Font:size=10:antialias=true:autohint=true",              // text               | 9,  10, 12
  "JoyPixels:style=Regular:pixelsize=12:antialias=true:autohint=true",  // emoji              | 12, 13, 16
  "Source Han Sans:pixelsize=10"                                        // asian characters   | 9,  10, 12
};

static char border_norm[]    = "#444444";
static char border_sel[]     = "#770000";
static char border_float[]   = "#005577";

static char bg_norm[]        = "#444444";
static char bg_sel[]         = "#444444";
static char bg_tray[]        = "#444444";

static char fg_norm[]        = "#bbbbbb";
static char fg_sel[]         = "#ffffff";
static char fg_tray[]        = "#eeeeee";

static char *colors[][4] = {
  //                    fg             bg             border             float border
  [SchemeTagsNorm]  = { fg_norm,       bg_norm,       border_norm,       border_norm},
  [SchemeTagsSel]   = { fg_sel,        bg_sel,        border_norm,       border_norm},
  [SchemeNorm]      = { fg_norm,       bg_norm,       border_norm,       border_norm},
  [SchemeSel]       = { fg_sel,        bg_sel,        border_sel,        border_float},
  [SchemeStatus]    = { fg_tray,       bg_tray,       border_norm,       border_norm},
};

/* sticky indicator */
static const XPoint stickyicon[]    = { {0,0}, {4,0}, {4,8}, {2,6}, {0,8}, {0,0} }; /* represents the icon as an array of vertices */
static const XPoint stickyiconbb    = {4,8};	/* defines the bottom right corner of the polygon's bounding box (speeds up scaling) */

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
/* xprop(1): WM_CLASS(STRING) = instance, class WM_NAME(STRING) = title */

/*  class           instance        title       	   tags mask    isfloating   isterminal  noswallow  monitor */
	{ TERMCLASS,      NULL,           NULL,       	   0,           0,           1,          0,         -1 },
	{ NULL,           NULL,           "Event Tester",  0,           0,           0,          1,         -1 },
  { NULL,           "scratchterm",  NULL,            0,           1,           1,          0,         -1 },
  { NULL,           "scratchcalc",  NULL,            0,           1,           1,          0,         -1 },
  { "Alacritty",    NULL,           "Neomutt",       0,           1,           1,          0,         -1 },
  { "Nitrogen",     NULL,           NULL,            0,           1,           0,          0,         -1 },
  { "MEGAsync",     NULL,           NULL,            0,           1,           0,          0,         -1 },
  { "qBittorrent",  NULL,           NULL,            0,           1,           0,          0,         -1 },
  { "Tor Browser",  NULL,           NULL,            0,           1,           0,          0,         -1 },
  { "Xarchiver",    NULL,           NULL,            0,           1,           0,          0,         -1 },
};

/* layout(s) */
static float mfact     = 0.55;    /* factor of master area size [0.05..0.95] */
static int nmaster     = 1;       /* number of clients in master area */
static int resizehints = 1;       /* 1 means respect size hints in tiled resizals */
static int decorhints  = 0;       /* 1 means respect decoration hints */
#define FORCE_VSPLIT 1            /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",	tile },                   // 0: Default: Master on left, slaves on right
	{ "TTT",	bstack },                 // 1: Master on top, slaves on bottom
	{ "[M]",	monocle },                // 2: All windows on top of eachother
	{ "><>",	NULL },			              // 3: no layout function means floating behavior
  { "[D]",	deck },                   // 4: Master on left, slaves in monocle-like mode on right
  { "|M|",	centeredmaster },		      // 5: Master in middle, slaves on sides
  { ">M>",	centeredfloatingmaster },	// 6: Same but master floats
  { "[@]",	spiral },                 // 7: Fibonacci spiral
  { "[\\]",	dwindle },                // 8: Decreasing in size right and leftward
	{ NULL,		NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
#define STACKKEYS(MOD,ACTION) \
	{ MOD,	XK_j,	ACTION##stack,	{.i = INC(+1) } }, \
	{ MOD,	XK_k,	ACTION##stack,	{.i = INC(-1) } }, \
	{ MOD,  XK_v, ACTION##stack,  {.i = 0 } }, \

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *termcmd[]  = { TERMINAL, NULL };
static const char *layoutmenu_cmd = "layoutmenu.sh";
static const char *appmenu_cmd = "appmenu.sh"; 

typedef struct {
	const char *name;
	const void *cmd;
} Sp;
// alacritty
const char *spcmd1[] = { TERMINAL, "--class", "scratchterm", "-t", "Alacritty - Scratchpad Terminal", "-o", "window.dimensions.columns=120", "-o", "window.dimensions.lines=32", "-o", "window.opacity=0.86", NULL };
const char *spcmd2[] = { TERMINAL, "--class", "scratchcalc", "-t", "Alacritty - Scratchpad Calculator", "-o", "font.size=24.0", "-o", "window.dimensions.columns=22", "-o", "window.dimensions.lines=10", "-o", "window.opacity=0.86", "-e", "bc", "-lq", NULL };

static Sp scratchpads[] = {
  // name              cmd
  {"scratchterm",      spcmd1},
  {"scratchcalc",      spcmd2},
};

#include <X11/XF86keysym.h>

static Key keys[] = {
//modifier                key             function        argument
  // ------ system ------
  { MODKEY,               XK_Return,      spawn,          {.v = termcmd} },
  { MODKEY|ShiftMask,		  XK_Return,	    togglescratch,	{.ui = 0} },
  { MODKEY,			          XK_apostrophe,	togglescratch,	{.ui = 1} },
  { MODKEY|ShiftMask,     XK_space,       togglefloating, {0} },
  { MODKEY,               XK_space,       zoom,           {0} },
  { MODKEY,               XK_0,           view,           {.ui = ~0} },
  { MODKEY,               XK_q,           killclient,     {0} },
	{ MODKEY,               XK_s,           togglesticky,   {0} },
  { MODKEY,               XK_f,           togglefullscr,  {0} },
  { MODKEY,               XK_g,           togglegaps,     {0} },
  { MODKEY|ShiftMask,     XK_g,           defaultgaps,    {0} },
  { MODKEY,               XK_l,           focusmon,       {.i = -1 } },
  { MODKEY,               XK_h,           focusmon,       {.i = +1 } },
  { MODKEY|ShiftMask,     XK_l,           tagmon,         {.i = -1 } },
  { MODKEY|ShiftMask,     XK_h,           tagmon,         {.i = +1 } },
  { MODKEY|ControlMask,   XK_l,           setmfact,       {.f = +0.05} },
  { MODKEY|ControlMask,   XK_h,           setmfact,       {.f = -0.05} },

  // ------ apps ------
  { MODKEY,               XK_d,           spawn,          SHCMD("dmenu_run") },
  { MODKEY|ShiftMask,     XK_w,           spawn,          SHCMD("dmenu_web-browsers") },
  { MODKEY|ShiftMask,     XK_e,           spawn,          SHCMD("dmenu_editconfs") },
  { MODKEY,               XK_w,           spawn,          SHCMD("firefox -P accounts_misc") },
  { MODKEY|ShiftMask,     XK_r,           spawn,          SHCMD("thunar") },
  { MODKEY,               XK_r,           spawn,          SHCMD("$TERMINAL -e lf") },
  { MODKEY,               XK_e,           spawn,          SHCMD("$TERMINAL -t 'Neomutt' -o window.dimensions.columns=120 -o window.dimensions.lines=32 -e neomutt") },

  // ------ function keys ------
  { MODKEY,               XK_F1,          setlayout,      {.v = &layouts[0]} },
  { MODKEY,               XK_F2,          setlayout,      {.v = &layouts[1]} },
  { MODKEY,               XK_F3,          setlayout,      {.v = &layouts[2]} },
  { MODKEY,               XK_F4,          setlayout,      {.v = &layouts[3]} },

  { MODKEY,               XK_F5,          spawn,          SHCMD("dmenu_wrapper") },
  { MODKEY,               XK_F6,          spawn,          SHCMD("dmenu_mount-wrapper") },
  { MODKEY,               XK_F7,          spawn,          SHCMD("dmenu_man") },
  { MODKEY,               XK_F8,          spawn,          SHCMD("dmenu_kill-process") },

  { MODKEY,               XK_F9,          spawn,          SHCMD("notify_toggle-dunst") },
  { MODKEY,               XK_F10,         spawn,          SHCMD("notify_calendar") },
  { MODKEY,		            XK_F11,		      spawn,		      SHCMD("notify_temp") },
  { MODKEY,               XK_F12,         spawn,          SHCMD("$TERMINAL -e yay -Syu") },

  // ------ special keys ------
  { MODKEY,               XK_grave,       spawn,          SHCMD("dmenu_emoji") },
  { MODKEY,               XK_BackSpace,   spawn,          SHCMD("dmenu_sysact") },
  { MODKEY|ShiftMask,     XK_BackSpace,   spawn,          SHCMD("slock") },

  { MODKEY,               XK_Insert,      spawn,          SHCMD("notify-send \"📋 Clipboard Contents\" \"$(xclip -o -selection clipboard)\"") },
  { MODKEY,               XK_Home,        spawn,          SHCMD("notify-send \"🏡 IP Address\" \"$(iplocal) $(sb_iplocate)\"") },

  { MODKEY,               XK_Print,       spawn,          SHCMD("notify-send -t 800 \"📸 Took Screenshot\" \"$(maim ~/Pictures/sshots/sshot-$(date '+%y_%m_%d-%H:%M:%S').png)\"") },
  { MODKEY|ShiftMask,     XK_Print,       spawn,          SHCMD("dmenu_maim") },
  { MODKEY,               XK_Scroll_Lock, spawn,          SHCMD("remaps & notify-send \"⌨️  Keyboard and Mouse remapping...\" \"Re-running defaults for any newly plugged-in peripherals.\"") },
  { MODKEY,               XK_Menu,        spawn,          SHCMD("xmenu_default") },

  { 0,                    XF86XK_AudioMute,               spawn,    SHCMD("pamixer -t; notify_vol; pkill -RTMIN+3 dwmblocks") },
  { 0,                    XF86XK_AudioRaiseVolume,        spawn,    SHCMD("pamixer -i 5; notify_vol; pkill -RTMIN+3 dwmblocks") },
  { MODKEY,               XF86XK_AudioRaiseVolume,        spawn,    SHCMD("pamixer --allow-boost -i 5; notify_vol; pkill -RTMIN+3 dwmblocks") },
  { 0,                    XF86XK_AudioLowerVolume,        spawn,    SHCMD("pamixer -d 5; notify_vol; pkill -RTMIN+3 dwmblocks") },
  { MODKEY,               XF86XK_AudioLowerVolume,        spawn,    SHCMD("pamixer --allow-boost -d 5; notify_vol; pkill -RTMIN+3 dwmblocks") },

  { MODKEY,               XF86XK_AudioPrev,               spawn,    SHCMD("applemuse_prev") },
  { MODKEY,               XF86XK_AudioPlay,               spawn,    SHCMD("applemuse_play") },
  { MODKEY,               XF86XK_AudioNext,               spawn,    SHCMD("applemuse_next") },

  // ------ stackkeys ------
	STACKKEYS(MODKEY,                       focus)
	STACKKEYS(MODKEY|ShiftMask,             push)

  // ------ tags ------
	TAGKEYS(                XK_1,           0)
	TAGKEYS(                XK_2,           1)
	TAGKEYS(                XK_3,           2)
	TAGKEYS(                XK_4,           3)
	TAGKEYS(                XK_5,           4)
	TAGKEYS(                XK_6,           5)
	TAGKEYS(                XK_7,           6)
	TAGKEYS(                XK_8,           7)
	TAGKEYS(                XK_9,           8)
};

/* button definitions - can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkRootWin,           0,              Button2,        togglebar,      {0} },
  { ClkRootWin,           0,              Button3,        spawn,          SHCMD("xmenu_default") },
	{ ClkLtSymbol,          0,              Button3,        layoutmenu,     {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
  { ClkWinTitle,          0,              Button3,        appmenu,        {0} }, 
	{ ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
	{ ClkStatusText,        0,              Button4,        sigdwmblocks,   {.i = 4} },
	{ ClkStatusText,        0,              Button5,        sigdwmblocks,   {.i = 5} },
	{ ClkStatusText,        ShiftMask,      Button1,        sigdwmblocks,   {.i = 6} },
};
