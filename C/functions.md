# functions

[signature](#signature)

[prototype](#prototype)

[pointer](#pointer)

[typedef](#typedef)

## signature

    A function's signature includes the function's name and the number, order 
    and type of its formal parameters. Two overloaded functions must not have 
    the same signature. The return value is not part of a function's signature.

## prototype

    Прототипом функции в языке Си или C++ называется объявление функции, не содержащее 
    тела функции, но указывающее имя функции, арность, типы аргументов и возвращаемый тип 
    данных. В то время как определение функции описывает, что именно делает функция, 
    прототип функции может восприниматься как описание её интерфейса.В прототипе имена 
    аргументов являются необязательными, тем не менее, необходимо указывать тип вместе 
    со всеми модификаторами (например, указатель ли это или константный аргумент).

## pointer

`double (*p_func)(int, char) = NULL;` // указатель на функцию возвращающуу double и принемающею int и char

## typedef

`typedef int (*p_func_t)(float, bool);` // псевдоним типа указателя на функции возвращающею int и принемающею float и bool
