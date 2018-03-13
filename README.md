# simple_shell
* a command line interpreter based off of dash
### Authors
Evan L. Sznol & Sonia Chevli
## Features
### Interactive/Non-interactive Modes
simpleshell can take user commands interactively by invoking the program. 
## Builtins
### Exit
Ctrl+C is disabled in simpleshell. Ctrl+D will terminate the program, as well as the following command:
```
exit [STATUS]
```
### cd
The user may change the working directory by invoking the `cd` builtin. Options include `cd`, `cd ~`, `cd -`, and `cd [PATH_TO_DIRECTORY]`. 
### env
The user may print the current environment by invoking the `env` builtin.
###
