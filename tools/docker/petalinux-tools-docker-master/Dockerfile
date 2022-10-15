FROM  ubuntu:16.04
LABEL maintainer="sae"

ARG petalinux_installer=./petalinux-v2019.1-final-installer.run
ARG install_dir=/opt/tmp_pet/petalinux
ARG home_dir=/home/artyom
ARG PETALINUX_VER=2019.1
ARG PETALINUX=${install_dir}

RUN dpkg --add-architecture i386 && \
    apt-get update && apt-get install -y --no-install-recommends \
    python3             \
    tofrodos            \
    iproute2            \
    gawk                \
    xvfb                \
    git                 \
    make                \
    net-tools           \
    libncurses5-dev     \
    lib32z1             \
    libssl-dev          \
    flex                \
    bison               \
    libselinux1         \
    gnupg               \
    wget                \
    diffstat            \
    chrpath             \
    socat               \
    xterm               \
    autoconf            \
    libtool             \
    tar                 \
    unzip               \
    texinfo             \
    zlib1g-dev          \
    gcc-multilib        \
    build-essential     \
    libsdl1.2-dev       \
    libglib2.0-dev      \
    libsdl-dev          \
    glib2.0             \
    automake            \
    screen              \
    pax                 \
    gzip                \
    libtool-bin         \
    locales             \
    cpio                \
    apt-utils           \
    rsync               \
    x11-utils           \
    lsb-release         \
    zlib1g:i386         \
    default-jre         \
# Using expect to install Petalinux automatically.
    expect              \
    sudo                \
    git-gui             \
    vim                 \
    bc

# add user information
RUN mkdir -p $home_dir && \
    echo "developer:x:1000:1000:Developer,,,:${home_dir}:/bin/bash" >> /etc/passwd && \
    echo "developer:x:1000:" >> /etc/group && \
    echo "developer ALL=(ALL) NOPASSWD: ALL" > /etc/sudoers.d/developer && \
    chmod 0440 /etc/sudoers.d/developer && \
    chown developer:developer -R $home_dir

# add install dir
RUN mkdir -p $install_dir && \
    chown developer:developer -R $install_dir

# add internal docker commands
RUN mkdir /opt/internal_cmd_docker && \
    chown developer:developer -R /opt/internal_cmd_docker

# add locale en_US.UTF-8 required by petalinux
RUN locale-gen en_US.UTF-8

USER developer

# Install Petalinux tools
WORKDIR $home_dir
COPY ./auto-install.sh .
COPY ./tools/internal_cmd_docker/* /opt/internal_cmd_docker/

COPY $petalinux_installer .
RUN ./auto-install.sh $petalinux_installer $install_dir && \
    rm -rf $petalinux_installer auto-install.sh

RUN echo 'echo "PetaLinux SDK"' >> ~/.bashrc

# Create alias for the petalinux commands
RUN echo 'alias plbuild="petalinux-build"' >> ~/.bashrc      && \
    echo 'alias plcreate="petalinux-create"' >> ~/.bashrc    && \
    echo 'alias plconfig="petalinux-config"' >> ~/.bashrc

# Setup python3 as default python (required by petalinux)
RUN echo 'alias python=python3' >> ~/.bashrc

# Set locale conf required by petalinux
RUN echo 'export LANG=en_US.UTF-8' >> ~/.bashrc

# Export path with SDK
RUN echo 'export PATH='$PETALINUX'/tools/hsm/bin:${PATH}' >> ~/.bashrc
RUN echo 'export PETALINUX_VER='$PETALINUX_VER >> ~/.bashrc

# Setup Petalinux environment
RUN echo '. '${PETALINUX}'/settings.sh' >> ~/.bashrc

RUN sudo ln -fs /bin/bash /bin/sh    # bash is PetaLinux recommended shell

RUN sudo ln -fs /usr/lib/x86_64-linux-gnu/libpcre16.so.3 /usr/lib/x86_64-linux-gnu/libpcre16.so.0 # neded by QT5 uuic ...

# Copy petalinux config also for root... to use SDK 
RUN sudo cp ~/.bashrc /root/

#WORKDIR /workspace

