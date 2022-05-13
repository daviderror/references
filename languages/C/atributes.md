# atributes

+ [about](#about)
+ [variable_atributes](#variable_atributes)
+ [struct_atributes](#struct_atributes)
+ [function_atributes](#function_atributes)

## about
Атрибуты позволяют специфицировать возможности переменных, функцийб структур, union, является расширением.

[референс](#https://gcc.gnu.org/onlinedocs/gcc/Function-Attributes.html)

## variable_atributes
`__attribute__((used))` - делает переменную или функцию статической.
`__attribute__((sector("name")))` - размещает переменную в определённый сектор данных программы.

## struct_atributes
Есть структура:
```
struct example {
	char a;
	char b;
	int x;
};
```
То при `sizeof (struct example`, на 64 ращрядной машине, вернет размер 8 байт, тк компилятор сложит a,b,x + 2 оставшихся байта в одно машинное слово.

Добавив атрибут в эту структуру:
```
struct example {
	char a;
	char b;
	int x;
} __attribute__((packed));
```
Можно через `#pragma pack(2)`, где 2 это степень сжатия структуры: 
```
#pragma pack(2)

struct example {
	char a;
	char b;
	int x;
} __attribute__((packed));
```

## function_atributes

### constructor and destructor
Если:
```
void __attribute__((constructor)) init();
void __attribute__((destructor)) end();

int main(void) 
{
	printf("main\n");
}

void __attribute__((constructor)) init()
{
	printf("init\n");
}

void __attribute__((destructor)) end() 
{
	printf("end\n");
}
```
То вывод будет:
```
init
main
end
```
Те этот атрибут позволяет запускать функции до запуска main и после выхода из main. Это можно сделать `#pragma`:
```
#pragma startup init
#pragma exit end

int main(void) 
{
	printf("main\n");
}

void __attribute__((constructor)) init()
{
	printf("init\n");
}

void __attribute__((constructor)) end() 
{
	printf("end\n");
}
```
### alias
Если в атрибуте указан `weak` и нет реализации `f(void)`, то будет выполняться ` __f_alias(void)`, иначе атрибут не сработает.

```
void __f_alias(void) {
	// do something
}

void f(void) __attribute__((weak, alias("__f_alias")));
```

### alloc_align
Говорит компилятору то что функция возвращает указательна значение в памяти, выравненное по значению аргумента функции.
`void *mem_align(size_t, size_t) __attribute__((alloc_align(1)))` - выравневание по значению первого аргумента функции.