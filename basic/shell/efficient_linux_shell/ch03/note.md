## Chapter 03 Repeat the history command
* md5sum *.jpg | cut -c1-32 | sort | uniq -c | sort -nr
* md5sum *.jg | cut -c1-32 | sort | uniq -c | sort -nr
### 3.1 View command history
* history (shell builtin)
* history 3
* history | less
* history | sort -nr | less
* history | grep -w cd
* history -c (clear)
### 3.2 Repeat the command in the call history
#### 3.2.1 Navigate through history using arrow keys
* history size (Ubuntu default: 1000, assign via HISTSIZE)
  * echo $HISTSIZE
  * HISTSIZE=-1 # No upper limit
  * HISTCONTROL
    * default unset
    * HISTCONTROL=ignoredups, Deduplication
  * echo $HISTFILE
#### 3.2.2 History Expand
* echo Efficient Linux
* !!
* !grep # Executes again the most recently executed command that begins with a specific string (grep).
* !?grep? # Executes again the most recently executed command that include specific string (grep).
* history | grep hosts (437  history | grep hosts)
* !437
* !-3 # The third last index
* !-3:p # just view command, not execute
* ls -l /etc/ | head -n3
* echo "!!" | wc -w
#### 3.2.3 Avoid deleting the wrong files
* ls
* rm *.txt
* alias rm="rm -i"
  * -i Interactive Confirmation
* rm *.txt
* ls *.txt
* rm !$ # !$ Indicates the last word entered in the previous command.
* head myfile.txt
* rm !$
* ls *.txt *.o *.log
* rm !* # !* Indicates all parameter entered in the previous command.
#### 3.2.4 Incremental search of command history
* press Ctrl-R enter Incremental search mode
* press Esc Ctrl-J or any edit key, leave and continue current command
* press Ctrl-G or Ctrl-C leave and clear terminal
### 3.3 Command line editing
#### 3.3.1 Move cursor within command
* left key : Move left one character
* right key : Move right one character
* Ctrl + left key : Move left one word
* Ctrl + right key : Move right one word
* Home : Move to the beginning of the line
* End : Move to the end of the line
* BackSpace or Delete : delete one character
#### 3.3.2 Caret notation for history expansion
* md5sum *.jg | cut -c1-32 | sort | uniq -c | sort -nr
  * md5sum: '*.jg': No such file or directory
* ^jg^jpg (Replace the wrong part)
  * md5sum *.jpg | cut -c1-32 | sort | uniq -c | sort -nr
  * sed style replace
    * !!:s/jg/jpg/ (Same effect)
    * !md5sum:s/jg/jpg/
#### 3.3.3 Emacs or Vim-style command-line editor
* The shell defaults to Emacs style
* Use set -o vi (can persist to $HOME/.bashrc) change to Vim style
* set -o emacs