# MyArchiver - Архиватор на основе алгоритма Хаффмана
## Описание
Архиватор на основе алгоритма Хаффмана может сжимать данные, а именно текстовые файлы. Также он может обратно разжимать текстовые файлы. Архиватор можно вызвать из командной строки, и в результате сжатия и расжатия результат будет записываться в изначально определённые файлы.
## Сборка программы в командной строке
Компилятор gcc должен быть установлен в командной строке. Открываем её, и пишем:
```
cd project
```
Вместо слова **project** нужно написать путь к папке с файлами проекта

Затем в компиляторе нужно написать следующее:
```
gcc -c *.c
gcc -o program *.o
program
```
Вместо слова **program** нужно написать имя программы (можно придумать любое, и далее его использовать)
## Работа проекта
В этой программе можно сделать два действия: сжать и разжать файл
### Сжатие файла
В командной строке нужно написать следующее:
```
./program -c filename
```
Вместо слова **program** нужно написать имя программы, которое уже указывалось

Вместо слова **filename** нужно написать путь к файлу, который нужно сжать (в нашем случае это файл **test.txt**)


В результате сжатия файла, в папку с файлами проекта добавится сжатый файл.

### Разжатие файла
Далее в командной строке нужно написать следующее:
```
./program -d encoded.zip
```
**program** - имя программы

**encoded.zip** - это сжатый .zip файл, который был создан в папке с файлами проекта в результате сжатия


В результате разжатия файла, в папку с файлами проекта добавится разжатый файл.

## Функции в файлах проекта
### bin_tree.c
`creating_a_tree` 
- Функция выделения памяти под один объект структуры tree.

`add_node0`
- Функция добавления узла на ветку.

`add_node`
- Обертка над функцией **add_node0**, сделанная для удобства.
### compress.c
`encoding`
- Построение дерева из корня **root**, на основе кодов **huff_code**. Рекурсивная функция, использующая **string** для построения кода.
- root: корень дерева, в которое строим коды.
- string: текущий код при рекурсивном вызове.
- huff_code: таблица кодов Хаффмана.

`decoding`
- Декодирование символа и запись его в файл **file**. Файловый дескриптор **file** должен быть открыт при передачи в функцию, иначе будет ошибка.
- **root** - корень дерева, где мы ищем код, расположенный в строке **string** по индексу **id**.
- root: корень дерева, в которое строим коды.
- string: текущий код при рекурсивном вызове.

`byte_code`


`getBit`


`add_node_decompressing`


`build_tree_from_codes`


`create_huff_tree`


`binToDec`


`file_parsing`


`huff_decompressing`

### queue.c
`deallocating_the_queue`


`realloc_the_memory`


`heapify`


`build_the_queue`


`deleting_a_root`


`Insert`

### tree_node.c
`swap_elements`


`build_the_node`
