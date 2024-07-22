## Chapter 01 Linux environment and related tools
* binutils package
### 1.1 Linux tools
#### 1.1.1 GDB (GNU debugger)
#### 1.1.2 objdump (in GNU binutils package)
* Only used for decompilation of ordinary ELF files
* View the data or code of all sections in the ELF file
  * objdump -D <elf_object>
* View only the program code in the ELF file
  * objdump -d <elf_object>
* View all symbols
  * objdump -tT <elf_object>
#### 1.1.3 objcopy (in GNU binutils package)
* Copy .data section from one ELF to another
  * objcopy --only-section=.data \<infile\> \<outfile\>
#### 1.1.4 stace (system call trace)
* Use the strace command to trace a basic program
  * strace /bin/ls -o ls.out
* Attach to an existing process using the strace command
  * strace -p \<pid\> -o daemon.out
* View all data read from the specified file descriptor
  * strace -e read=\<file descriptor\> /bin/ls
* View all data write into the specified file descriptor
  * strace -e write=\<file descriptor\> /bin/ls
#### 1.1.5 ltrace (library trace)
#### 1.1.6 Basic ltrace commands
* Use -S options to trace system call
* ltrace \<program\> -o program.out
#### 1.1.7 ftrace (function trace)
* https://github.com/elfmaster/ftrace
#### 1.1.8 readelf
* Query section header table
  * readelf -S \<object\>
* Query the program header table
  * readelf -l \<object\>
* Querying the symbol table
  * readelf -s \<object\>
* Query ELF file header data
  * readelf -n \<object\>
* Query relocation entry
  * readelf -r \<object\>
* Query dynamic segment
  * readelf -d \<object\>
#### 1.1.9 ERESI (ELF decompilation system interface)
* http://www.eresi-project.org
* Cerberus ELF interface (http:://www.phrack.org/archives/issues/61/8.txt)
* Embedded ELF debugging (http:://www.phrack.org/archives/issues/63/9.txt)
### 1.2 Useful devices and files
* /proc/\<pid\>/maps
* /proc/kcore (kernel debugging)
* /boot/System.map (all kernel's symbol)
* /proc/kallsyms (also for kernel's symbol)
* /proc/iomem
  * grep Kernel /proc/iomem
* ECFS (extended core file snapshot)
  * https://gitbhub.com/elfmaster/ecfs
### 1.3 Linker-related environment pointers
* LD_PRELOAD
  * specify high link priority library
* LD_SHOW_AUXV
  * LD_SHOW_AUXV=1 whoami
* linker script
  * a simple scripting language
  * gcc uses the -T option to specify a linker script