## Chapter 06 Parent, child and Environment
### 6.1 shell is the executable
* cd /bin
* ls -l bash cat ls grep
* cat /etc/shells
* echo $SHELL
* Simulated shell program
  * halshell
* child shell
  * bash
  * PS1="%% "
  * exit
### 6.2 Parent-child process
* chmod +x cdtest
* pwd
* ./cdtest
* pwd
* cd is shell builtin, The pwd of the parent and child shells are independent of each other, so if cd is an external program, path switching in the shell cannot be achieved.
* cut -f1 grades | sort | uniq -c | sort -nr | head -n1 | cut -c9
### 6.3 Environment variables
* echo $HOME
* echo $PWD
* echo $EDITOR
* printenv HOME # same as echo $HOME
* printenv | sort -i | less
* title="Efficient Linux"
* echo $title
* printenv title
#### 6.3.1 Define environment variable
* MY_VARIABLE=10
* export MY_VARIABLE
* export ANOTHER_VARIABLE=20
* export E="I am an environment variable"
* L="I am just a local variable"
* echo $E
* echo $L
* bash
* echo $E
* echo $L
* exit
* export E="I am the original value"
* echo $E
* bash
* echo $E # duplicate
* E="I was modified in a child"
* echo $E
* exit
* echo $E
* The environment variables of the parent process are copied to the child process by value.
#### 6.3.2 Beware of "global" variables
* Environment variables are not global variables.
* Starting with export means this var is copyable
### 6.4 Child shell and subshell
* child shell
  * copy environment variables
  * Local variables and aliases are not copied
  * alias
  * bash --norc # new bash shell and ignore .bashrc
  * alias
  * echo $HOME
  * exit
* subshell
  * Completely copy the parent shell
  * (ls -l)
  * echo $BASH_SUBSHELL
  * bash
  * echo $BASH_SUBSHELL
  * exit
  * (echo $BASH_SUBSHELL)
### 6.5 Configure environment
* Startup files
  * /etc/profile
  * $HOME/.bash_profile
  * $HOME/.bash_login
  * $HOME/.profile # Generic, not just bash
  * $HOME/.bashrc
* Initialization files
  * /etc/bash.bashrc
    * Set via BASH_ENV=/usr/local/etc/bashrc
  * $HOME/.bashrc
    * Set via BASH_ENV=/usr/local/etc/bashrc
* Clean up files
  * /etc/bash.bash_logout
  * $HOME/.bash_logout
#### 6.5.1 Re-read the configuration file
* source ~/.bash_profile
* . ~/.bash_profile
#### 6.5.2 Get configuration files uniformly
* Using Source Code Management Tools
  * git
  * svn
  * ...