#ifndef _ADLIST_H_
#define _ADLIST_H_

/**
 * Node, List and Iterator are the only data structures used currently
 */
typedef struct listNode {
  struct listNode* prev;
  struct listNode* next;
  void* value;
} listNode;


typedef struct listIter {
  listNode* next;
  int direction;
} listIter;


typedef struct list {
  listNode* head;
  listNode* tail;
  void* (*dup)(void* ptr);
  void (*free)(void* ptr);
  int (*match)(void* ptr, void* key);
  unsigned long len;
} list;

// Functions implemented as macros

#define listLength(l) ((l)->len)
#define listFirst(l) ((l)->head)
#define listLast(l) ((l)->tail)
#define listPrevNode(n) ((n)->prev)
#define listNextNode(n) ((n)->next)
#define listNodeValue(n) ((n)->value)

#define listSetDupMethod(l, m) ((l)->dup = (m))
#define listSetFreeMethod(l, m) ((l)->free = (m))
#define listSetMatchMethod(l, m) ((l)->match = (m))

#define listGetDupMethod(l) ((l)->dup)
#define listGetFreeMethod(l) ((l)->free)
#define listGetMatchMethod(l) ((l)->match)

/**
 * Prototypes
 */

/**
 * Create a linked list
 */
list* listCreate(void);\

/**
 * Remove the linked list
 */
void listRelease(list* list);

/**
 * Make the linked list
 * empty
 */
void listEmpty(list* list);

/**
 * Add head node
 * to linked list
 */
list* listAddNodeHead(list* list, void* value);

/**
 * Add tail node
 * to linked list
 */
list* listAddNodeTail(list* list, void* value);

/**
 * Add node node
 * insted of old_node
 */
list* listInsertNode(list* list, listNode* old_node, void* value, int after);

/**
 * Delete node from
 * linked list
 */
void listDelNode(list* list, listNode* node);

listIter* listGetIterator(list* list, int direction);
listNode* listNext(listIter* iter);

void listReleaseIterator(listIter* iter);
list* listDup(list* origin);

listNode* listSearchKey(list* list, void* key);
listNode* listIndex(list* list, long index);

void listRewind(list* list, listIter* li);
void listRewindTail(list* list, listIter* li);
void listRotate(list* list);
void listJoin(list* l, list* o);

/**
 * Directionsfor iterators
 */
#define AL_START_HEAD 0
#define AL_START_TAIL 1 

#endif // _ADLIST_H_
