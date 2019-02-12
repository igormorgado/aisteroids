#ifndef __GAMEOBJNODE_H__
#define __GAMEOBJNODE_H__

typedef struct gameobjnode gameobjnode_st;
struct gameobjnode
{
    int              key;
    struct gameobj * obj;
    gameobjnode_st * prev;
    gameobjnode_st * next;
};

/* 
 * Memory management 
 */

/* Initializes a Gameobj node struct */
struct gameobjnode * gameobjnode__init(struct gameobj * obj);
void                 gameobjnode__free(struct gameobjnode * self);

/* List handling */
struct gameobjnode * gameobjnode__first(struct gameobjnode * self);
struct gameobjnode * gameobjnode__last(struct gameobjnode * self);
struct gameobjnode * gameobjnode__next(struct gameobjnode * self);
struct gameobjnode * gameobjnode__prev(struct gameobjnode * self);
struct gameobjnode * gameobjnode__next_by_key(struct gameobjnode * self, int key);
struct gameobjnode * gameobjnode__next_by_objtype(struct gameobjnode * self, int type);
struct gameobjnode * gameobjnode__next_by_objflag(struct gameobjnode * self, unsigned int obj_flag);

/* Should these two function receive a gameobjnode instead? */
void                 gameobjnode__add_after(struct gameobjnode * self, struct gameobj *obj);
void                 gameobjnode__add_before(struct gameobjnode * self, struct gameobj *obj);

void                 gameobjnode__delete(struct gameobjnode * self);

void                 gameobjnode__print(struct gameobjnode *self);
#endif /* __GAMEOBJNODE_H__ */
