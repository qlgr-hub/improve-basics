## Chapter 04 Browse file system
* cd /usr/share/lib/etc/bin
* pwd
### 4.1 Quick access to a specific directory
#### 4.1.1 Quickly return to the root directory
* pwd (/workspace/efficient_linux_shell/ch04)
* cd
* pwd (/home/qlgr)
* cd $HOME/Work
* cd ~/Work
* echo $HOME ~ (/home/qlgr /home/qlgr)
* echo ~{target user name}
#### 4.1.2 Tab key auto-completion
* cd /usr
* ls
* cd sha<tab>
* cd share/
* cd s<tab>
* cd s<tab><tab> (sbin/ share/ src/)
* cd sh<tab>
* cd share/
* The behavior of tab completion is command-dependent.
#### 4.1.3 Use aliases or variables to jump to frequently visited directories
* \# In a shell configuration file:
  * alias work="cd $HOME/Work/Projects/Web/src/include"
* work
* pwd
* work1=$HOME/Work/Projects/Web/src/include
* cd $work1
* pwd
* ls $work1/css
* \# Place in a shell configuration file and source it:
  * alias rcedit='$EDITOR $HOME/.bashrc'
* rcedit to edit $HOME/.bashrc
* qcd shell function (in shell configuration file)
* ```
        # Define the qcd fuction
        qcd() {
            # Accept 1 argument that's a string key, and perform a diffrent
            # "cd" operation for each key
            case "$1" in
                work)
                    cd $HOME/Work/Projects/Web/src/include
                    ;;
                recipes)
                    cd $HOME/Family/Cooking/Recipes
                    ;;
                video)
                    cd /data/Arts/Video/Collection
                    ;;
                beatles)
                    cd $HOME/Music/mp3/Artists/B/Beatles
                    ;;
                *)
                    # The supplied argument was not one of the supported keys
                    echo "qcd: unknown key '$1'"
                    return1
                    ;;
            esac
            # Helpfully print the current directory name to indicate where you are
            pwd
        }
        # Set up tab completion
        complete -W "work recipes video beatles" qcd
* qcd beatles
  * /home/{user name}/Music/mp3/Artists/B/Beatles
  * complete is shell builtin
* qcd <tab><tab> (work recipes video beatles)
* qcd v<tab>
* qcd video
#### 4.1.4 Using CDPATH to quickly navigate large file systems
* cd ~/Family/Memories/Photos
* cd Photos (bash: cd: Photos: No such file or directory)
* pwd (etc)
* cd Photos (/home/{user name}/Family/Memories/Photos)
* CDPATH environment variable, like PATH
#### 4.1.5 Properly organize the root directory to speed up browsing the file system
* \# Place in a shell configuration file and source it:
  * export CDPATH=\$HOME:\$HOME/Work:\$HOME/Family:\$HOME/Linux:$HOME/Music:..
* Check the file system tree for duplicate names
  * ls -d */ && (ls -d \*/\*/ | cut -d/ -f2-) | sort | uniq -c | sort -nr | less
### 4.2 Quickly return to a specific directory
#### 4.2.1 Switch back and forth between the two directories with "cd -"
* pwd (/workspace/efficient_linux_shell/ch04)
* cd /etc
* cd -
* pwd (/workspace/efficient_linux_shell/ch04)
#### 4.2.2 Switching between directories with pushd and popd
* Each running shell maintains its own directory stack
* pwd (/workspace/efficient_linux_shell/ch04)
* pushd /workspace/efficient_linux_shell/ch01
* pushd /workspace/efficient_linux_shell/ch02
* pushd /workspace/efficient_linux_shell/ch03
* pwd
* dirs (Horizontal output)
* dirs -p (Vertical output)
* dirs -p | nl -v0 (Also output line number)
* dirs -v (Also output line number)
* popd
* popd
* popd
* popd (bash: popd: directory stack empty)
* pwd (/workspace/efficient_linux_shell/ch04)
* pushd # with no argument, behavior same as "cd -"
* While jumping back and forth between multiple directories via pushd, I accidentally ran cd and lost a directory.
  * Run "pushd -" + "pushd" to save it
* pushd +N (number)
* pushd -N
* popd +N
* popd -N
