#ifndef SOCKET_STATS_H
#define SOCKET_STATS_H

#include "iostream"
#include <string.h>
#include "info.h"

#define ESTABLISHED 0
#define LISTENING 1
#define CONNECTED 2

using namespace std;
void getSocketInfo(struct info_settings &statistics, struct info_settings &first_stats);
void getInfo(struct info_settings &statistics, struct info_settings &first_stats, int mode);
#endif
