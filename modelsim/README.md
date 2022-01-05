# modelsim

1.  [downloading](#downloading)
2.  [installing](#installing)
3.  [launching](#launching)
4.  [issue_1](#issue_1)
5.  [issue_2](#issue_2)
6.  [issue_3](#issue_3)
7.  [issue_4](#issue_4)
8.  [issue_5](#issue_5)

## downloading
Download the modelsim 18.1 lite from the Intel as an individual file: https://fpgasoftware.intel.com/?product=modelsim_ae#tabs-2

## installing
    sudo dpkg --add-architecture i386
    sudo apt-get update
    sudo apt-get install libc6:i386 libncurses5:i386 libstdc++6:i386 lib32ncurses5 libxft2 libxft2:i386 lib32ncurses5 libxext6 libxext6:i386

    chmod +x ModelSimProSetup-18.1.0.222-linux.run
    ./ModelSimProSetup-18.1.0.222-linux.run

    PATH=$PATH:/opt/modelsim_ase/bin

## launching
    vsim

or

    cd /opt/modelsim_ase/bin/
    ./vsim

## issue_1

referance: https://gist.github.com/Razer6/cafc172b5cffae189b4ecda06cf6c64f

aka: could not find ./../linux_rh60/vsim

    sudo subl modelsim_dir/modelsim_ase/bin/vsim

    mode=${MTI_VCO_MODE}
        |
        V
    mode=${MTI_VCO_MODE:-"32"}

    *)                vco="linux_rh60" ;; 
        |
        V 
    *)                vco="linux" ;;

## issue_2

referance: https://gist.github.com/Razer6/cafc172b5cffae189b4ecda06cf6c64f

version 1 aka:
    
    Error in startup script: 
    Initialization problem, exiting.
     
    Initialization problem, exiting.
     
    while executing
    "InitializeINIFile quietly"
    invoked from within
    "ncFyP12 -+"
        (file "/mtitcl/vsim/vsim" line 1)
    ** Fatal: Read failure in vlm process (0,0)

    download freetype-2.11.0

freetype-2.11.0: https://ftp.osuosl.org/pub/blfs/conglomeration/freetype/

    sudo apt-get build-dep -a i386 libfreetype6
    sudo dpkg --add-architecture i386
    sudo apt-get update
    sudo apt-get install build-essential
    sudo apt-get install gcc-multilib g++-multilib
    sudo apt-get install lib32z1 lib32stdc++6 lib32gcc1
    sudo apt-get install expat:i386 fontconfig:i386 libfreetype6:i386 libexpat1:i386 libc6:i386 libgtk-3-0:i386
    sudo apt-get install libcanberra0:i386 libpng12-0:i386 libice6:i386 libsm6:i386 libncurses5:i386 zlib1g:i386
    sudo apt-get install libx11-6:i386 libxau6:i386 libxdmcp6:i386 libxext6:i386 libxft2:i386 libxrender1:i386
    sudo apt-get install libxt6:i386 libxtst6:i386

    cd ~/Downloads/
    cd freetype-2.11.0
    ./configure --build=i686-pc-linux-gnu "CFLAGS=-m32" "CXXFLAGS=-m32" "LDFLAGS=-m32"
    make -j8

    mkdir /modelsim_dir/modelsim_ase/lib32
    sudo cp ~/Downloads/freetype-2.11.00/objs/.libs/libfreetype.so* /modelsim_dir/modelsim_ase/lib32

    sudo subl /modelsim_dir/modelsim_ase/bin/vsim
    dir=`dirname "$arg0"`
    LD_LIBRARY_PATH=${dir}/lib32

There are the version 2 and continue in the issue_3 for this error.

## issue_3

version 2 aka:
    
    Error in startup script: 
    Initialization problem, exiting.
     
    Initialization problem, exiting.
     
    while executing
    "InitializeINIFile quietly"
    invoked from within
    "ncFyP12 -+"
        (file "/mtitcl/vsim/vsim" line 1)
    ** Fatal: Read failure in vlm process (0,0)

After the issue_2 download and install the Modelsim/Questa compatible libraries

    sudo wget http://security.ubuntu.com/ubuntu/pool/main/libp/libpng/libpng12-0_1.2.54-1ubuntu1.1_amd64.deb
    sudo wget http://security.ubuntu.com/ubuntu/pool/main/libp/libpng/libpng12-0_1.2.54-1ubuntu1.1_i386.deb
    sudo wget http://archive.ubuntu.com/ubuntu/pool/main/f/freetype/libfreetype6_2.6.1-0.1ubuntu2_i386.deb
    sudo wget http://archive.ubuntu.com/ubuntu/pool/main/f/freetype/libfreetype6_2.6.1-0.1ubuntu2_amd64.deb

    sudo dpkg -i libpng12-0_1.2.54-1ubuntu1.1_i386.deb
    sudo dpkg -i libpng12-0_1.2.54-1ubuntu1.1_amd64.deb
    sudo dpkg -i libfreetype6_2.6.1-0.1ubuntu2_i386.deb
    sudo dpkg -i libfreetype6_2.6.1-0.1ubuntu2_amd64.deb

There is the version 1 in the issue_5 for this error.

## issue_4

aka: libXft.so.2: cannot open shared object file

    sudo  apt-get install libxft2 libxft2:i386 lib32ncurses5

## issue_5

aka: libXext.so.6: cannot open shared object file. libXext.so.6 not found

    sudo apt install libxext6
    sudo apt install libxext6:i386

