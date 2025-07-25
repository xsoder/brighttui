# BRIGHTTUI: X11 Only TUI application

A brightness terminal application implemented for x11.
> ![WARNING]
> This is still under development.

## Dependency

The packages required to build it are ncurses and libXrandr.

To install these packages. Visit your package manager.

## Debian based distro

``` bash
    $ sudo apt install libncurses-dev libxrandr-dev
```

## Arch based distro 

``` bash
    $ sudo pacman -S ncurses libXrandr
```

## How to build

Simply run the make file.

``` bash
    $ make
```

For faster compilation run the following command.

``` bash
    $ make -j$(nproc)
```
