# asm

## cpulator

`https://cpulator.01xz.net/`

## registers

| register | description      |
| :---     | :---             |
| r0       |                  |
| r1       |                  |
| r2       |                  |
| r3       |                  |
| r4       |                  |
| r5       |                  |
| r6       |                  |
| r7       | system calls     |
| r8       |                  |
| r9       |                  |
| r10      |                  |
| r11      |                  |
| r12      |                  |
| sp       | stack pointer    |
| lr       |                  |
| pc       | programm counter |
| cpsr     |                  |
| sppsr    |                  |
|          |                  |

## main

```
.global _start
_start:
```

## instruction

### mov

Перемещает знаяения регистров процессора между собой.

Synctax: `mov reg_dest,reg_src`

```
mov r0, #30
mov r1, r0
```

### ldr

Загружает значения из стэка в регистр процессора.

Synctax: `ldr reg_dest,mem_data`

```
ldr r0, =list     // ссылка на list
ldr r1, [r0]      // загрузить в r1 значение из r0
ldr r2, [r0, #4]   // загрузить в r2 значение со смещением 4 байта относительно r0
ldr r3, [r0, #4]!  // предварительное приращение адреса в стэке
ldr r4, [r0], #4   // посфиксное приращение адреса в стэке, те подготовка следующего адреса для следующей инструкции
ldr r5, [r0]

.data
list:
    .word 4,5,-9,1,0,2,-3
```