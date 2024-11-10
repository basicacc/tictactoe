# Error File
In case you don't hear anything after specifying music name, you can check .ErrorFile in the same directory as executable file to find out problem.
<br><br>

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
<br><br>
# Issues
There might some issues happen, (I don't think they will happen). Just in case these are fixes:
## mpg123
You might experience issue with mpg123 non-stop playing in loop even after exiting program, to kill process run:
```bash
killall mpg123 #if you started program with sudo priviliges, you might need sudo permission for this command too.
```
or
```bash
ps aux | grep 'mpg123'
kill -9 <PID>
```