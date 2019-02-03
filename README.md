# AIsteroids

A AI testbed over asteroids

# Build

```
git clone https://github.com/igormorgado/aisteroids.git
cd aisteroids
make
```

# ERROR

```
$ make
gcc -g -fms-extensions  -DDEBUG -c -o obj/gameobj.o src/gameobj.c
gcc -g -fms-extensions  -DDEBUG -c -o obj/linked_list.o src/linked_list.c
src/linked_list.c: In function ‘gameobjlist__add’:
src/linked_list.c:27:15: error: incompatible types when assigning to type ‘union <anonymous>’ from type ‘gameobj *’ {aka ‘struct gameobj *’}
     node->obj = obj;
               ^
src/linked_list.c: In function ‘gameobjlist__print’:
src/linked_list.c:56:26: error: invalid type argument of ‘->’ (have ‘union <anonymous>’)
                 node->obj->type,
                          ^~
src/linked_list.c:57:26: error: invalid type argument of ‘->’ (have ‘union <anonymous>’)
                 node->obj->objFlags,
                          ^~
src/linked_list.c:58:26: error: invalid type argument of ‘->’ (have ‘union <anonymous>’)
                 node->obj->active ? "true":"false",
                          ^~
src/linked_list.c:59:38: error: invalid type argument of ‘->’ (have ‘union <anonymous>’)
                 point3f_fmt(node->obj->position)
                                      ^~
make: *** [Makefile:16: obj/linked_list.o] Error 1
```

How to make the union work?


# Coding conventions

1. function naming should use `underscore_separated_words()` and **not**
`CamelCaseNamingConvention`.

2. variable naming should use `almostCamelCaseNaming`, for now, probably it 
will be changed in future.

3. Every game entity is described in its own source file and header file, for
example a *ship* object is described in `ship.c` and `ship.h` respectively.

4. All functions related to a game object (using the same example the *ship* 
needs to be named using the format `gameobject__function_name()`, for example a
function to turn ship left would be named `ship__turn_left()`. That is for 
a clear "namespace"  like structure. Avoid things to be english readable as 
`turn_ship_left()`.

5. Functions that act over a game object **MUST** have it's first parameter as 
the object itself (like python classes/object declaration). For example the 
function defined above `ship__turn_left()` prototype could be: 
`void ship__turn_left(struct ship * self, float angle)`.

6. Use `self` as the variable name for the self reference in game objects for 
sake of organization and readibility. Of course you would be tempted to use 
some name that represent the object itself using example above `struct ship * ship`,
but in long run this will make harder to read.

7. Be descriptive in naming, variable and functions should be self explanatory 
at least for a small degree of precision, of course details would go on internal
documentation.



