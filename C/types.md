# types

1.  [float_double](#float_double)


## float_double

    Литералы; 0.1 (double), 0.1L (lomg double), 0.1f (float)

    Bad case:
```
#include <stdio.h>

if ((0.1 + 0.2) == 0.3) {
	printf("T");
}
else {
	printf("F");
}
```
    printf log: F
```
printf("%.30lf != %.30lf", 0.1 + 0.2, 0.3);
```
    printf log: 0.3000000000000000444 != 0.2999999999999999888

    Good case:
```
#include <stdio.h>
#include <math.h>
 
double res = 0.1 + 0.2;

const double eps = 1e-8, // эпсилон задающий точность
             comp = 0.3;

if (dabs(res - comp) <= eps) { // fabs для float
	printf("T");
}
else {
	printf("F");
}
```
    printf log: T