# preprocessor

define для ifdef и тп можно задать через gcc опцию, те не обязательно прямо в коде, в коде вообще можно не задавать, если чё...

пример для define DEBUG который нужно устоноуить в 1 из gcc
gcc -DDEBUG=1 -02 и тд...

пример exept с возвратом значения:
```
#define exept(condition, seterr, errptr, gotoptr) { \
    bool cond = (condition); \
                             \
    if (true == cond) { \
    	errptr = seterr; \
    	goto gotoptr; \
    }\
    cond; \
}

```