# Music Player
## Windows
**wmplayer** (Available by default) needs to be installed in system to be able to play music, loop is **not** available for windows, project is more focused on **unix-based** systems.
## Unix-based
To be able to play music while playing game, you need `mpg123` installed in your system, but if you don't want it, it is not necessary, you can still play the game.
Also, `Musics` folder need to be at same directory as executable file so program can find it.
### mpg123 Installation Guide

`mpg123` is a fast MP3 player that supports a wide range of platforms.
To install `mpg123`, run:

#### Debian/Ubuntu-based Distributions

```bash
sudo apt update
sudo apt install mpg123
```
#### Red Hat-based Distributions (Fedora, CentOS, RHEL)

```bash
sudo dnf install mpg123
```

```bash
sudo yum install epel-release
sudo yum install mpg123
```
#### Arch-based Distributions (Arch Linux, Manjaro)
```bash
sudo pacman -S mpg123
```
<br><br>
# Log and Error file
### Log File
Log file will be stored in the same directory as the executed program with the name ```log_file.log```, every new game starts and ends with **' *** '**
### Error File
In case you don't hear anything after specifying music name, you can check ```.ErrorFile``` in the same directory as executed program to find out problem.
<br><br>
# Issues
There might some issues happen, (I don't think they will happen). Just in case these are fixes:
## Unicode
In order to be able to see unicode characters, your terminal has to encode text characters to UTF-8
### Linux (Terminal Emulators like GNOME Terminal, Konsole, etc.)
* Open **Preferences** or **Settings**.
* Look for a section labeled **Text**, **Character Encoding**, or **Encoding**.
* Set the encoding to **UTF-8**.

### Windows (PowerShell or Command Prompt)
By default, **Command Prompt (cmd)** does not fully support Unicode. You can switch to **Windows Terminal** or **PowerShell** for better support.

To enable UTF-8 in Command Prompt: 
```cmd
::This will enable UTF-8 only for current session, after you close cmd, it will get back to default
chcp 65001
```
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
