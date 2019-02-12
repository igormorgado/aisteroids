#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "gameobj.h"
#include "gameobjnode.h"

struct gameobjnode *
gameobjnode__init(struct gameobj * obj)
{
    // TODO:
    // How to handle kew assignment without know the last key added to list?
    // Maybe a large random value to avoid conflict? 
    struct gameobjnode * self;
    self = malloc(sizeof *self);
    self->key = 0;      
    self->obj = obj;
    self->prev = NULL;
    self->next = NULL;

    return self;
}

void
gameobjnode__free(struct gameobjnode * self)
{
    if(self->prev)
        self->prev->next = self->next;

    if(self->next)
        self->next->prev = self->prev;

    /* TODO:
     *
     * Should we also free the self->obj?
     *
     * Or should we return self->obj to be cleaned by caller?
     */
    
    free(self);

    return;
}

struct gameobjnode * 
gameobjnode__next(struct gameobjnode * self)
{
    return self->next;
}

struct gameobjnode *
gameobjnode__prev(struct gameobjnode * self)
{
    return self->prev;
}

struct gameobjnode *
gameobjnode__first(struct gameobjnode *self)
{
    struct gameobjnode * pnode = self;
    while(pnode)
    {
        pnode = gameobjnode__prev(self);
    }
    return pnode;
}

struct gameobjnode *
gameobjnode__last(struct gameobjnode *self)
{
    struct gameobjnode * pnode = self;
    while(pnode)
    {
        pnode = gameobjnode__next(self);
    }
    return pnode;
}

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
gameobjnode__add_after(struct gameobjnode * self, struct gameobj * obj)
{
    struct gameobjnode * newnode = gameobjnode__init(obj);

    if(self->next) {
        newnode->next = self->next;
        self->next->prev = newnode;
    }

    newnode->prev = self;
    self->next = newnode;
}

void
gameobjnode__add_before(struct gameobjnode * self, struct gameobj *obj)
{
    struct gameobjnode * newnode = gameobjnode__init(obj);

    if(self->prev) {
        newnode->prev = self->prev;
        self->prev->next = newnode;
    }

    newnode->next = self;
    self->prev = newnode;
}

void 
gameobjnode__delete(struct gameobjnode * self)
{

    if(self->prev)
        self->prev->next = self->next;

    if(self->next)
        self->next->prev = self->prev;

    free(self);
}

void
gameobjnode__print(struct gameobjnode * self)
{
	char *sfmt = point3f_fmt(self->obj->position);
	printf("[%d] - Type: %d - Flags: %d -  Active: %5s - Pos (%s)\n",
	        self->key,
	        self->obj->type,
	        self->obj->obj_flags,
	        self->obj->active ? "true":"false",
		sfmt
	);
	free(sfmt);
}


