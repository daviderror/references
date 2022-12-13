# python

## plan
+ lectures https://www.youtube.com/watch?v=XKHEtdqhLK8
+ target
+ pet project

## install anakonda

https://www.anaconda.com/products/distribution/download-success-pythonanywhere

`bash Anaconda3-2022.05-Linux-x86_64.sh`


## variables

### str
``` 
var = "it's string"
print(type(var))
print(var)

var_1 = "added string"
print(var + var_1)

print(var + " " + var_1)
```

```
print(len(var))
print(var.find("i"))
print(var.upper())
print(var * 3)
```

### int
```
var = 21
print(type(var))
print(var)

var += 1
print(var)

print(var + 1)
```

### float
```
var = 250.5
print(type(var))
print(var)
```

### bool
```
var = False
print(type(var))
print(var)
```

### multiple assignment
```
name, age, attractive = "Bro", 21, True
spongebob = patrick, sandy, squidward = 30
```

### type casting
```
x = 1
y = 2.1
z = "3"

print(x)
print(y)
print(z)

print(x + int(y))
print(y + float(z))
print(z + " " + str(y))
```

## input
```
name = input("what is your name?\n")
print("hello " + name)

age = int(input("How old are you?\n"))
print("You are " + str(age))

height = float(input("What is your height?\n"))
print("Your height is " + str(height))
```