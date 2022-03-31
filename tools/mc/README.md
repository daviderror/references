# mc

1.  [installing](#installing)
2.  [launch](#launch)
3.  [settings](#settings)
4.  [ssh](#ssh)
5.  [removing](#removing)

## installing 
```
sudo apt-get update
sudo apt -y install mc
```

## launch
```
mc
```

## settings
   Full set ini is in.

1. Skin
    Gui case: Options -> Appearance -> Skin

    File case:
    ~/.config/mc/ini (if the ini fike is absent, create it ~~~subl ini)
    ini <- skin=[<darkfar> <default> <dark> <gotar> <and etc>]

## ssh
    In the Option bar:

1. FTP (via ssh)
    1.1. Left/Right -> FTP link <- user@ip_address <- password
    1.2. Left/Right -> FTP link <- user:password@ip_address
2. Shell (via ssh)
    Left/Right -> shell link <- sh://user@ip_address <- password

## removing
    To remove the mc following and the mc package along with its dependencies aftrer that
```
sudo apt-get remove  mc
sudo apt-get remove --auto-remove mc
```