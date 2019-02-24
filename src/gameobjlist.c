#include <stdlib.h>
#include <stdio.h>
#include "gameobj.h"
#include "gameobjnode.h"
#include "gameobjlist.h"
#include "common.h"


struct gameobjlist *
gameobjlist__init(void)
{
	struct gameobjlist *list;
	list = smalloc(sizeof *list);

	list->size = 0;
	list->front = NULL;
	list->back = NULL;

	return list;
}

/*
 * gameobjlist_add: Add a `struct gameobj` to `struct gameobjlist` front
 */
void
gameobjlist__add(struct gameobjlist *self, struct gameobj *obj)
{
	// Create a new node
	struct gameobjnode * node = gameobjnode__init(obj);

	// If we already have an object in front
	if(self->front)
	{
		node->key = self->front->key + 1;        // Key will +1 front key
		node->next = self->front;                // New node next point to front
		self->front->prev = node;                // front->prev points to node
	}

	self->front = node;                          // Node is the new front

	self->size += 1;                            // We add one to list size
}

/* This function frees the list */
void *
gameobjlist__free_list(struct gameobjlist *self)
{
	return sfree(self);
}

/* This function free all nodes in a list */
void *
gameobjlist__free_nodes(struct gameobjlist *self)
{

	struct gameobjnode *node;
	struct gameobjnode *next;
	node = self->front;
	while(node)
	{
		next = node->next;
		sfree(node);
		node = next;
	}
	return sfree(self);
}

/* This functions free all objects of all nodes in list */
void *
gameobjlist__free_objects(struct gameobjlist *self)
{
	return NULL;
}

/* This function free recursively all objects, nodes and the list itself */
void *
gameobjlist__free(struct gameobjlist *self)
{
	/* TODO:
	 * There is no reason to run the list twice, but we will do that
	 * for now
	 */
	// gameobjlist__free_objects(self);
	// gameobjlist__free_nodes(self);
	return gameobjlist__free_list(self);
}

struct gameobjnode *
gameobjlist__front(struct gameobjlist * self)
{
	return self->front;
}

struct gameobjnode *
gameobjlist__back(struct gameobjlist * self)
{
	return self->back;
}

size_t 
gameobjlist__size(struct gameobjlist * self)
{
	return self->size;
}

bool 
gameobjlist__empty(struct gameobjlist * self)
{
	return gameobjlist__size(self) == 0?true:false;
}


void
gameobjlist__push_front(struct gameobjlist * self, struct gameobj * obj)
{
	if(self) {
		if(self->front) {
			struct gameobjnode * node = gameobjnode__add_gameobj_before(self->front, obj);
			self->front = node;
		} else {
			struct gameobjnode * node = gameobjnode__init(obj);
			self->front = node;
			self->back = node;
		}
		self->size++;
	}
}

struct gameobj *
gameobjlist__pop_front(struct gameobjlist * self)
{
	struct gameobj * pobj;
	struct gameobjnode * pnode;
	if(self && self->front && self->front->obj) {
		pobj = self->front->obj;
		pnode = self->front->next;
		// TODO:
		// SHOULD I FREE HERE ? OR LEAVE FOR SOMEWHERE ELSE?
		// NEED TO THINK MORE ABOUT THE RELATIONSHIP
		// between OBJ, NODE and LIST
		gameobjnode__free(self->front);
		self->front = pnode;
		self->size--;
		if (gameobjlist__empty(self))
				self->back = NULL;
		return pobj;
	}
	return NULL;
}

struct gameobj *
gameobjlist__peek_front(struct gameobjlist * self)
{
	if(self && self->front)
		return self->front->obj;
	return NULL;
}

void
gameobjlist__push_back(struct gameobjlist * self, struct gameobj * obj)
{
	if(self) {
		if(self->back) {
			struct gameobjnode * node = gameobjnode__add_gameobj_after(self->back, obj);
			self->back = node;
			self->size++;
		} else {
			struct gameobjnode * node = gameobjnode__init(obj);
			self->front = node;
			self->back = node;
			self->size++;
		}
	}
}

struct gameobj *
gameobjlist__pop_back(struct gameobjlist * self)
{
	struct gameobj * pobj;
	struct gameobjnode * pnode;
	if(self && self->back && self->back->obj) {
		pobj = self->back->obj;
		pnode = self->back->prev;
		// TODO:
		// SHOULD I FREE HERE ? OR LEAVE FOR SOMEWHERE ELSE?
		// NEED TO THINK MORE ABOUT THE RELATIONSHIP
		// between OBJ, NODE and LIST
		gameobjnode__free(self->back);
		self->back = pnode;
		self->size--;
		if (gameobjlist__empty(self))
				self->front = NULL;
		return pobj;
	}
	return NULL;
}

struct gameobj *
gameobjlist__peek_back(struct gameobjlist * self)
{
	if(self && self->back)
		return self->back->obj;
	return NULL;
}


void
gameobjlist__debug_list(struct gameobjlist *self)
{
	struct gameobjnode *pnode;
	int i = 0;
	if (self) {
		printf("\nlist sz: %zu - addr: %p - front: %p - back: %p\n", 
				self->size, 
				(void *)self, 
				(void *)self->front, 
				(void *)self->back);
		if(self->front) {
			pnode = self->front;
			while (pnode) {
				printf("[%2d] (%10d) addr:%14p - prv: %14p - obj(%1d):%14p - next: %p\n", 
						i,
						pnode->key,
						(void *)pnode, 
						(void *)pnode->prev,
						pnode->obj->obj_flags,
						(void *)pnode->obj,
						(void *)pnode->next
				);
				pnode = gameobjnode__next(pnode);
				i++;
			}
		}
	}
	printf("\n");
}

void
gameobjlist__print(struct gameobjlist *self)
{
	struct gameobjnode *node;
	node = self->front;
	while(node) {
		gameobjnode__print(node);
		node = gameobjnode__next(node);
	}
}

