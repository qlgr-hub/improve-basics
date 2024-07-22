## Chapter 05 Expand your toolbox
### 5.1 Generating text
* cut -d: -f1 /etc/passwd | sort
* cat *.txt | wc -l
#### 5.1.1 date
* date
  * +: Start of format string
  * %Y: year
  * %m: month
  * %d: day
  * %H: hour # 24-hour system
  * %M: minute
  * %S: second
  * %A: day of the week
* date +%Y-%m-%d
* date +%H:%M:%S
* date +"I cannot believe it's already %A!"
#### 5.1.2 seq
* seq 1 5 # seq {start} {end}
* seq 1 2 10 # seq {start} {step} {end}
* seq 3 -1 0 # Descending
* seq 1.1 0.1 2 # floating point
* seq -s/ 1 5 # -s separator
* seq -w 8 10 # -w Equal Width
#### 5.1.3 Brace expansion (shell feature)
* {start..end} or {start..end..step}
* echo {1..10}
* echo {10..1} # Descending
* echo {01..10} # Equal Width
* echo {1..1000..100}
* echo {1000..1..100}
* echo {01..1000..100}
* ls (file1 file2 file4)
* ls file[2-4] # Pattern matching operators for file names
* ls file{2..4} # Just append number list (ls: cannot access 'file3': No such file or directory)
* echo {A..Z} # not just number
* echo {A..Z} | tr -d ' ' # -d delete
* echo {A..Z} | tr ' ' '\n'
* alias nth="echo {A..Z} | tr -d ' ' | cut -c"
#### 5.1.4 find
* find /etc -print
* find . -type f -print # just file
* find . -type d -print # just directory
* find /etc -type f -name "*.conf" -print
  * The pattern needs to be quoted or escaped to prevent the shell from processing the expression before executing the command
* find . -iname "*.txt" -print # ignore case
* find /etc -exec echo @ {} @ ";"
  * {}: Placeholder for result
  * ";" or \; # ending of -exec
* find /etc -type f -name "*.conf" -exec ls -l {} ";"
* find $HOME/tmp -type f -name "*~" -exec echo rm {} ";"
* find $HOME/tmp -type f -name "*~" -exec rm {} ";"
#### 5.1.5 yes
* yes
* yes woof!
* yes "Efficient Linux" | head -n3
### 5.2 Separate text
#### 5.2.1 grep
* cat frost
* grep his frost
* grep -w his frost # equal width
* grep -i his frost # ignore case
* grep -l his * # find file include his
* grep (get regular expression and print)
* grep '^[A-Z]' myfile # Start with uppercase letter
* grep -v '^$' myfile # Filter empty lines
  * -v ignore
  * '^$' match empty lines
* grep 'cookie\|cake' myfile # match cookie or cake
* grep '.....' myfile # Contain at least 5 characters line
* grep '<.*>' page.html # All < before >, e.g. html label
* grep w. frost # find 'w.', but it dosn't work
  * grep 'w\.' frost
  * grep -F w. frost # fixed, force ignore regular expression
  * fgrep w. frost # fgrep == grep -F ?
* grep -f
  * find Find text that matches a set of strings
  * cat /etc/passwd
  * cat /etc/shells
  * cut -d: -f7 /etc/passwd | sort -u | grep -f /etc/shells -F
    * sort -u # Deduplication and sort
#### 5.2.2 tail
* cat alphabet
* tail -n3 alphabet # last 3 lines, default last 10 lines
* tail -n+25 alphabet # Everything from line 25 to the end of the file
* head -n4 alphabet | tail -n1 # Contents at a certain position in the middle of the file
* head -n8 alphabet | tail -n3 # 6 ~ 8 line
  * head -nN alphabet | tail -n{N-M+1} # M ~ N
* head -4 alphabet # head -n4 alphabet
* tail -3 alphabet # tail -n3 alphabet
* tail +25 alphabet # tail -n+25 alphabet
#### 5.2.3 awk {print}
* less /etc/hosts
* awk '{print \$2}' /etc/hosts 
  * {print \$column number}
  * {print \$(column number)} # for bigger than 9
  * $NF: last column (NF is field number)
  * $0 whole line
* echo Efficient fun Linux | awk '{print $1 $3}' # has no space
* echo Efficient fun Linux | awk '{print $1, $3}' # has space
* df / /data
* df / /data | awk '{print $4}'
* df / /data | awk 'FNR>1 {print $4}' # NR is row No.
* echo efficient:::::linux | awk -F':*' '{print  $2}' # Specify separator
### 5.3 Combining text
* cat peom1
* cat peom2
* cat peom3
* cat peom1 poem2 poem3
* echo efficient       linux   in    $HOME
#### 5.3.1 tac
* cat poem1 poem2 poem3 | tac
* tac peom1 poem2 poem3
#### 5.3.2 paste
* cat title-words1
* cat title-words2
* paste title-words1 title-words2
* paste title-words1 title-words2 | cut -f2
* paste -d, title-words1 title-words2 # Delimiter
* paste -d, -s title-words1 title-words2 # transpose combine
* paste -d "\n" title-words1 title-words2 # Cross Display
#### 5.3.3 diff
* cat file1
* cat file2
* diff file1 file2
* diff file1 file2 | grep '^[<>]' # Start with '<' or '>'
* diff file1 file2 | grep '^[<>]' | cut -c3- # delete starting symbol
### 5.4 Text conversion
* wc\sort\uniq
#### 5.4.1 tr
* echo $PATH | tr : "\n"
* echo efficient | tr a-z A-Z
* echo Efficient | tr A-Z a-z
* echo Efficient Linux | tr " " "\n"
* echo efficient linux | tr -d ' \t' # delete space and tab
#### 5.4.2 rev
* Brief of reverse ?
* echo Efficient Linux | rev
* cat celebrities
* rev celebrities
* rev celebrities | cut -d' ' -f1
* rev celebrities | cut -d' ' -f1 | rev
* rev myfile | tac | rev | tac # Hedged
#### 5.4.3 awk and sed
* same as head
  * sed 10q myfile
  * awk 'FNR<=10' myfile
* echo image.jpg | sed 's/\.jpg/.png/' # Replace .jpg to .png
* echo "linux efficient" | awk '{print $2, $1}'
* Basic knowledge of awk
  * awk {awk script} {input file} # execute awk script
  * awk -f {awk script1} -f {awk script2} -f {awk script3} {input file} # execute multiple awk script file
  * awk '{print $NF}' celebrities
    * same as rev celebrities | cut -d' ' -f1 | rev
  * echo efficient linux | awk '/efficient/'
  * awk -F'\t' '{print $4, "(" $3 ").", "\"" $2 "\""}' animals.txt
  * awk -F'\t' '/^horse/{print $4, "(" $3 ").", "\"" $2 "\""}' animals.txt
  * awk -F'\t' '$3~/^201/{print $4, "(" $3 ").", "\"" $2 "\""}' animals.txt
  * ```
        awk -F'\t' \
        'BEGIN {print "Recent books:"} \
        $3~/^201/{print "-", $4, "(" $3 ").", "\"" $2 "\""} \
        END {print "For more books, search the web"}' \
        animals.txt
  * seq 1 100 | awk '{s+=$1} END {print s}'
  * cd images
    * md5sum *.jpg | cut -c1-32 | sort | uniq -c | sort -nr | grep -v "      1 "
    * md5sum *.jpg
    * md5sum *.jpg | awk '{counts[$1]++}'
    * md5sum *.jpg | awk '{counts[$1]++} END {for (key in counts) print counts[key]}'
    * md5sum *.jpg | awk '{counts[$1]++} END {for (key in counts) print counts[key] " " key}'
    * md5sum *.jpg | awk '{counts[$1]++; names[$1]=names[$1] " " $2} END {for (key in counts) print counts[key] " " key ":" names[key]}'
    * md5sum *.jpg | awk '{counts[$1]++; names[$1]=names[$1] " " $2} END {for (key in counts) print counts[key] " " key ":" names[key]}' | grep -v '^1 ' | sort -nr
    * md5sum *.jpg | awk '{counts[$1]++; names[$1]=names[$1] " " $2} END {for (key in counts) if (counts[key] > 1) print counts[key] " " key ":" names[key]}' | sort -nr
* Basic knowledge of sed
  * sed: stream editor 
  * sed {sed script} {input file} # execute sed script
  * sed -e {sed script1} -e {sed script2} -e {sed script3} {input file} # execute multiple sed scripts
  * sed -f {sed script1} -f {sed script2} -f {sed script3} {input file} # execute multiple sed script files
  * s/regexp/replacement/
    * Replacing/Can be replaced with other convenient characters
    * s/regexp/replacement/ # Use /
    * s_regexp_replacement_ # Use _
    * s@regexp@replacement@ # Use @
  * echo Efficient Windows | sed "s/Windows/Linux/"
  * sed 's/.* //' celebrities
    * same as rev celebrities | cut -d' ' -f1 | rev
  * echo Efficient Stuff | sed "s/stuff/linux/"
  * echo Efficient Stuff | sed "s/stuff/linux/i" # options i ignore case
  * echo efficient stuff | sed "s/f/F/" (eFficient stuff) # Just replace first match 
  * echo efficient stuff | sed "s/f/F/g" (eFFicient stuFF) # options g means global (Replace all matches)
  * seq 10 14 | sed 4d # delete line 4th
  * seq 101 200 | sed '/[13579]$/d' # options d means delete (delete the lines ending with an odd number)
  * Matching subexpressions with sed
    * Start with\(  end with \): subexpressions
    * subexpressions has No. e.g. \1 \2 At most \9
    * ls (image.jpg.1 image.jpg.2 image.jpg.3)
    * image\.jpg\.[1-3]
    * image\.jpg\.\([1-3]\)
    * ls image.jpg* | sed "s/image\.jpg\.\([1-3]\)/image\1.jpg/"
    * \([a-z][a-z]*\) # base name
    * \([a-z][a-z][a-z]\) # extension name
    * \([0-9]\) # a number
    * ls | grep ".\*\\.[0-9]\$" | sed "s/\([a-z][a-z]*\)\.\([a-z][a-z][a-z]\)\.\([0-9]\)/\1\3.\2/"
### 5.5 Further expanding the toolbox
* cat title.txt
* fold -w40 title.txt # wrap each input line to fit in specified width
* man -k width # -k key word search
* man -k "wide|width"