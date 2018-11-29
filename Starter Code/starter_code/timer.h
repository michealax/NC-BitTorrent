#ifndef TIMER_H
#define TIMER_H

#include <sys/timer.h>
#include "bt_parse.h"
#include "queue.h"
#include "chunk.h"
#include "sha.h"
#include "job.h"

int get_time(struct timeval *start);

#endif // TIMER_H
