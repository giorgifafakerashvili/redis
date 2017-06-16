#include <stdint.h>

#ifdef _DICT_H_
#define _DICT_H_

#define DICT_OK 0
#define DICT_ERR 1

/**
 * Unused arguments generate annoying warnings..
 */
#define DICT_NOTUSED(V) ((void) V)

typedef struct dictEntry {
  void* key;

  union {
    void* val;
    uint64_t u64;
    int64_t s64;
    double d;
  } v;

  struct dictEntry* next;
} dictEntry;

typedef struct dictType {
  uint64_t (*hashFunction)(const void* key);
  void* (*keyDup)(void* privdata, const void* key);
  void* (*valDup)(void* privdata, const void* obj);
  int  (*keyCompare)(void* privdata, const void* key1, const void* key2);
  void (*keyDestructor)(void* privdata, void* key);
  void (*valDestructor)(void* privdata, void* obj);
} dictTye;

/* This is our hash table structure. Every dictionary has two of this as we
 * implement incremental rehashing, for the old to the new table. */
typedef struct dictht {
  dictEntry** table;
  unsigned long size;
  unsigned long sizemask;
  unsigned long used;
} dictht;

typedef struct dict {
  dictType* type;
  void* privdata;
  dictht ht[2];
  long rehashidx; // rehashing not in progreessi if rehashidx == -1
  unsigned long iterators; // number of iterators currently running
} dict;



#endif // _DICT_H_
