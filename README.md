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
gcc -g -fms-extensions  -c -o obj/ship.o src/ship.c 
In file included from src/ship.h:6,
                 from src/ship.c:4:
src/control.h:16:5: error: unknown type name ‘Ship’
     Ship * ship;
     ^~~~
src/control.h:20:25: error: unknown type name ‘Ship’
 Control * control__init(Ship * ship, int type);
                         ^~~~
src/control.h:23:40: error: unknown type name ‘Ship’
 void control__set_ship(Control * self, Ship * ship);
                                        ^~~~
make: *** [Makefile:15: obj/ship.o] Error 1
```

Help me to fix! ;-)


