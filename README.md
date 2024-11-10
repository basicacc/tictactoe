# Error File
In case you don't hear anything after specifying music name, you can check .ErrorFile in the same directory as executable file to find out problem.


# Music Player
To be able to play music while playing game, you need `mpg123` installed in your system, but if you don't want it, it is not necessary, you can still play the game.
Also, `Musics` folder need to be at same directory as executable file so program can find it.
## mpg123 Installation Guide

`mpg123` is a fast MP3 player that supports a wide range of platforms.
To install `mpg123`, run:

### Debian/Ubuntu-based Distributions

```bash
sudo apt update
sudo apt install mpg123
```
### Red Hat-based Distributions (Fedora, CentOS, RHEL)

```bash
sudo dnf install mpg123
```

```bash
sudo yum install epel-release
sudo yum install mpg123
```
### Arch-based Distributions (Arch Linux, Manjaro)
```bash
sudo pacman -S mpg123
```
