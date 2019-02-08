#include <stdlib.h>
#include <stdio.h>
#include "gameobj.h"
#include "gameobjlist.h"


gameobjlist_st *
gameobjlist__init(void)
{
    gameobjlist_st *list;
    list = malloc(sizeof *list);

    list->size = 0;
    list->head = NULL;

    return list;
}

void
gameobjlist__add(gameobjlist_st *self, struct gameobj *obj)
{
    // Create a new node
    gameobjnode_st * node;
    node = malloc(sizeof *node);

    // Associate the object to the new node
    node->obj = obj;

    // New node has no prev/next relationship and key by default is 0
    node->next = NULL;
    node->prev = NULL;
    node->key = 0;

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

void
gameobjlist__print(gameobjlist_st *self)
{
    gameobjnode_st *node;
    node = self->head;
    while(node)
    {
        printf("[%d] - Type: %d - Flags: %d -  Active: %s - Pos (%s)\n",
                node->key,
                node->obj->type,
                node->obj->obj_flags,
                node->obj->active ? "true":"false",
                point3f_fmt(node->obj->position)
        );

        node = node->next;
    }
}

void
gameobjlist__free(gameobjlist_st *self)
{
    gameobjnode_st *node;
    gameobjnode_st *next;
    node = self->head;
    while(node)
    {
        next = node->next;
        free(node);
        node = next;
    }
    free(self);


}
