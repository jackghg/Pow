# Pow
Minimal window switcher that uses wmctrl, wrote in c++ and fltk.
## Options:
-s   font size  
-m	side margin from screen  
-t	top margin  
-b	your titlebar height  
-?  help
## Install
Requires wmctrl and fltk.  
On Arch:  
`sudo pacman -S fltk wmctrl`  
To build and install use:  
`sudo make build clean install`  
To uninstall:  
`sudo make uninstall`  
