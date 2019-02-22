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
	list->head = NULL;
	list->tail = NULL;

	return list;
}

/*
 * gameobjlist_add: Add a `struct gameobj` to `struct gameobjlist` head
 */
void
gameobjlist__add(struct gameobjlist *self, struct gameobj *obj)
{
	// Create a new node
	struct gameobjnode * node = gameobjnode__init(obj);

	// If we already have an object in head
	if(self->head)
	{
		node->key = self->head->key + 1;        // Key will +1 head key
		node->next = self->head;                // New node next point to head
		self->head->prev = node;                // head->prev points to node
	}

	self->head = node;                          // Node is the new head

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
	node = self->head;
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
gameobjlist__begin(struct gameobjlist * self)
{
	return self->head;
}

struct gameobjnode *
gameobjlist__end(struct gameobjlist * self)
{
	return self->tail;
}

int 
gameobjlist__size(struct gameobjlist * self)
{
	return self->size;
}


void
gameobjlist__push_head(struct gameobjlist * self, struct gameobj * obj)
{
	if(self) {
		if(self->head) {
			// printf("\nTem cabeca\n");
			struct gameobjnode * node = gameobjnode__add_gameobj_before(self->head, obj);
			self->head = node;
		} else {
			// printf("\nNAO Tem cabeca\n");
			struct gameobjnode * node = gameobjnode__init(obj);
			self->head = node;
			self->tail = node;
		}
		self->size++;
	}
}

struct gameobj *
gameobjlist__pop_head(struct gameobjlist * self)
{
	struct gameobj * pobj;
	struct gameobjnode * pnode;
	if(self && self->head && self->head->obj) {
		pobj = self->head->obj;
		pnode = self->head->next;
		// TODO:
		// SHOULD I FREE HERE ? OR LEAVE FOR SOMEWHERE ELSE?
		// NEED TO THINK MORE ABOUT THE RELATIONSHIP
		// between OBJ, NODE and LIST
		gameobjnode__free(self->head);
		self->head = pnode;
		self->size--;
		return pobj;
	}
	return NULL;
}

struct gameobj *
gameobjlist__peek_head(struct gameobjlist * self)
{
	if(self && self->head && self->head->obj)
		return self->head->obj;
	return NULL;
}

void
gameobjlist__push_tail(struct gameobjlist * self, struct gameobj * obj)
{
	if(self) {
		if(self->tail) {
			gameobjnode__add_gameobj_after(self->tail, obj);
		} else {
			struct gameobjnode * node = gameobjnode__init(obj);
			self->head = node;
			self->tail = node;
		}
		self->size++;
	}
}

struct gameobj *
gameobjlist__pop_tail(struct gameobjlist * self)
{
	struct gameobj * pobj;
	if(self && self->head && self->head->obj) {
		pobj = self->head->obj;
		gameobjnode__free(self->head);
		self->size--;
		return pobj;
	}
	return NULL;
}

struct gameobj *
gameobjlist__peek_tail(struct gameobjlist * self)
{
	if(self && self->tail && self->tail->obj)
		return self->tail->obj;
	return NULL;
}

// struct gameobj *
// gameobjnode__next(struct gameobjlist * self, struct gameobjnode * node)
// {
//     return node->next;
// }
// 
// struct gameobj *
// gameobjnode__next_by_flag(struct gameobjlist * self, struct gameobjnode * node)
// {
//     return node->next;
// }
// 
// struct gameobj *
// gameobjlist__prev(struct gameobjlist * self, struct gameobjnode * node)
// {
//     return node->prev;
// }
// 
// // NOT GUD MAKES NOT MUCH SENSE =/
// struct gameobj *
// gameobjlist__end(struct gameobjlist * self, struct gameobjnode * node)
// {
//     return node->next;
// }
// 
// void
// gameobjlist__delete(struct gameobjlist * self, struct gameobjnode * node)
// {
// 
//     if(node->prev)
//         node->prev->next = node->next;
// 
//     if(node->next)
//         node->next->prev = node->prev;
// 
//     self->size--;
// 
//     // TODO:
//     // LEMBRE-SE ESTAMOS REMOVENDO O NODE MAS NAO O OBJETO QUE O NODE SE 
//     // REFERENCIA, ESTE DEVE SER REMOVIDO EM OUTRO LUGAR
//     // MAS SERA QUE SERA POSSIVEL?
//     // TALVEZ ADICIONAR UM CONTADOR DE USOS AOS OBJS E NO CASO DO CONTADOR
//     // SER 0 remover tambem o objeto ao qual o no se refere
//     free(node);
// }

void
gameobjlist__debug_list(struct gameobjlist *self)
{
	struct gameobjnode *pnode;
	int i = 0;
	if (self) {
		printf("\nlist sz: %zu - addr: %p - head: %p - tail: %p\n", 
				self->size, 
				(void *) self, 
				(void *)self->head, 
				(void *)self->tail);
		if(self->head) {
			pnode = self->head;
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
	node = self->head;
	while(node) {
		gameobjnode__print(node);
		node = gameobjnode__next(node);
	}
}

