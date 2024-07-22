## Chapter 07 11 ways to run commands
* grep Nutshell animals.txt
* cut -f1 grades | sort | uniq -c | sort -nr
### 7.1 List skills
#### 7.1.1 Conditional lists
* cd dir
* touch new.txt
* cd dir && touch new.txt
* cp myfile.txt myfile.safe
* nano myfile.txt
* rm myfile.safe
* cp myfile.txt myfile.safe && nano myfile.txt && rm myfile.safe
* git add . && git commit -m"fixed a bug" && git push
* cd dir || mkdir dir
* cd dir || exit 1
* cd dir || mkdir dir && cd dir || echo "I failed"
* ls myfile.txt
* echo \$? # \$? means last executed command return value
#### 7.1.2 Unconditional lists
* sleep 7200; cp -a ~/important-files /mnt/backup_drive
* sleep 300; echo "remember to walk the dog" | mail -s reminder $USER
### 7.2 Substitution skills
#### 7.2.1 Command substitution
* grep -l "Artist: Kansas" *.txt
* mkdir kansas
* mv carry_on_wayward_son.txt kansas/
* mv dust_in_the_wind.txt kansas/
* mv belexes.txt kansas/
* mv kansas/* ./
* mv $(grep -l "Artist: Kansas" *.txt) kansas
* cd bank-statements/
* ls eStmt*pdf | tail -n1
* okular $(ls eStmt*pdf | tail -n1)
* echo Today is $(date +%A)
* echo Today is \`date +%A\`
* cd ../kansas
* KansasFiles=$(grep -l "Artist: Kansas" *.txt)
* echo $KansasFiles
#### 7.2.2 Process substitution
* mkdir /tmp/jpegs && cd /tmp/jpegs
* touch {1..1000}.jpg
* rm 4.jpg 981.jpg
* ls -1 | sort | less
* ls *.jpg | sort -n > /tmp/original-list
* seq 1 1000 | sed 's/$/.jpg/' > /tmp/full-list
* diff /tmp/original-list /tmp/full-list
* rm /tmp/original-list /tmp/full-list
* <(ls -1 | sort -n)
* cat <(ls -1 | sort -n)
* cp <(ls -1 | sort -n) /tmp/listing
* cat /tmp/listing
* ls *.jpg | sort -n
* seq 1 1000 | sed 's/$/.jpg/'
* diff <(ls *.jpg | sort -n) <(seq 1 1000 | sed 's/$/.jpg/')
* diff <(ls *.jpg | sort -n) <(seq 1 1000 | sed 's/$/.jpg/') | grep '>' | cut -c3-
* echo <(ls)
* Process substitution is Non-POSIX features
  * Need set +o posix to enable
* \<(xxx) # create a readable tmp fd
* \>(xxx) # create a writeable tmp fd
### 7.3 Command as string skills
#### 7.3.1 Command passed as string to bash
* bash -c "ls -l"
* pwd
* touch /tmp/badfile
* bash -c "cd /tmp && rm badfile"
* pwd
* sudo echo "New log file" > /var/log/custom.log (bash: /var/log/custom.log: Permission denied)
  * sudo cannot handle io redirection
* sudo bash -c 'echo "New log file" > /var/log/custom.log'
#### 7.3.2 Passing commands to bash with pipe
* echo "ls -l"
* echo "ls -l" | bash
* cd ./test/
* ls -1 ??*
* mkdir {a..z}
* ^\(.\)
* \(.*\)$
* ^\(.\)\(.*\)$
* mv \1\2 \1
* ls -1 ??* | sed 's/^\(.\)\(.*\)$/mv \1\2 \1/'
* ls -1 ??* | sed 's/^\(.\)\(.*\)$/mv \1\2 \1/' | less
* ls -1 ??* | sed 's/^\(.\)\(.*\)$/mv \1\2 \1/' | bash
#### 7.3.3 Remotely execute strings using ssh
* ssh myhost.example.com
* ssh myhost.example.com ls
* ssh myhost.example.com ls > outfile # on local host
* ssh myhost.example.com "ls > outfile" # on remote host
* echo "ls > outfile" | ssh myhost.example.com
* echo "ls > outfile" | ssh -T myhost.example.com
  * -T No pseudo-terminal will be allocated
* echo "ls > outfile" | ssh myhost.example.com bash
#### 7.3.4 Running a set of commands via xargs
* xargs
  * stdin: input string
  * command line: command template
* cd xargs_demo/example1
* ls -1
* ls -1 | xargs wc -l
* ls -1 | xargs cat
* wc -l *
* cd ../example2
* find . -type f -name \*.py -print
* find . -type f -name \*.py -print0 | xargs -0 wc -l
* xargs
  * -n argument count each command
  * -I specify replacement placeholders
* cd ../example3
* ls | xargs echo
* ls | xargs -n1 echo
* ls | xargs -n2 echo
* ls | xargs -n3 echo
* ls | xargs -I XYZ echo XYZ is my favorite food
* rm *.txt # If .txt file tool many will report an error
  * Use following command can resolve it
  * ls | grep '\.txt$' | xargs rm
* find . -maxdepth 1 -name \*.txt -type f -print0 | xargs -0 rm
* security (The file name contains special characters)
  * find ... -print0 | xargs -0
  * ls | tr '\n' '\0' | xargs -0
    * alias ls0="find . -maxdepth 1 -print0"
### 7.4 Process control skills
#### 7.4.1 Background command
* wc -c my_extremely_huge_file.txt &
* command1 & command2 & command3 &
* command4 & command5 & echo hi
* Ctrl-Z stop process then enter bg
* wc -c my_extremely_huge_file.txt &
* bg # Move the currently pending job to the background
* bg %n # Move pending job number n to the background
* fg # Move the current background job to the foreground
* fg %n # Move background job number n to the foreground
* kill %n # Terminate background job number n
* jobs # browse shell jobs
* sleep 20 &
* jobs
* sleep 20 &
* fg
* sleep 20
* ^Z
* jobs
* fg
* sleep 20
* ^Z
* bg
* jobs
* sleep 100 &
* sleep 200 &
* sleep 300 &
* jobs
* fg %2
* ^Z
* jobs
* kill %3
* jobs
* bg %2
* jobs
* sort /usr/share/dict/words | head -n2 &
* sort /usr/share/dict/words | head -n2 > /tmp/results &
  * cat /tmp/results
* cat &
* jobs
* fg
* command1 && command2 && command3 &
#### 7.4.2 Explicit subshell
* (cd /usr/local && ls)
* pwd
* tar xvf package.tar.gz
* cat package.tar.gz | (mkdir -p /tmp/other && cd /tmp/other && tar xzvf -)
* tar czf - dir1 | (cd /tmp/dir2 && tar xvf -)
* tar czf - dir1 | ssh myhost '(cd /tmp/dir2 && tar xvf -)'
* subshell
  * echo $BASH_SUBSHELL # not subshell
  * (echo $BASH_SUBSHELL) # subshell
  * echo &(echo $BASH_SUBSHELL) # subshell
  * cat <(echo $BASH_SUBSHELL) # subshell
  * bash -c \'echo $BASH_SUBSHELL' # not subshell
#### 7.4.3 Replace shell process
* bash
* PS1="Doomed> "
  * echo hello
  * exec ls
* chmod exec1
* ./exec1
* cat /tmp/outfile
* chmod exec2
* ./exec2
* cat /tmp/outfile2
* The shell that executes exec will exit after exec completes.