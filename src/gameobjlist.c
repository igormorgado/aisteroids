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


struct gameobjnode *
gameobjlist__begin(struct gameobjlist * self)
{
	return self->head;
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
gameobjlist__print(struct gameobjlist *self)
{
	struct gameobjnode *node;
	node = self->head;
	while(node)
	{
		gameobjnode__print(node);
		node = gameobjnode__next(node);
	}
}

void *
gameobjlist__free(struct gameobjlist *self)
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

