## misra

+ [about](#about)
+ [rule_1_1](#rule_1_1)
+ [rule_1_2](#rule_1_2)
+ [rule_1_3](#rule_1_3)
+ [rule_2_1](#rule_2_1)
+ [rule_2_2](#rule_2_2)
+ [rule_2_3](#rule_2_3)
+ [rule_2_4](#rule_2_4)
+ [rule_2_5](#rule_2_5)
+ [rule_2_6](#rule_2_6)
+ [rule_2_7](#rule_2_7)


## about
MISRA (motor industry software reliability association) - стандарт для обеспечения надежности ПО в разработке встраеваемых транспрортных систем (хотя используется во всех критически важных системах).

```
1998 - MISRA-C:1988 (93 обязательныз правил и 34 рекомендательных)
2004 - MISRA-C:2004 (121 обязательныз правил и 20 рекомендательных, правила разделили на 21 категорию)
2012 - MISRA-C:2012 (123 обязательныз правил и 20 рекомендательных, 16 директив - правила связанные с процессами и процедурами)
2016 - MISRA-C:2016 (дополнение)
2020 - MISRA-C:2020 (переиздание MISRA-C:2016)
```

## rule_1_1
Исходный код и его синтаксис должны соответвовать стандартам и ограничениям языка, а также не превышать ограничея транзакций имплементаций (вторая часть предложения хз что значит).

Это просто требование соблюдать синтаксис языка.

## rule_1_2
Нельзя использовать языковые раширения кроме ассемблерных вставок.

## rule_1_3
В программе не долны быть неопределенного поведения. //todo ссылка

Все случаи неопределенного поведения описанны в Appendix H -> H.1 стандарта Си.

## rule_2_1
В проекте не должно быть не достижимого кода.

```
FILE *open_file(const char *file_name)
{
    FILE *f = fopen(file_name, "w");

    if (nullptr == f) {
    	exit(1);
    	printf("No such file: %s", file_name) // non-compliant, it is not reacheable
    }

	return f;
}
```

```
if (n < 10) return 10;
else if (n < 20) return 20;
else if (n < 30) return 30;
else if (n < 50) return 50;
else if (n < 40) return 40; // non-compliant, it is not reacheable
else if (n < 60) return 60;
```


## rule_2_2
В коде не должно быть мертвого кода, те таких конструкций которые работают в холостую как, к примеру, пустые циклы.
```
extern volatile uint16_t v;

extern char *p;

void f(void)
{
	uint16_t x;

	(void) v;       // compliant, the cast to void is permited

	(uint32_t) v;   // non-compliant, operator is dead
	v >> 3;         // non-compliant, operator is dead
	x = 3;          // non-compliant, operator is dead, since x not read subsequently

	*p++;           // non-compliant, result is not used
	(*p)++;         // compliant, *p is incremented
}
```


`__asm("NOP");` - несчитается такой конструкцией.

Пустые функции не являются мёртвым кодом тк от их оптимизации работа программы не изменится.

```
void g (void) 
{

}

void h (void)
{
	g();
}
```
## rule_2_3
В проекте не должны быть объявлены не используемые типы данных.

ТК не ясно забыто ли это по ошибке или является избыточным.

## rule_2_4
В проекте не должны быть объявлены не используемые тэги.

ТК не ясно забыто ли это по ошибке или является избыточным.

```
typedef struct st {
	uint8_t a;
	uint8_t b;
	bool    c;
} rec;

bool unused_tag(void) 
{
	enum state (e_init, e_run, e_sleep); // non-compliant

    rec.c = true;

    return rec.c; // non-compliant, since in programm used only 'c' field
}
```

## rule_2_5
В проекте не должны быть объявлены не используемые макросы.

ТК не ясно забыто ли это по ошибке или является избыточным.

## rule_2_6
В проекте не должны быть объявлены не используемые лэйблэ `goto`.

```
string unused_label(int inc) 
{
	int c = 10 + inc;

	if (15 == c) {
		goto ret;
	} else {
        goto ret2;
	}

ret:
    return "ret"
ret2:
    return "ret2"
label:
    return "label"; // non-compliant, since label is unused
}
```

## rule_2_7
В проекте не должны быть объявлены не используемые параметры функций тк не ясно ошибка это или нет.