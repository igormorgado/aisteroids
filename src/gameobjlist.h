#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

#include <sys/types.h>
#include "gameobj.h"

typedef struct gameobjnode gameobjnode_st;
struct gameobjnode
{
    int              key;
    struct gameobj * obj;
    gameobjnode_st * prev;
    gameobjnode_st * next;
};

typedef struct gameobjlist gameobjlist_st;
struct gameobjlist
{
    size_t        size;
    gameobjnode_st * head;
};


gameobjlist_st * gameobjlist__init(void);
void             gameobjlist__free(gameobjlist_st *self);
void             gameobjlist__add(gameobjlist_st *self, struct gameobj *obj);

// void          gameobjlist__remove(gameobjlist *self, gameobjnode *node);
// void          gameobjlist__remove_by_key(gameobjlist *self, int key);
// void          gameobjlist__remove_by_pos(gameobjlist *self, int pos);
//struct  gameobj     * gameobjlist__next_by_type(gameobjlist *self, int type);
//struct  gameobj     * gameobjlist__next_flag(gameobjlist *self, unsigned int objFlag);

void          gameobjlist__print(gameobjlist_st *self);
#endif
