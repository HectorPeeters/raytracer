#pragma once

#define ANSI_RESET "\x1B[0m"
#define ANSI_BLACK "\x1B[30m"
#define ANSI_RED "\x1B[31m"
#define ANSI_GREEN "\x1B[32m"
#define ANSI_YELLOW "\x1B[33m"
#define ANSI_BLUE "\x1B[34m"
#define ANSI_MAGENTA "\x1B[35m"
#define ANSI_CYAN "\x1B[36m"
#define ANSI_WHITE "\x1B[37m"

enum t_log_type { debug, info, warning, error };

#define LDEBG(fmt...) rtlog(debug, __LINE__, __FILE__, fmt)
#define LINFO(fmt...) rtlog(info, __LINE__, __FILE__, fmt)
#define LWARN(fmt...) rtlog(warning, __LINE__, __FILE__, fmt)
#define LERR(fmt...) rtlog(error, __LINE__, __FILE__, fmt)

void rtlog(enum t_log_type type, int line, const char *file, const char *fmt,
           ...);
