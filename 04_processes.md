-- 04-a-5000
Намерете командите на 10-те най-стари процеси в системата.

ps -e -o comm -o etimes --no-headers | tr -s " " | sort -n -k2 | head -n 10 | cut -d" " -f1
or
ps -e -o cmd -o start_time --sort=start_time --no-headers | head -n 10

-- 04-a-6000
Намерете PID и командата на процеса, който заема най-много виртуална памет в системата.

ps -e -o pid -o comm --sort=vsize | tail -n 1


-- 04-a-6300
Изведете командата на най-стария процес

ps -e -o cmd -o start_time --sort=start_time --no-headers | head -n 1

-- 04-b-5000
Намерете колко физическа памет заемат всички процеси на потребителската група root.
ps -e -o group -o size --no-headers | grep ^root | awk -F ' ' '{count+=$2} END {print count}'
or
ps -e -g root -o size --no-headers| awk '{count+=$1} END {print count}'

-- 04-b-6100
Изведете имената на потребителите, които имат поне 2 процеса, чиято команда е vim (независимо какви са аргументите й)

ps -e -o cmd -o user | grep ^vim | tr -s " "  | cut -d ' ' -f 3| uniq -c | tr -s " " | sed "s/ //" | awk -F ' ' '{if($1 > 1) print $2}'

-- 04-b-6200
Изведете имената на потребителите, които не са логнати в момента, но имат живи процеси

cut -d: -f1 /etc/passwd | grep -v "$(ps -o user)"

-- 04-b-7000
Намерете колко физическа памет заемат осреднено всички процеси на потребителската група root. Внимавайте, когато групата няма нито един процес.

ps -o size -g root | awk '{all+=$1; count+=1} END {if (count!=0) {print all/count}}'

-- 04-b-8000
Намерете всички PID и техните команди (без аргументите), които нямат tty, което ги управлява. Изведете списък само с командите без повторения.

ps -e -o tty -o comm -o pid --sort=comm | grep ^? | tr -s " " | cut -d' ' -f2 | uniq 

-- 04-b-9000
Да се отпечатат PID на всички процеси, които имат повече деца от родителския си процес.