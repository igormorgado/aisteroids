#ifndef __GAMEOBJLIST_H__
#define __GAMEOBJLIST_H__

#include <sys/types.h>
#include "gameobj.h"
#include "gameobjnode.h"

struct gameobjlist
{
    size_t        size;
    gameobjnode_st * head;
    gameobjnode_st * tail;
};


struct gameobjlist * gameobjlist__init(void);
void                 gameobjlist__free(struct gameobjlist *self);
void                 gameobjlist__add(struct gameobjlist *self, struct gameobj *obj);
void                 gameobjlist__remove(struct gameobjlist * self, struct gameobjnode *node);
void                 gameobjlist__remove_by_key(struct gameobjlist * self, int key);
void                 gameobjlist__remove_by_pos(struct gameobjlist * self, int pos);

struct gameobjnode * gameobjlist__begin(struct gameobjlist * self);

void                 gameobjlist__foreach(struct gameobjlist * self, 
                                          void (*f)(struct gameobjnode *, void*),
                                          void * f_data);

void                 gameobjlist__print(struct gameobjlist *self);

#endif /* __GAMEOBJLIST_H__ */
