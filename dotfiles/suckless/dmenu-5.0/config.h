/* See LICENSE file for copyright and license details. */
/* Default settings; can be overriden by command line. */

static int topbar = 1;                      /* -b  option; if 0, dmenu appears at bottom     */
/* -fn option overrides fonts[0]; default X11 font or font set */
static const char *fonts[] = {
	"mono:size=12.5"
};
static const char *prompt      = NULL;      /* -p  option; prompt to the left of input field */
static const char *colors[SchemeLast][2] = {
	/*                          fg         bg       */
	[SchemeNorm]          =  { "#BBBBBB", "#211e1d" },
	[SchemeSel]           =  { "#383838", "#f9f0c2" },
	[SchemeSelHighlight]  =  { "#3f3f3f", "#f9f0c2" },
	[SchemeNormHighlight] =  { "#383838", "#211e1d" },
	[SchemeOut]           =  { "#211e1d", "#f9f0c2" },
};
/* -l option; if nonzero, dmenu uses vertical list with given number of lines */
static unsigned int lines      = 15;

/*
 * Characters not considered part of a word while deleting words
 * for example: " /?\"&[]"
 */
static const char worddelimiters[] = " ";

/* Size of the window border */
static const unsigned int border_width = 2;

