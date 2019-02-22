#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "gameobj.h"
#include "gameobjnode.h"
#include "common.h" 

struct gameobjnode *
gameobjnode__init(struct gameobj * obj)
{
    // TODO:
    // How to handle kew assignment without know the last key added to list?
    // Maybe a large random value to avoid conflict? 
    struct gameobjnode * self;
    self = smalloc(sizeof *self);
    self->key = rand();      
    self->obj = obj;
    self->prev = NULL;
    self->next = NULL;

    return self;
}

void
gameobjnode__delete(struct gameobjnode * self)
{

	if(self->prev)
		self->prev->next = self->next;

	if(self->next)
		self->next->prev = self->prev;
}

void *
gameobjnode__free(struct gameobjnode * self)
{
	gameobjnode__delete(self);

	/* TODO:
	 *
	 * Should we also free the self->obj?
	 *
	 * Or should we return self->obj to be cleaned by caller?
	 */
	return sfree(self);
}

struct gameobjnode * 
gameobjnode__next(struct gameobjnode * self)
{
	if(self && self->next) 
		return self->next;
	return NULL;
}

struct gameobjnode *
gameobjnode__prev(struct gameobjnode * self)
{
	if(self && self->prev) 
		return self->prev;
	return NULL;
}

struct gameobjnode *
gameobjnode__first(struct gameobjnode *self)
{
	struct gameobjnode * pnode = self;
	while(pnode->prev) 
		pnode = gameobjnode__prev(pnode);
	return pnode;
}

struct gameobjnode *
gameobjnode__last(struct gameobjnode *self)
{
	struct gameobjnode * pnode = self;
	while(pnode->next)
		pnode = gameobjnode__next(pnode);
	return pnode;
}

/* TODO:
 * Need to rethink way these functions should work since my plan is be able
 * to use those sequentialy or composing them.
 * There is two options right now (none of those is able to completely solve
 * the problem
 *
 * One solution is `next_by_key` being able to return the element that the
 * pointer points too. Doing that composition isn't possible since next calls
 * will always return the same address. Of course the caller can do a
 * workaround calling one for the actual then a loop for the next, but that
 * isn't planned right now.
 *
 * The second way of thinking is to `next_by_key` always returns elements AFTER
 * the where the pointer points too, in this case it never finds where actualy
 * points too. But with that it becames impossible to find a value that exists
 * in the first element, since it will never read it. A workaround is also on
 * caller where we can first check if the first element matches the value then
 * keep going, but its also treats special cases (not intended).
 *
 * Maybe returning the object itself (it exists) and passing the pointer + 1 in
 * the caller should be the best way (like python3 list.index does).
 */

// struct gameobjnode *
// gameobjnode__next_by_key(struct gameobjnode * self, int key)
// {
//     struct gameobjnode * pnode;
//     pnode = self->next;
//     while(pnode)
//     {
//         if(pnode->key == key)
//             return pnode;
// 
//         pnode = pnode->next;
//     }
//     return NULL;
// }
       

// struct gameobjnode *
// gameobjnode__next_by_objtype(struct gameobjnode * self, int type)
// {
//     struct gameobjnode * pnode;
//     pnode = self;
//     while(pnode->next)
//     {
//         if(pnode->obj->type == type)
//         {
//             return pnode;
//         }
//         pnode = pnode->next;
//     }
//     return NULL;
// }

       
// struct gameobjnode *
// gameobjnode__next_by_objflag(struct gameobjnode * self, unsigned int obj_flag)
// {
//     struct gameobjnode * pnode;
//     pnode = self->next;
//     while(pnode)
//     {
//         if(pnode->obj->obj_flag &= obj_flag)
//             return pnode;
// 
//         pnode = pnode->next;
//     }
//     return NULL;
// }


void
gameobjnode__add_after(struct gameobjnode * self, struct gameobjnode * node)
{
	if(self) {
		if(self->next) {
			node->next = self->next;
			self->next->prev = node;
		}
		self->next = node;
	}
	node->prev = self;
}

struct gameobjnode *
gameobjnode__add_gameobj_after(struct gameobjnode * self, struct gameobj * obj)
{
    struct gameobjnode * newnode = gameobjnode__init(obj);
    gameobjnode__add_after(self, newnode);
    return newnode;
}

void
gameobjnode__add_before(struct gameobjnode * self, struct gameobjnode *node)
{
	if(self) {
		if(self->prev) {
			node->prev = self->prev;
			self->prev->next = node;
		}
		self->prev = node;
	}
	node->next = self;
}

struct gameobjnode *
gameobjnode__add_gameobj_before(struct gameobjnode * self, struct gameobj * obj)
{
    struct gameobjnode * newnode = gameobjnode__init(obj);
    gameobjnode__add_before(self, newnode);
    return newnode;
}

void
gameobjnode__print(struct gameobjnode * self)
{
	char *sfmt = point3f_fmt(&self->obj->position);
	printf("[%d] - Type: %d - Flags: %d -  Active: %5s - prev %p - next %p -  Pos (%s)\n",
	        self->key,
	        self->obj->type,
	        self->obj->obj_flags,
	        self->obj->active ? "true":"false",
		(void *)self->prev,
		(void *)self->next,
		sfmt
	);
	sfree(sfmt);
}


