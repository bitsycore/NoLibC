#ifndef NOLIBC_NLC_AC_COLOR_H
#define NOLIBC_NLC_AC_COLOR_H

#define AC_RESET   "\x1b[0m"
#define AC_END     AC_RESET

#define AC_BOLD       "\x1b[1m"
#define AC_FAINT      "\x1b[2m"
#define AC_ITALIC     "\x1b[3m"
#define AC_UNDERLINE  "\x1b[4m"
#define AC_BLINK      "\x1b[5m"
#define AC_RAPIDBLINK "\x1b[6m"
#define AC_REVERSE    "\x1b[7m"
#define AC_CONCEAL    "\x1b[8m"
#define AC_STRIKE     "\x1b[9m"
#define AC_DOUBLEUNDER "\x1b[21m"
#define AC_NORMALINT  "\x1b[22m"
#define AC_OVERLINE   "\x1b[53m"

#define AC_BLACK   "\x1b[30m"
#define AC_RED     "\x1b[31m"
#define AC_GREEN   "\x1b[32m"
#define AC_YELLOW  "\x1b[33m"
#define AC_BLUE    "\x1b[34m"
#define AC_MAGENTA "\x1b[35m"
#define AC_CYAN    "\x1b[36m"
#define AC_WHITE   "\x1b[37m"

#define AC_BBLACK   "\x1b[90m"
#define AC_BRED     "\x1b[91m"
#define AC_BGREEN   "\x1b[92m"
#define AC_BYELLOW  "\x1b[93m"
#define AC_BBLUE    "\x1b[94m"
#define AC_BMAGENTA "\x1b[95m"
#define AC_BCYAN    "\x1b[96m"
#define AC_BWHITE   "\x1b[97m"

#define AC_BG_BLACK   "\x1b[40m"
#define AC_BG_RED     "\x1b[41m"
#define AC_BG_GREEN   "\x1b[42m"
#define AC_BG_YELLOW  "\x1b[43m"
#define AC_BG_BLUE    "\x1b[44m"
#define AC_BG_MAGENTA "\x1b[45m"
#define AC_BG_CYAN    "\x1b[46m"
#define AC_BG_WHITE   "\x1b[47m"

#define AC_BG_BBLACK   "\x1b[100m"
#define AC_BG_BRED     "\x1b[101m"
#define AC_BG_BGREEN   "\x1b[102m"
#define AC_BG_BYELLOW  "\x1b[103m"
#define AC_BG_BBLUE    "\x1b[104m"
#define AC_BG_BMAGENTA "\x1b[105m"
#define AC_BG_BCYAN    "\x1b[106m"
#define AC_BG_BWHITE   "\x1b[107m"

#define AC_FG256(n) "\x1b[38;5;" #n "m"
#define AC_BG256(n) "\x1b[48;5;" #n "m"

#define AC_RGB_FG(r,g,b) "\x1b[38;2;" #r ";" #g ";" #b "m"
#define AC_RGB_BG(r,g,b) "\x1b[48;2;" #r ";" #g ";" #b "m"

#endif //NOLIBC_NLC_AC_COLOR_H
