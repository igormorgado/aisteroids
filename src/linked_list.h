#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

#include "gameobj.h"

typedef struct gameobjnode gameobjnode;
struct gameobjnode {
    int              key;
    struct gameobj * obj;
    gameobjnode * prev;
    gameobjnode * next;
};

typedef struct gameobjlist gameobjlist;
struct gameobjlist {
    size_t        size;
    gameobjnode * head;
};

gameobjlist * gameobjlist__init(void);
void          gameobjlist__destroy(gameobjlist *self);
void          gameobjlist__add(gameobjlist *self, gameobj *obj);

// void          gameobjlist__remove(gameobjlist *self, gameobjnode *node);
// void          gameobjlist__remove_by_key(gameobjlist *self, int key);
// void          gameobjlist__remove_by_pos(gameobjlist *self, int pos);
// gameobj     * gameobjlist__next_by_type(gameobjlist *self, int type);
// gameobj     * gameobjlist__next_flag(gameobjlist *self, unsigned int objFlag);

void          gameobjlist__print(gameobjlist *self);
#endif
