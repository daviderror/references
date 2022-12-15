# python

## plan
+ lectures https://www.youtube.com/watch?v=XKHEtdqhLK8
+ 1000 exercise
+ algorithms
+ target
+ pet project

## install anakonda

https://www.anaconda.com/products/distribution/download-success-pythonanywhere

`bash Anaconda3-2022.05-Linux-x86_64.sh`


## variables

### str
``` 
var = "it's string"
print(type(var))           # -> <class 'str'>
print(var)                  # -> it's string

var_1 = "added string"
print(var + var_1)          # -> it's stringadded string

print(var + " " + var_1)    # -> it's string added string
```

```
print(len(var))         # -> 11
print(var.find("t"))    # -> 1
print(var.upper())      # -> IT'S STRING
print(var * 3)          # -> it's stringit's stringit's string
```

```
# [start:stop:step] by default step == 1

str = "Art Code"
first_part = str[0:2]
print(first_part)        # -> Art

first_part = str[:4]
print(first_part)        # -> Art C

second_part = str[4:8]
print(second_part)       # -> Code

second_part = str[2:]
print(second_part)       # -> o Code

second_part = str[0:-1:1]
print(second_part)        # -> Art Cod

fynky_part = str[0:8:2]
print(fynky_part)        # -> AtCd

fynky_part = str[::2]
print(fynky_part)        # -> AtCd

reversed_str = str[::-1]
print(reversed_str)      # -> edoC trA
```
```
# [start:stop:step] by default step == 1

website = "http://google.com"
slice_website = slice(7,-4)
print(website[slice_website])    # -> google

```
```
animal = "cow"
item = " moon"
print("the {} jumped over the {}".format(animal, item))   # -> the cow jumped over the moon
print("the {0} jumped over the {1}".format(animal, item)) # -> the cow jumped over the moon
print("the {1} jumped over the {0}".format(animal, item)) # -> the moon jumped over the cow

print("the {first_arg} jumped over the {second_arg}".format(first_arg = "cow", second_arg = "moon")) # -> the cow jumped over the moon

text = "the {} jumped over the {}"
print(text.format(animal, item))                 # -> the cow jumped over the moon

name = "artem"
print("Hello, my name is {}.".format(name))       # -> Hello, my name is artem.
print("Hello, my name is {:10}.".format(name))    # -> Hello, my name is artem     .
print("Hello, my name is {:>10}.".format(name))   # -> Hello, my name is artem     .
print("Hello, my name is {:<10}.".format(name))   # -> Hello, my name is      artem.
print("Hello, my name is {:^10}.".format(name))   # -> Hello, my name is    artem  .

number = 3.14159
print("The number pi is {:.3f}".format(number))   # -> 3.141

number_2 = 1000
print("The number pi is {:.3f}".format(number))   # -> 1000.000
print("The number pi is {:,}".format(number))     # -> 1,000
print("The number pi is {:b}".format(number))     # -> 1111101000
print("The number pi is {:o}".format(number))     # -> 1750
print("The number pi is {:X}".format(number))     # -> 3E8
print("The number pi is {:E}".format(number))     # -> 1.000000E+03
```

### int
```
var = 21
print(type(var))    # -> <class 'int'>
print(var)

var += 1
print(var)          # -> 22

print(var + 1)      # -> 23
```

### float
```
var = 250.5
print(type(var))    # -> <class 'float'>
print(var)          # -> 250.5
```

### bool
```
var = False
print(type(var))    # -> <class 'bool'>
print(var)          # -> False
```

### multiple assignment
```
name, age, attractive = "Art", 21, True
spongebob = patrick, sandy, squidward = 30
```

### type casting
```
x = 1
y = 2.1
z = "3"

print(x)                   # -> 1
print(y)                   # -> 2.1
print(z)                   # -> 3

print(x + int(y))          # -> 3
print(y + float(z))        # -> 5.1
print(z + " " + str(y))    # -> 3 2.1
```

## input
```
name = input("what is your name?\n")               # <- Artem
print("hello " + name)                             # -> hello Artem

age = int(input("How old are you?\n"))             # <- 34
print("You are " + str(age))                       # -> You are 34

height = float(input("What is your height?\n"))    # <- 178,2
print("Your height is " + str(height))             # -> Your height is 178,2
```

## import
```
import math

pi = 3.14
print(round(pi))        # -> 3
print(math.ceil(pi))    # -> 4
print(math.floor(pi))   # -> 3
print(pow(pi,2))        # -> 9,8596
print(matn.sqrt(25))    # -> 5

pi = -3.14
print(abs(pi))          # -> 3.14

x, y, z = 1, 2, 3
print(max(x, y, z))     # -> 3
print(min(x, y, z))     # -> 1
```

## if
```
if age_var >= 18:
	print("You are an adult!")
elif age_var == 110:
	print("You are acenture old!")
elif age_var < 0:
	print("You haven't been born yet!")
else:
	print("You are a child!")
```
```
if temp_var >= 0 and temp_var <= 30:
	print("the temperature is good today!")
	ptint("go outside!")
elif temp_var < 0 or temp_var > 30:
	c
	ptint("stay inside!")
```

## loops
```
while 1 == 1:    # infinite loop
	print("I am in in a infinite loop")
```
```
while len(name) == 0:
	name = input("Enter your name: ")
```
```
name = None

while not name:
	name = input("Enter your name: ")
```
```
for i in range(10):
	print(i)
```
```
for i in range(50,100):
	print(i)              # -> 50 51 52...
```
```
for i in range(50,100,2):
	print(i)                # -> 50 52 54...
```
```
for i in range(50,0,-1):
	print(i)                # -> 50 49 48...
```
```
for i in "Hello":
	print(i)                # -> H e l l o
```
### nested loop
```
for i in range(10):
	for j in range(10):
		print("@")
	print()
```
### break
```
while True:
	name = input("Enter your name: ")
	if name != ""
	    break
```
### continue
```
phone_number = "123-456-789"

for i in phone_number:
	if i == "-":
	    continue
	print(i, end = "")
```
### pass
```
for i in range(1,21):
	if i == 13:
		pass
	else
		print(i)
	
```

## list

Used to store multiple items in a single variable

### 1D list
```
food = ["pizza", "hamburgers", "hotdog", "spaghetti"]
print(food[0])    # -> pizza
print(food[1])    # -> hamburgers
print(food[2])    # -> hotdog
print(food[3])    # -> spaghetti

food[2] = "sushi"
print(food[0])    # -> sushi

food.append("ice cream")
food.remove("hotdog")
food.pop()       # removes the last element
food.insert(0, "cake")
food.sort()
food.clear()     # removes all elements of a list
```

### 2D list
```
drinks = ["coffee", "soda", "tea"]
dinner = ["pizza", "hamburgers", "hotdog"]
dessert = ["cake", "ice cream"]

food = [drinks, dinner, dessert]

print(food)        # -> [["coffee", "soda", "tea"],["pizza", "hamburgers", "hotdog"], ["cake", "ice cream"]]

print(food[0])     # -> ["coffee", "soda", "tea"]
print(food[0][0])  # -> coffee
```

## tuple
Collection which is ordered and unchangeable used to group together related data.

```
student = ("Art", 21, "male")

print(student.count("Art"))    # -> 1
print(student.index("male"))   # -> 2

for i in student:              # Art 21 male
    print(x)

if "Art" in student:
	print("Art is here!")
```

## set
Collection which is unordered, unindexed. No duplicate values.

```
utensils = {"fork","spoon","knife"}

for x in utensils:   # -> knife fork spoon
    print(x)

for x in utensils:   # -> fork knife spoon
	print(x)

utensils.add("napkin")
utensils.remove("fork")
utensils.clear()

dishes = {"bowl", "plate", "cup"}

utensils.update(dishes)  # adds all element of dishes to utensils

tabs = utensils.union(dishes)

print(utensils.difference(dishes))
```

## dictionary
A changeable, unordered collection of unique key: value pairs.
It is fast becaus hashed.

```
capitals = {'USA':'Washington DC',
'India':'New Dehli',
'China':'Beijing',
'Russia':'Moscow'}

print(capitals['Russia'])         # -> Moscow
print(capitals.get('Germany'))    # -> None
print(capitals.keys())            # -> USA, India, China, Russia
print(capitals.values())
print(capitals.items())

for key, values in capitals.items():
	print(key, value)

capitals.update({'Germany':'Berlin'})
capitals.update({'USA','Las Vegas'})
capitals.pop('China')
capitals.clear()
```

##  index_operator
Index operator [] gives access to a sequence's element (str, list, tuples)

```
name = "art Code!"

if (name[0].islower()):
	name = name.capitalize()

print(name)

first_name = name[0:3].upper()
first_name = name[:3].upper()
last_name = name[4:].lower()
last_character = name[-1]

print(first_name)        # -> ART
print(last_name)         # -> code
print(last_character)    # -> !

last_character = name[-2]
print(last_character)    # -> e
```

## functions

A block of code which is executed only when it is called.

```
def hello():
	print("hello!")
	print("Have a nice day!")

hello()
```

### arguments
```
def hello(name)
	print("hello " + name)
	print("Have a nice day!")

hello("Bude")

my_name = "Artem"
hello(my_name)
```
```
def hello(first_name, last_name)
	print("hello " + first_name + " " + last_name)
	print("Have a nice day!")

my_name = "Artem"
hello("Bude", my_name)
```
```
def hello(first_name, last_name, age)
	print("hello " + first_name + " " + last_name)
	print("You are" + str(age))

my_name = "Artem"
hello("Bude", my_name, 34)
```

### keyword arguments
```
def hello(first_name, last_name, age)
	print("hello " + first_name + " " + last_name)
	print("You are" + str(age))

my_name = "Artem"
hello(age = 34, last_name = my_name, first_name = "Bude")
```

### \*args
Parameters that will pack all arguments into a tuple useful so that a function can accept a varying amount of arguments.

    args - just name, there is \* crusial.

```
def hello(*args)   # args just name
	print("hello " + args[0] + " " + args[1])
	print("You are" + str(args[2]))

my_name = "Artem"
hello("Bude", my_name, 34)

```
```
def hello(*args)   # args just name
	for i in args
	    print("hello " + i)

my_name = "Artem"
hello("Bude", my_name, "34")

```

### \*\*kwargs
Parameters that will pack all arguments into a dictionary useful so that a function can accept a varying amount of arguments.

    kwargs - just name, there is \*\* crusial.

```
def hello(**kwargs)   # kwargs just name
	print("hello " + kwargs['first'] + " " + kwargs['midle'])
	print("You are" + kwargs['age'])

my_name = "Artem"
hello(first = "Bude", midle = my_name, age = "34")
```
```
def hello(**kwargs)   # kwargs just name
	for key, value in kwargs.items():
	    print(value)

my_name = "Artem"
hello(first = "Bude", midle = my_name, age = "34")
```

### return statement
```
def multiply(number_1, number_2):
	result = number_1 * number_2
	return result

print(multiply(6,8))   # -> 48

x = multiply(5,7)
print(x)               # -> 35

```

### nested functions calls
Functions calls inside other function calls.
```
print(round(abs(float(input("Enter a whole positive namber: ")))))
```

## scope
The region that a variable is recognized. A variable is only available from inside the region it is created. A global and locally scoped version of a variable can be created.

## random
```
import random

x = random.randint(1,6)
y = random.random()

my_list = ['rock', 'paper', 'scissors']
z = random.choice(my_list)

random.shuffle(my_list)
print(my_list)
```

## exception
Event detected during execution that interrupt the flow of program.


Error will occure if denominator will be equelent 0
```
numerator = int(input("Enter a number to divide"))
denominator = int(input("Enter a number to divide by"))
result = numerator / denominator
print(result)
```

An exception vertion
```
try:
    numerator = int(input("Enter a number to divide"))
    denominator = int(input("Enter a number to divide by"))
    result = numerator / denominator
    print(result)
except ZeroDivisionError:
    print("you can't divide by zero.")
except ValueError:
    print("Enter only numbers please.")
except Exception:
    print("something went wrong.")
else:
    print(result)
finally:  # Optional
    print("This will always execute")
```

## file
### file detection
```
import os

path = "/home/file_dir/file.txt"

if os.path.exists(path):
	print("Exist")

	if cfile(path):
		print("it's a file")
	elif os.path.isdir(path)
		print("it's a direction)
else:
	print("doesn't exist")
```

### file reading
```
import os

path = "/home/file_dir/file.txt"

with open('path') as file:  # the file will be automaticly closed
	print(file.read())

print(file.closed())        # -> True
```

### file writing
```
import os

path = "/home/file_dir/file.txt"
text = "Yoooooo\nThis is some text\n"

with open('path', 'w') as file:  # write (rewrite) file
	file.write(text)

with open('path', 'a') as file:  # add text to file
	file.write(text)
```

### file coping
```
import shutil

src_path = "/home/file_dir/file.txt"
dst_path = "/home/file_dir/file_2.txt"
dst_copy_path = "/home/file_dir/file_3.txt"
dst_copy2_path = "/home/file_dir/file_4.txt"

shutil.copyfile(src_path, dst_path)
shutil.copy(src_path, dst_copy_path)
shutil.copy2(src_path, dst_copy2_path)
```

### file moving
```
import os

src_path = "/home/file_dir/file.txt"
dst_path = "/home/file_dir/dst/file.txt"

try:
	if os.path.exist(dst_path):
		print("Ther is already a file there")
	else:
		os.replace(src_path, dst_path)
		print(src_path + " was moved")
except FileNotFoundError:
	print(src_path + " was not found")
```

### file removing
```
import os
import shutil

path = "/home/file_dir/file.txt"

try:
	os.remove(path)
except FileNotFoundError:
	print(src_path + " was not found")
exccept PermissionError:
	print("you haven't permissions")
exccept OSerror:
	print("you cannot delete that using that function")
else:
    print(path + " was removed")
```
```
import os

path = "/home/file_dir"

try:
	os.rmdir(path)
except FileNotFoundError:
	print(src_path + " was not found")
exccept PermissionError:
	print("you haven't permissions")
exccept OSerror:
	print("you cannot delete that using that function")
else:
    print(path + " was removed")
```
```
import shutil

path = "/home/file_dir"

try:
	shutil.rmtree(path)
except FileNotFoundError:
	print(src_path + " was not found")
exccept PermissionError:
	print("you haven't permissions")
exccept OSerror:
	print("you cannot delete that using that function")
else:
    print(path + " was removed")
```

## modules
A file containing pythin code.

```
import my_module

my_module.some_foo_1()
my_module.some_foo_2()
```
```
import my_module as mml

mml.some_foo_1()
mml.some_foo_2()
```
```
from my_module import some_foo_1 some_foo_1, some_foo_2

some_foo_1()
some_foo_2()
```
```
from my_module import *

some_foo_1()
some_foo_2()
```