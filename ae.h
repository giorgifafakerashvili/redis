#ifndef _AE_H_
#define _AE_H_

#include <time.h>

#define AE_OK   0
#define AE_ERR  -1

#define AE_NONE   0
#define AE_READABEL  1
#define AE_WRITABLE  2


#define AE_FILE_EVENT   1
#define AE_TIME_EVENT   2
#define AE_ALL_EVENTS (AE_FILE_EVENT | AE_TIME_EVENT)
#define AE_DONT_WAIT 4

#define AE_NOMORE -1
#define AE_DELETED_EVENT_ID -1

/**
 * Macros
 */
#define AE_NOTUSED(V) ((void)V)

struct aeEventLoop;

/**
 * Types and data structures
 */
typedef void aeFileProc(struct aeEventLoop* eventLoop, int fd, void* clientData, int mask);
typedef int aeTimeProc(struct aeEventLoop* eventLoop, long long id, void* clientData);
typedef void aeEventFinalizerProc(struct aeEventLoop* eventLoop, void* clientData);
typedef void aeBeforeSleepProc(struct aeEventLoop* eventLoop);

/**
 * File event structure
 */
typedef struct aeFileEvent {
  int mask; // one of AE_(READABLE|WRIABLE)
  aeFileProc* rfileProc;
  aeFileProc* wfileProc;
  void* clientData;
} aeFileEvent;

/**
 * Time Event Structure
 */
typedef struct aeTimeEvent {
  long long id; // time event identifier
  long when_sec; // seconds
  long when_ms; // milliseconds
  aeTimeProc* timeProc;
  aeEventFinalizerProc* finalizerProc;
  void* clientData;
  struct aeTimeEvent* next;
} aeTimeEvent;

/**
 * A fired event
 */
typedef struct aeFiredEvent {
  int fd;
  int mask;
} aeFiredEvent;

/**
 * State of an event based program
 */
typedef struct aeEventLoop {
  int maxfd; // highest file descriptor currently registered
  int setsize; // max number of file descriptors tracked
  long long timeEventnextId;
  time_t lastTime; // used to detect system clock now
  aeFileEvent* events; // registered events
  aeFiredEvent* fired; // fired events
  aeTimeEvent* timeEventHead;
  int stop;
  void* apidata; // this is used for polling API specifying data
  aeBeforeSleepProc* beforesleep;
  aeBeforeSleepProc* aftersleep;
} aeEventLoop;



#endif
