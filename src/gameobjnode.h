#ifndef __GAMEOBJNODE_H__
#define __GAMEOBJNODE_H__

struct gameobjnode
{
    int              key;
    struct gameobj * obj;
    struct gameobjnode * prev;
    struct gameobjnode * next;
};

/* 
 * Memory management 
 */

struct gameobjnode *	gameobjnode__init(struct gameobj * obj);
void *			gameobjnode__free(struct gameobjnode * self);
void			gameobjnode__delete(struct gameobjnode * self);

/* List handling */
struct gameobjnode *	gameobjnode__next(struct gameobjnode * self);
struct gameobjnode *	gameobjnode__prev(struct gameobjnode * self);
// struct gameobjnode * gameobjnode__next_by_key(struct gameobjnode * self, int key);
// struct gameobjnode * gameobjnode__next_by_objtype(struct gameobjnode * self, int type);
// struct gameobjnode * gameobjnode__next_by_objflag(struct gameobjnode * self, unsigned int obj_flag);
struct gameobjnode *	gameobjnode__first(struct gameobjnode * self);
struct gameobjnode *	gameobjnode__last(struct gameobjnode * self);
void			gameobjnode__add_after(struct gameobjnode * self, 
					       struct gameobjnode * node);
void			gameobjnode__add_before(struct gameobjnode * self, 
						struct gameobjnode * node);
struct gameobjnode *	gameobjnode__add_gameobj_after(struct gameobjnode * self, 
						       struct gameobj * node);
struct gameobjnode *	gameobjnode__add_gameobj_before(struct gameobjnode * self, 
							struct gameobj * node);

void			gameobjnode__print(struct gameobjnode * self);
#endif /* __GAMEOBJNODE_H__ */
