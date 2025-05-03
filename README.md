# SSA_PR5

# Технології та запуск

## Як середовище розробки було обрано Docker-контейнер на базі образу `debian:bullseye-slim` з таких причин:

### Прозорість — усі початкові умови для виконання завдання задані в `Dockerfile`, що дозволяє бачити весь процес виконання, а також гарантує стабільність роботи коду.

### Швидкість відтворення початкових умов — Docker-контейнер дозволяє легко змінювати необхідні пакети та конфігурації. Усі зміни можна відкрутити назад за кілька секунд, тоді як у віртуальній машині це займає певний час. Це особливо актуально для завдань, які потребують змін або видалення файлів.

### Зручність розробки — Docker дозволяє швидко змінювати архітектуру, копіювати файли з основної машини та автоматизувати повторювані команди, що значно пришвидшує розробку.

### Варіативність — якщо щось неможливо або складно реалізувати на базі одного образу, завжди можна замінити його на інший.

#### *У завданнях, які неможливо реалізувати як задумано без використання повноцінної системи, буде застосовано `VM`*

## Запуск

### Всі необхідні команди для запуску контейнерів та виконання файлів описані в `Dockerfile`

#### *В наступному пункті будуть описуватися тільки результати виконання команд, відповіді на питання та опис реалізації*

# Звіт по завданням

## Задача 1

### Вивід команди rwho до more 

#### *Для запуску використовувалась VM*
```
yaroslav@yaroslav:~/ssa/SSA_PR7/task1 $ gcc -Wall -g task.c -o task 
yaroslav@yaroslav:~/ssa/SSA_PR7/task1 $ ./task 
yaroslav yaroslav:ttyv1 Feb 8 20:01 
--More--(END)
```

## Задача 2

### Імітація команди ls -l
```
root@07364bc947a2:/app# gcc -Wall task.c -o task
root@07364bc947a2:/app# ./task
total 24
-rwxr-xr-x  1 root root    17312 May 03 07:23 task
-rwxr-xr-x  1 root root     2197 May 03 07:15 task.c
root@07364bc947a2:/app# ls -l
total 24
-rwxr-xr-x 1 root root 17312 May  3 07:23 task
-rwxr-xr-x 1 root root  2197 May  3 07:15 task.c
root@07364bc947a2:/app# 
```

## Задача 3

### Друкук рядки з файлу, що містять слово
```
root@857b6652c4bd:/app# gcc -g task.c -o task -lm
root@857b6652c4bd:/app# ./task
Usage: ./task <word> <file>
root@857b6652c4bd:/app# ./task hi test.txt
hi 0
hi 4
hi 8
hi 10
```

## Задача 4

### Спрощена версія утиліти more
```
root@75434f9ee1c5:/app# gcc -g task.c -o task -lm
root@75434f9ee1c5:/app# ./task test.txt test.txt
==== test.txt ====
1
2
3
4
5
6
7
8
9
10
11
12
13
14
15
16
17
18
19
20
Press Enter to continue...
21
22
23
24
25
26
27
28
29
30
31
32
33
34
35
36
37
38
39
40
Press Enter to continue...
41
End of file
==== test.txt ====
1
2
3
4
5
6
7
8
9
10
11
12
13
14
15
16
17
18
19
20
Press Enter to continue...
21
22
23
24
25
26
27
28
29
30
31
32
33
34
35
36
37
38
39
40
Press Enter to continue...
41
End of file
```

## Задача 5

### Перелічування всіх файли в поточному каталозі та всіх файлів в підкаталогах.

```
root@222558a065c4:/app# gcc -g task.c -o task -lm
root@222558a065c4:/app# ./task
./task
./test/test2.txt
./test/test3.txt
./test1.txt
./task.c
```

## Задача 6

### Перелічування підкаталогів у алфавітному порядку.

```
root@0319a03e2236:/app# gcc -g task.c -o task -lm
root@0319a03e2236:/app# ./task
testA/
testB/
```

## Задача 7

### Надання дозволу на файли `.c` іншим користувачам

```
root@d5683665882a:/app# gcc -g task.c -o task -lm
root@d5683665882a:/app# su testuser
$ cat test.c
cat: test.c: Permission denied
$ exit
root@d5683665882a:/app# ./task 
File: test.c
Give permission to 'test.c'? (y/n): y
Permission granted.
File: task.c
Give permission to 'task.c'? (y/n): n
root@d5683665882a:/app# su testuser
$ cat test.c
#include <stdio.h>
#include <stdlib.h>...
```

## Задача 8

### Програма для пофайлового видалення
```
root@8e8c7314489e:/app# gcc -g task.c -o task -lm
root@8e8c7314489e:/app# ./task 
Do you want to delete file: task? (y/n): n
Do you want to delete file: testB.c? (y/n): y
File testB.c deleted successfully.
Do you want to delete file: testA.c? (y/n): y
File testA.c deleted successfully.
Do you want to delete file: task.c? (y/n): y
File task.c deleted successfully.
root@8e8c7314489e:/app# ls
task
```

## Задача 9

### Таймер виконання фрагменту коду
```
root@e566703fdf9b:/app# gcc -g task.c -o task -lm
root@e566703fdf9b:/app# ./task
Time taken to execute the code: 0.410000 milliseconds
```

## Задача 10

### Генератор випадкових чисел
```
root@9bc0b7561169:/app# gcc -g -Wall task.c -o task -lm
root@9bc0b7561169:/app# ./task
Random numbers in the range [0.0, 1.0]:
0.681428
0.182609
0.667024
0.453154
0.763804

Enter a value for n: 10

Random numbers in the range [0.0, 10.00]:
6.271491
5.946759
5.255958
9.280894
6.000743
root@9bc0b7561169:/app# ./task
Random numbers in the range [0.0, 1.0]:
0.543257
0.480631
0.581576
0.007823
0.228267

Enter a value for n: 99.74

Random numbers in the range [0.0, 99.74]:
38.473032
97.292104
37.565537
86.014824
76.664803
```

## Задача за варіантом 22

### Детектор сплячих процесів
```
root@7398b1609d8f:/app# gcc -g -Wall task.c -o task -lm
root@7398b1609d8f:/app# gcc -g -Wall sleep.c -o sleep
root@7398b1609d8f:/app# ./sleep &
[1] 17
root@7398b1609d8f:/app# Process 1 (PID: 18) sleeps for 60 seconds...
Process 2 (PID: 19) sleeps for 60 seconds...
Process 3 (PID: 20) sleeps for 60 seconds...
Process 4 (PID: 21) sleeps for 60 seconds...
Process 5 (PID: 22) sleeps for 60 seconds...

root@7398b1609d8f:/app# ./task 
Sleeping processes detected:
PID        Status     CPU Time   Command
1          S          0.20       s
17         S          0.00       sleep
18         S          0.00       sleep
19         S          0.00       sleep
20         S          0.00       sleep
21         S          0.00       sleep
22         S          0.00       sleep
23         S          0.00       +
24         S          0.00       +
```