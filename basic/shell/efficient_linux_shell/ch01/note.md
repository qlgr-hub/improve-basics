## Chanper 01 Combination of commands
### 1.1 Input, output and pipe
* ls -l /bin
* less # Display only one page of information at a time
* ls -l /bin/ | less
  * '|' is named pipe: command ls's stdout connect to command less's stdin
### 1.2 Six commmands
#### 1.2.1 wc
* wc animals.txt
* wc -l animals.txt # line number
* wc -w animals.txt # word number
* wc -c animals.txt # character number
* ls -1
* ls -1 | wc -l
* wc animals.txt | wc -w
* wc animals.txt | wc -w | wc
* <font color=Red>
  ls is different from all other Linux commands. It knows whether its stdout is redirected and output in different formats.
  </font>

  * ls /bin/
  * ls /bin/ | cat
  * ls
  * ls | wc -l
  * ls 
    * -1 Force output to one line.
    * -C Force output to multiple columns.
#### 1.2.2 head
* head -n3 animals.txt
* head -n3 animals.txt | wc -w
* ls /bin/ | head -n5
#### 1.2.3 cut
* cut -f2 animals.txt
* cut -f2 animals.txt | head -n3
* cut -f1,3 animals.txt | head -n3
* cut -f2-4 animals.txt | head -n3
* cut -c1,2,3 animals.txt
* cut -c1-3 animals.txt
  * -f: When the input consists of strings (fields) each separated by a '\t', cut by fields.
  * -c: Splitting by character position
* cut -f4 animals.txt
* cut -f4 animals.txt | cut -d, -f1
  * -d: delimiter, Change the delimiter from tab to a specific character.
#### 1.2.4 grep
* grep Nutshell animals.txt # Output the lines containing Nutshell.
* grep -v Nutshell animals.txt # Output the lines not containing Nutshell.
* grep Perl *.txt # find from multiple files
* ls -l /usr/lib/
* ls -l /usr/lib/ | cut -c1
* ls -l /usr/lib/ | cut -c1 | grep d
* ls -l /usr/lib/ | cut -c1 | grep d | wc -l
#### 1.2.5 sort
* sort animals.txt # Sort ascending
* sort -r animals.txt # Sort descending
  * default is alphabetical order
  * -n is used to specify in numerical order
* cut -f3 animals.txt
* cut -f3 animals.txt | sort -n
* cut -f3 animals.txt | sort -nr
* cut -f3 animals.txt | sort -nr | head -n1
  * Min value: sort -n | head -n1
  * Max value: sort -nr | head -n1
* head -n5 /etc/passwd
* head -n5 /etc/passwd | cut -d: f1
* head -n5 /etc/passwd | cut -d: f1 | sort
* cat /etc/passwd | cut -d: -f1 | sort
* cut -d: -f1 /etc/passwd | grep -w qlgr
* cut -d: -f1 /etc/passwd | grep -w rutabaga
  * -w: Only whole word matches are output; partial matches are not counted.
#### 1.2.6 uniq
* cat letters
* uniq letters
* uniq -c letters
  * -c Count the number of occurrences of each item.
* cat grades
* cut -f1 grades | sort
* cut -f1 grades | sort | uniq -c
* cut -f1 grades | sort | uniq -c | sort -nr
* cut -f1 grades | sort | uniq -c | sort -nr | head -n1
* cut -f1 grades | sort | uniq -c | sort -nr | head -n1 | cut -c9
### 1.3 Check for duplicate files
* cd images
* ls
* md5sum image001.jpg
* md5sum image001.jpg image002.jpg image003.jpg
* md5sum *.jpg | cut -c1-32 | sort
* md5sum *.jpg | cut -c1-32 | sort | uniq -c
* md5sum *.jpg | cut -c1-32 | sort | uniq -c | sort -nr
* md5sum *.jpg | cut -c1-32 | sort | uniq -c | sort -nr | grep -v "      1 "
* md5sum *.jpg | grep f6464ed766daca87ba407aede21c8fcc
* md5sum *.jpg | grep f6464ed766daca87ba407aede21c8fcc | cut -c35-