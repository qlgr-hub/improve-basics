## Chapter 08 Building a one-line command
* bash one-liner
    * ```
        paste <(echo {1..10}.jpg | sed 's/ /\n/g') \
            <(echo {0..9}.jpg | sed 's/ /\n/g') \
            | sed 's/^/mv /' \
            | bash
* echo {0..10}.jpg
* echo {0..9}.jpg
* echo {0..10}.jpg | sed 's/ /\n/g'
* echo {0..9}.jpg | sed 's/ /\n/g'
* paste <(echo {0..10}.jpg | sed 's/ /\n/g') <(echo {0..9}.jpg | sed 's/ /\n/g')
* paste <(echo {0..10}.jpg | sed 's/ /\n/g') <(echo {0..9}.jpg | sed 's/ /\n/g') | sed 's/^/mv /'
* paste <(echo {0..10}.jpg | sed 's/ /\n/g') <(echo {0..9}.jpg | sed 's/ /\n/g') | sed 's/^/mv /' | bash
### 8.1 Ready
#### 8.1.1 Don't be rigid
* ls *.jpg
* ls | grep '\\.jpg$'
* There are thousands of methods
  * echo $(ls *.jpg)
  * bash -c 'ls *jpg'
  * cat <(ls *.jpg)
  * find . -maxdepth 1 -type f -name \*.jpg -print
  * ls > tmp && grep '\.jpg$' tmp && rm -f tmp
  * paste <(echo ls) <(echo \*.jpg) | bash
  * bash -c 'exec $(paste <(echo ls) <(echo \*.jpg))'
  * echo 'monkey *.jpg' | sed 's/monkey/ls/' | bash
  * python -c 'import os; os.system("ls *.jpg")'
#### 8.1.2 Consider where to start
* echo {A..Z}
  * echo {A..Z} | awk '{print $(17)}'
  * echo {A..Z} | sed 's/ //g' | cut -c17
* echo {1..12}
  * echo 2021-{01..12}-01 | xargs -n1 date +%B -d
* ls
* ls | awk '{print "echo -n", $0, "| wc -c"}'
* ls | awk '{print "echo -n", $0, "| wc -c"}' | bash | sort -nr | head -n1
#### 8.1.3 Proficient in testing tools
* echo # print the results to check
* ls # Tests destructive commands
* tee # Intermediate results are output to files for confirmation
### 8.2 Insert a file name into the sequence
* seq -w 10 -1 3
* seq -w 10 -1 3 | sed 's/\(.*\)/ch\1.asciidoc/'
* seq -w 11 -1 4 | sed 's/\(.*\)/ch\1.asciidoc/'
* paste <(seq -w 10 -1 3 | sed 's/\(.*\)/ch\1.asciidoc/') <(seq -w 11 -1 4 | sed 's/\(.\*\)/ch\1.asciidoc/')
* paste <(seq -w 10 -1 3 | sed 's/\(.*\)/ch\1.asciidoc/') <(seq -w 11 -1 4 | sed 's/\(.\*\)/ch\1.asciidoc/') | sed 's/^/mv /'
* paste <(seq -w 10 -1 3 | sed 's/\(.*\)/ch\1.asciidoc/') <(seq -w 11 -1 4 | sed 's/\(.\*\)/ch\1.asciidoc/') | sed 's/^/mv /' | bash
* ls ch*.asciidoc
### 8.3 Check matching files
* cd ./mediawiki/original
* ls
* ls *.jpg | cut -d. -f1
* ls *.txt | cut -d. -f1
* diff <(ls *.jpg | cut -d. -f1) <(ls *.txt | cut -d. -f1)
* diff <(ls *.jpg | cut -d. -f1) <(ls *.txt | cut -d. -f1) | grep '^[<>]'
* diff <(ls *.jpg | cut -d. -f1) <(ls *.txt | cut -d. -f1) | grep '^[<>]' | awk '/^</{print $2 ".jpg"} /^>/{print $2 ".txt"}'
* cd ./mediawiki/with_yellow_canary
* diff <(ls *.jpg | cut -d. -f1) <(ls *.txt | cut -d. -f1) | grep '^[<>]' | awk '/^</{print $2 ".jpg"} /^>/{print $2 ".txt"}'
* ```
    diff <(ls *.jpg | sed 's/\.[^.]*$//') \
        <(ls *.txt | sed 's/\.[^.]*$//') \
        | grep '^[<>]' \
        | awk '/^</{print $2 ".jpg"} /^>/{print $2 ".txt"}'
* ```
    ls *.{jpg,txt} | sed 's/\.[^.]*$//' | uniq -c
* ```
    ls *.{jpg,txt} | sed 's/\.[^.]*$//' | uniq -c \
        | awk '/^ *1 /{print $2}'
* ```
    ls *.{jpg,txt} | sed 's/\.[^.]*$//' | uniq -c \
        | awk '/^ *1 /{print $2 "*"}'
* ```
    ls -1 $(ls *.{jpg,txt} | sed 's/\.[^.]*$//' | uniq -c \
        | awk '/^ *1 /{print $2 "*"}')
### 8.4 Generate CDPATH for home directory
* CDPATH=$HOME:$HOME/Work:..
* (cd && ls -d */)
* (cd && ls -d */) | sed 's/^/$HOME\//g'
* (cd && ls -d */) | sed 's@^@$HOME\/@g'
* ```
    (cd && ls -d */) | sed -e 's@^@$HOME\/@g' -e 's@/$@@'
* ```
    echo $(cd && ls -d */ | sed -e 's@^@$HOME\/@g' -e 's@/$@@')
* ```
    echo '$HOME' \
        $(cd && ls -d */ | sed -e 's@^@$HOME\/@g' -e 's@/$@@') \
        '..'
* ```
    echo '$HOME' \
        $(cd && ls -d */ | sed -e 's@^@$HOME\/@g' -e 's@/$@@') \
        '..' \
        tr ' ' ':'
* ```
    echo 'CDPATH=$HOME' \
        $(cd && ls -d */ | sed -e 's@^@$HOME\/@g' -e 's@/$@@') \
        '..' \
        tr ' ' ':'
### 8.5 Generate test files
* wc -l /usr/share/dict/words
* shuf /usr/share/dict/words | head -n3
* echo $RANDOM $RANDOM $RANDOM
* shuf -n $RANDOM /usr/share/dict/words | wc -l
* pwgen (sudo apt install pwgen)
* pwgen -N1 10 # generate one word length 10 charater
* echo $(pwgen -N1 10).txt
* mkdir -p /tmp/randomfiles && cd /tmp/randomfiles
* shuf -n $RANDOM -o $(pwgen -N1 10).txt /usr/share/dict/words
* ls
* wc -l ohWuoc0ohb.txt
* head -n3 ohWuoc0ohb.txt
* ```
    for i in {1..1000}; do
        shuf -n $RANDOM -o $(pwgen -N1 10).txt /usr/share/dict/words
    done
* echo 'shuf -n $RANDOM -o $(pwgen -N1 10).txt /usr/share/dict/words'
* echo 'shuf -n $RANDOM -o $(pwgen -N1 10).txt /usr/share/dict/words' | bash
* yes 'shuf -n $RANDOM -o $(pwgen -N1 10).txt /usr/share/dict/words' | head -n 1000 | bash
* yes head bash
* yes 'convert -size 8x8 xc: +noise Random -scale 100x100 $(pwgen -N1 10).png' | head -n 1000 | bash (sudo apt install imagemagick)
### 8.6 Generate empty files
* mkdir /tmp/empties
* cd /tmp/empties
* touch file{01..1000}.txt
* grep '^[a-z]*$' /usr/share/dict/words
* grep '^[a-z]*$' /usr/share/dict/words | shuf | head -n1000
* grep '^[a-z]*$' /usr/share/dict/words | shuf | head -n1000 | xargs touch