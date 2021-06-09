/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int showsystray        = 1;     /* 0 means no systray */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const char *fonts[]          = { "Mononoki Nerd Font:size=10" };
static const char dmenufont[]       = "Mononoki Nerd Font:size=10";

static const char norm_fg[] = "#d8dee9";
static const char norm_bg[] = "#2E3440";
static const char norm_border[] = "#4C566A";

static const char bar_border[] = "#4C566A";

static const char sel_fg[] = "#eceff4";
static const char sel_bg[] = "#4C566A";
static const char sel_border[] = "#8FBCBB";

static const char *colors[][3]      = {

  /*               fg           bg         border                         */
  [SchemeNorm]    = { norm_fg,  norm_bg,   norm_border }, // unfocused wins
  [SchemeSel]     = { sel_fg,   sel_bg,    sel_border },  // the focused win
 	[SchemeStatus]  = { norm_fg, norm_bg,  sel_fg  }, // Statusbar right {text,background,not used but cannot be empty}
 	[SchemeTagsSel]  = { sel_fg, sel_bg,  "#000000"  }, // Tagbar left selected {text,background,not used but cannot be empty}
  [SchemeTagsNorm]  = { norm_fg, norm_bg,  "#000000"  }, // Tagbar left unselected {text,background,not used but cannot be empty}
  [SchemeInfoSel]  = { sel_fg, sel_bg,  "#000000"  }, // infobar middle  selected {text,background,not used but cannot be empty}
  [SchemeInfoNorm]  = { norm_fg, norm_bg,  "#000000"  }, // infobar middle  unselected {text,background,not used but cannot be empty}
};

/* tagging */
static const char *tags[] = { "爵 ", " ", " ", " ", ""};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class        instance       title          tags mask     iscentered   isfloating   monitor 	scratch key*/
	{ "Alacritty",  "nmtui",       NULL,         ~0,            1,           1,           -1,       0 },
	{ "Alacritty",  "pulsemixer",  NULL,          0,            1,           1,           -1,       0 },
	{ "Alacritty",  "mutt",        NULL,          0,            1,           1,           -1,       0 },
	/* { "Alacritty",  "vifm",        NULL,          0,            1,           1,           -1,       0 }, */
  { "Dragon",     "dragon",      NULL,         ~0,            0,           1,           -1,       0 },
  { "trayer",     NULL,          NULL,         ~0,            0,           1,           -1,       0 },
	{ "Alacritty",  "scratchpad",  NULL,          0,            1,           1,           -1,      's' },
	{ "Alacritty",  "scratchpython", NULL,        0,            1,           1,           -1,      'p' },
	{ "Alacritty",  "cmus",        NULL,          0,            1,           1,           -1,      'm' },
	{ "stalonetray",NULL,          NULL,          0,            1,           1,           -1,      't' },
  { "firefox",    NULL,          NULL,          1,            0,           0,           -1,       0 },
  { "TelegramDesktop", NULL,     NULL,          1<<3,         0,           0,           -1,       0 },
  { "discord",    NULL,          NULL,          1<<3,         0,           0,           -1,       0 },
  { "code-oss",   NULL,          NULL,          1<<2,         0,           0,           -1,       0 },
  { "Gimp",       NULL,          NULL,          1<<4,         0,           0,           -1,       0 },
  { "Inkscape",   NULL,          NULL,          1<<4,         0,           0,           -1,       0 },
};

/* window swallowing */
static const int swaldecay = 3;
static const int swalretroactive = 1;
static const char swalsymbol[] = "﬒ ";

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ " 舘  ",      tile },    /* first entry is default */
	{ "   ",      NULL },    /* no layout function means floating behavior */
	{ "   ",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", norm_bg, "-nf", norm_fg, "-sb", sel_bg, "-sf", sel_fg, NULL };
static const char *termcmd[]  = { "alacritty", NULL };

/*First arg only serves to match against key in rules*/
static const char *terminal_scratchpadcmd[] = {"s", "alacritty", "--class", "scratchpad", NULL}; 
static const char *python_scratchpadcmd[] = {"p", "alacritty", "--class", "scratchpython", "-e", "ipython", NULL}; 
static const char *cmus_scratchpadcmd[] = {"m", "alacritty", "--class", "cmus", "-e", "cmus", NULL}; 
static const char *systray_scratchpadcmd[] = {"t", "stalonetray", NULL}; 

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_r,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|Mod1Mask,              XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_dead_circumflex,  togglescratch,  {.v = terminal_scratchpadcmd } },
	{ MODKEY|ShiftMask,             XK_dead_circumflex,  togglescratch,  {.v = python_scratchpadcmd } },
	{ MODKEY,                       XK_dead_acute,       togglescratch,  {.v = systray_scratchpadcmd } },
	{ MODKEY,                       XK_m,      togglescratch,  {.v = cmus_scratchpadcmd } },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_plus,   incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_minus,  incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_space,  zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_c,      killclient,     {0} },
	{ MODKEY|Mod1Mask,              XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|Mod1Mask,              XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY|Mod1Mask,              XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_f,      togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_u,      swalstopsel,    {0} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ControlMask,           XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkClientWin,         MODKEY|ShiftMask, Button1,      swalmouse,      {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

