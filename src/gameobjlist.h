#ifndef __GAMEOBJLIST_H__
#define __GAMEOBJLIST_H__

#include <sys/types.h>
#include "gameobj.h"
#include "gameobjnode.h"

/* TODO:
 * Should we add a reference to every list member in struct?
 */
struct gameobjlist
{
    size_t        size;
    struct gameobjnode * head;
    struct gameobjnode * tail;
};


struct gameobjlist *	gameobjlist__init(void);
void *			gameobjlist__free(struct gameobjlist *self);
void *			gameobjlist__free_list(struct gameobjlist *self);
void *			gameobjlist__free_nodes(struct gameobjlist *self);
void *			gameobjlist__free_objects(struct gameobjlist *self);
int			gameobjlist__size(struct gameobjlist * self);

// TODO: SHould these work with gameobj instead nodes?
struct gameobjnode *	gameobjlist__begin(struct gameobjlist * self);
struct gameobjnode * 	gameobjlist__end(struct gameobjlist * self);
void                 	gameobjlist__push_head(struct gameobjlist *self, struct gameobj *obj);
struct gameobj *     	gameobjlist__peek_head(struct gameobjlist *self);
struct gameobj *     	gameobjlist__pop_head(struct gameobjlist *self);
void                 	gameobjlist__push_tail(struct gameobjlist *self, struct gameobj *obj);
struct gameobj *     	gameobjlist__peek_tail(struct gameobjlist *self);
struct gameobj *     	gameobjlist__pop_tail(struct gameobjlist *self);
// void                 gameobjlist__remove(struct gameobjlist * self, struct gameobjnode *node);
// void                 gameobjlist__remove_by_key(struct gameobjlist * self, int key);
// void                 gameobjlist__remove_by_pos(struct gameobjlist * self, int pos);
// void                 gameobjlist__foreach(struct gameobjlist * self, 
//                                           void (*f)(struct gameobjnode *, void*),
//                                           void * f_data);

void			gameobjlist__debug_list(struct gameobjlist * self);
void			gameobjlist__print(struct gameobjlist * self);

#endif /* __GAMEOBJLIST_H__ */
