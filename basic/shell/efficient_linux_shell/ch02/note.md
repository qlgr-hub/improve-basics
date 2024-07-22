## Chapter 02 Shell Introduction
* ls *.py
  * \* is Wildcards, Wildcards are processed by the shell, not the command itself.
  * In addition, the pipeline is also processed by the shell to achieve redirection, and the command is not aware of it.
### 2.1 The meaning of Shell
### 2.2 Pattern matching for file names
* Find Linux from chapter1~chapter100
  * grep Linux chapter1 chapter2 chapter3 chapter4 chapter5 ...
  * grep Linux chapter*
    * Behind the scenes, the shell expands the pattern "chapter*" into a list, then execute grep
  * grep Linux chapter?
    * ? means any character, so "chapter?" expands into chapter1~chapter9
    * grep Linux chapter?? (chapter10~chapter99)
  * grep Linux chapter[12345] (chapter1~chapter5)
    * grep Linux chapter[1-5] (chapter1~chapter5)
  * grep Linux chapter*[02468] (chapter2, chapter4, chapter6, chapter8)
  * ls [A-Z]\*_\*@
    * Matches, starts with a capital letter, contains an underscore, and ends with @.
* ls -1 /etc/*.conf
* ls (Peoms  Pictures  Politics)
* cd P* (cd: too many arguments)
* ls \*.doc (ls: cannot access '*.doc': No such file or directory)
* <font color=Red>Pattern matching is done by the shell, not the command.</font>
* <font color=Red>The shell's pattern matching applies only to file and directory paths.</font>
* <font color=Red>Some Linux commands, such as grep, sed, and awk, have their own pattern matching mechanisms.</font>
### 2.3 Variable evaluation
* printenv HOME
* printenv USER
* echo My name is $USER and my files are in $HOME.
* echo P*s (Peoms Pictures Politics)
#### 2.3.1 Where do variables come from?
* work=/workspace/efficient_linux_shell/ch02/Projects
* cd $work
* pwd (/workspace/efficient_linux_shell/ch02/Projects)
* touch myfile
* cp myfile $work/
* ls $work
* work = $HOME/Projects (work: command not found)
#### 2.3.2 Variables and the mysterious logic behind them
* echo $HOME
* The shell evaluates variables before executing commands.
#### 2.3.3 Patterns and variables
* move file
  * mv mammals/*.txt reptiles (ok)
    * echo mammals/*.txt (mammals/lizard.txt mammals/snake.txt)
    * mv mammals/lizard.txt mammals/snake.txt reptiles
  * FILES="lizard.txt snake.txt"
    * mv mammals/$FILES reptiles (mv: cannot stat 'snake.txt': No such file or directory)
    * echo mammals/$FILES (mammals/lizard.txt snake.txt)
    * mv mammals/lizard.txt snake.txt reptiles
    * ```
            for f in $FILES; do
                mv mammals/$f reptiles
            done
### 2.4 Simplify commands with aliases
* alias g=grep
* alias ll="ls -l"
* alias less="less -c"
* alias # list all alias settings
* alias g (alias g='grep')
* unalias g
### 2.5 Redirecting input and output
* grep Perl animals.txt
* grep Perl animals.txt > outfile
  * cat outfile
* echo There was just one match >> outfile (append)
* wc animals.txt
* wc < animals.txt
* cp nonexistent.txt file.txt (cp: cannot stat 'nonexistent.txt': No such file or directory)
  * cp nonexistent.txt file.txt > errors
    * cat errors (empty file)
  * cp nonexistent.txt file.txt 2> errors
    * cat errors (ok)
  * cp nonexistent.txt file.txt 2> errors
  * cp another.txt file.txt 2>> errors
    * cat errors (ok)
  * echo This file exists > goodfile.txt
  * cat goodfile.txt nonexistent.txt &> all.output
  * cat all.output
* wc < animals.txt > count
  * cat count
* grep Perl < animals.txt | wc > count
### 2.6 Use quoting and escaping to prevent shell evaluation
* ls file1 file2 file3 # Spaces separate words
* ls -l (If file name includes spaces, e.g.'Efficient Linux Tips.txt')
* cat Efficient Linux Tips.txt (not ok)
  * cat 'Efficient Linux Tips.txt' (ok)
  * cat "Efficient Linux Tips.txt" (ok)
  * cat Efficient\ Linux\ Tips.txt (ok)
* echo '$HOME' (\$HOME)
* echo "Notice that $HOME is evaluated"
* echo 'Notice that $HOME is not'
* echo \$HOME (\$HOME)
* echo "The value of \$HOME is $HOME" (ok)
* echo 'The value of \$HOME is $HOME' (not ok)
* echo "This message is \"sort of\" interesting"
* echo "This is a very long message that needs to extend \
  * onto multiple lines"
* cut -f1 grades \
  * | sort \
  * | uniq -c \
  * | sort -nr \
  * | head -n1 \
  * | cut -c9
* \ can be used as a line continuation character
* alias less="less -c"
* less myfile  # use alias
* \less myfile # use original command
### 2.7 Find program
* ls -l /bin/ls
* echo $PATH
* echo $PATH | tr : "\n"
* which cp
* which which
* type cp
  * type is shell builtin
  * can find
    * executable
    * alias
    * function
    * builtin
### 2.8 Environment and initialization files
* ls $HOME
* ls -a $HOME
* .bashrc
  * source $HOME/.bashrc
  * . $HOME/.bashrc