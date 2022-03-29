#if (0 == defined(MACROUTILS_H))
#define MACROUTILS_H

#define arr_len(array) (sizeof (array) / sizeof (*(array)))

#define arr_foreach(var, arr) \
   for (long keep = 1, cnt = 0, size = arr_len(arr); keep && (cnt < size); keep = !keep, cnt++) \
       for (typeof(*(arr)) var = (arr)[cnt]; keep; keep = !keep) \

#endif
