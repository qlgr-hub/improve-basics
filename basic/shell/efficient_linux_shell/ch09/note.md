## Chapter 09 Processing text files
* cut -d: -f1 /etc/passwd | sort
* awk -F: '$3>=1000 {print $1}' /etc/passwd
* awk -F: '$3>=1000 {print $1}' /etc/passwd | xargs -I@ echo "Hi there, @!"
* awk -F: '$3>=1000 {print $1}' /etc/passwd | xargs -I@ echo ' echo "Hi there, @!" | mail -s greetings @'
* awk -F: '$3>=1000 {print $1}' /etc/passwd | xargs -I@ echo ' echo "Hi there, @!" | mail -s greetings @' | bash
### 9.1 Find files
* find $HOME -name .bashrc -print
* find $HOME -print > .ALLFILES # Caching results speeds up subsequent lookups.
* head -n3 .ALLFILES
* ff
* ```
    #!/usr/bin/env bash
    # $@ means allrguments provided to sctipt
    grep "$@" .ALLFILES
* chmod +x ff
* echo $PATH
* ./ff .bashrc
* ./ff -i bash | less
* ./ff -i bash | wc -l
* cron + find update .ALLFILES
* locate
### 9.2 Check the expiration date of a domain name
* whois example.com | less
* whois example.com | grep \ 'Registry Expiry Date:'
* whois example.com | grep \ 'Registry Expiry Date:' | awk '{print $4}'
* date --date 2024-08-13T04:00:00Z
* date --date 2024-08-13T04:00:00Z +'%Y-%m-%d'
* date --date $(whois example.com | grep \ 'Registry Expiry Date:' | awk '{print $4}') +'%Y-%m-%d'
* check-expiry
* ```
    #!/usr/bin/env bash
    expdate=$(date \
                --date $(whois "$1" \
                        | grep 'Registry Expiry Date:' \
                        | awk '{print $4}') \
                +'%Y-%m-%d')
    echo "$expdate	$1"		# Separated by a tab
* chmod +x check-expiry
* ./check-expiry
* ./check-expiry-all &> expiry.txt &
* cat expiry.txt
* sort -n expiry.txt | head -n1
* awk "\\\$1<=\\"$(date +%Y-%m-%d)\\"" expiry.txt
### 9.3 Building an area code database
* grep -w NJ areacodes.txt
* grep -w 202 areacodes.txt
* grep Washington areacodes.txt
* wc -l areacodes.txt
* cut -f2 areacodes.txt | sort | uniq -c | sort -nr | head -n1
* awk -F'\t' '{printf "%s,%s,\"%s\"\n", $1, $2, $3}' areacodes.txt
* awk '\$2~\/^NJ$/{ac=ac FS $1} END {print "NJ:" ac}' areacodes.txt
* awk '{arr[$2]=arr[$2] " " $1} END {for (i in arr) print i ":" arr[i]}' areacodes.txt
* areacode
* ```
    #!/usr/bin/env bash
    if [ -n "$1" ]; then
        grep -iw "$1" areacodes.txt
    fi
* chmod +x areacode
* ./areacode 617
### 9.4 Building a password manager
* touch vault
* chmod 600 vault
* code vault # edit
* cat vault
* mkdir ~/etc
* mv vault ~/etc
* cd ~/etc
* grep sally vault
* grep work vault
* grep drop vault
* code pman-v1
* chmod +x pman-v1
* ./pman-v1 goog
* ./pman-v1 account
* ./pman-v1 facebook
* code pman-v2
* chmod +x pman-v2
* ./pman-v2
* ./pman-v2 smith
* ./pman-v2 xyzzy
* code pman-v3
* chmod +x pman-v3
* gpg --quick-generate-key email-address default default never
* gpg -e -r 457709928@qq.com vault
* gpg -d -q vault.gpg
* id3tool # extract ID3 info from .mp3 file