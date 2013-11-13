Задача 5. Стековая машина с условными переходами
================================================

Разовьём [задачу 4](../stack-build-script/). Добавим в язык метки и одну команду условного перехода:

- `:ЧИСЛО` - метка для совершения перехода с номером ЧИСЛО. Пример: `:42`.
- `jbe ЧИСЛО` - снимает пару чисел `a` и `b` со стека. Делает переход на метку `ЧИСЛО`, если
`a < b`. Иначе продолжает выполнение программы со следующей строчки.

Например, вот эта программа печатает 42 в вечном цикле:
```asm
:1       ; метка с номером 1. не попадёт в ассемблированный файл, не исполняется
push 42  ; кладём на стек число 42
out      ; снимаем число 42 со стека и печатаем его
push 0   ; кладём на стек число 0
push 1   ; кладём на стек число 1
jb 1     ; если 0 < 1, то делаем переход на метку 1 (вечный цикл)
```

Также стоит добавить либо команду `dup` (продублировать вершину стека), либо две команды работы с регистром:
- `pop_ax` - снести вершину стека в регистр `ax`
- `push_ax` - положить значение регистра `ax` на стек (регистр при этом сохраняет своё значение)

Напишем программу, которая печатает квадраты первых 10 натуральных чисел. Реализация через регистр:
```asm
push 0   ; начальное значение счётчика цикла
:1       ; метка начала цикла
push 1   ; кладём единицу, на которую увеличим счётчик цикла
add      ; инкремент счётчика
pop_ax   ; кладём счётчик в регистр
push_ax  ; сохраняем счётчик для следующей итерации
push_ax  ; копия для проверки условия выхода из цикла
push_ax  ; дубликат для подсчёта квадрата
push_ax  ; дубликат для подсчёта квадрата
push_ax  ; дубликат для вывода числа
out      ; выводим число
mul      ; считаем квадрат числа
out      ; выводим квадрат числа
push 10  ; кладём граничное значение цикла
jb :1    ; прыжок если stack[-2] < stack[-1]
```

Реализация через `dup`:
```asm
push 0   ; начальное значение счётчика цикла
:1       ; метка начала цикла
push 1   ; кладём единицу, на которую увеличим счётчик цикла
add      ; инкремент счётчика
dup      ; копия для проверки условия выхода из цикла
dup      ; дубликат для подсчёта квадрата
dup      ; дубликат для подсчёта квадрата
dup      ; дубликат для вывода числа
out      ; выводим число
mul      ; считаем квадрат числа
out      ; выводим квадрат числа
push 10  ; кладём граничное значение цикла
jb :1    ; прыжок если stack[-2] < stack[-1]
```


1. Дизайн команд
----------------

Команды из архитектуры, представленной выше, съедают все свои аргументы со стека. Подумайте, насколько это оправдано, и не хотите ли вы поменять их дизайн.

Имеется ввиду следующее. Пусть нужно распечатать вершину стека, после чего продолжить с ней работать. В нашей архитектуре для этого надо написать
```asm
dup
out
```

Если бы команда `out` не съедала свой аргумент, то мы могли бы просто написать 
```asm
out
```
Вершина стека при этом осталась бы нетронутой.



2. Интерпретатор, ассемблер, дизассемблер
-----------------------------------------

Реализуйте интерпретатор, ассемблер и дизассемблер для этого языка команд.

Для осуществления интерпретации и ассемблирования советуем делать два прохода по тексту программы. На первом проходе никакие действия в режиме интерпретации не исполняются, а для всех меток запоминается номер команды, на которую они указывают. На втором проходе для всех команд `jb` (или для ваших собственных команд условного перехода) по номеру метки проставляется номер команды, на которую надо делать прыжок.



Краткий конспект разговора 1 ноября
-----------------------------------

1. Кодировки: windows-1250, windows-1251, koi8-r, UTF-8, UTF-16. Для желающих имеются [задачи](https://sites.google.com/site/vpavlenkoinf/home/teoria/kodirovki-i-dvoicnye-dannye-zadanie).

2. Флаги "-v", "-E". Файлы .c/.h/.o/.a. Порядок сборки приложений.



План разговора на 8 ноября
--------------------------

1. Различия функций `fgets`, `fscanf`, `getline`. Как считать содержимое файла целиком, почему `getc()` возвращает `int`, а не `char`. 

2. One definition rule (правило, исключения), include guard.

3. Стандарт POSIX: что такое `#define _GNU_SOURCE` в `man getline`?

4. Начала работы с утилитой make.