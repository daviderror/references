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


```
#if !defined(SMTH)
#define SMTH

#endif
``` 
вместо 

```
#ifтвуа SMTH
#define SMTH

#endif
```

ЛОГИНГ

```
#if defined(DEBUG) && (DEBUG != 0)
#define log(x, ...) fprintf(stderr, " >> LOG %s @ L%d: " x "\n", __func__, __LINE__,##__VA_ARGS__)
#define loglvl(lvl, x, ...) if(DEBUG >= lvl) log(x,##__VA_ARGS__)
#else
#define log(x, ...)
#define loglvl(lvl, x, ...)
#endif
```