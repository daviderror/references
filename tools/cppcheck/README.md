+ [about](#about)
+ [install](#install)
+ [uninstall](#uninstall)
+ [check](#check)
+ [misra](#misra)
+ [posix](#posix)

## about
SAT - static analysis tool;

## install
```
sudo apt update
sudo apt install cppcheck
```
или из [git](https://github.com/danmar/cppcheck)
```
unzip cppcheck-master.zip
cd cppcheck-master
make
```
либо git'ом
```
git fork https://github.com/danmar/cppcheck
cd cppcheck
make
```

## uninstall
`sudo apt uninstall cppcheck`

## check
Если файл main.c содержет код:
```
int main()
{
    char a[10];
    a[10] = 0;
    return 0;
}
```
то выполнив 

`gcc main.c` 

никаких ошибок будет не выведенно, но если выполнить

`cppcheck file_name.c`, то появится лог о присваивание в не существующий элемент массива, тем самым избегая UB <-- //to do ссылка.
`cppcheck path_name` - для проверки всех файлов директории.

## misra
`cppcheck --addon=misra file_name.cpp`

## posix
`cppcheck --std=posix file_name.cpp`
