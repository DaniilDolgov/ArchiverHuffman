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
- Конвертация кода, записанного строкой в unsigned char. Например, если **B_code** = "101", то в результате мы получим unsigned char res = 0b00000101.
- **B_code**: строковое представление двоичного кода.
- **return**: вычисленный байт;

`getBit`
- Получение конкретного бита у байта.
- Например, если **byte** = 0b00101110, **position** = 3, то мы получим 1, так как: 0b00101110
- Нумерация начинается с нуля и идет слева направо.
- **byte**: байт.
- **position**: номер бита, который мы хотим получить.
- **return**: 0 или 1.

`add_node_decompressing`
- Функция, строящая дерево Хаффмана по закодированным символам. То есть обратное построение.
- Имея код и символ добавляем его в дерево `root`.
- **root**: Корень дерева Хаффмана.
- **code**: Код символа.
- **sym**: Символ.
- **currentID**: Индекс символа кода, на который мы сейчас смотрим.

`build_tree_from_codes`
- Создание дерева по таблице кодов Хаффмана.
- **huff_codes**: Таблица кодов, из которых мы строим дерево.
- **return**: Возвращаем корень построенного дерева.

`create_huff_tree`
- Построение дерева Хаффмана по заданному тексту. Алгоритм состоит в следующем:
  - 1) Считаем, с какой частотой встречается каждый символ в строке.
  - 2) Создаем бинарное дерево, на основе вычисленных частот, таким образом, что символы с наибольшей частотой будут иметь более короткий код, а коды с наименьшей частотой - длинный код.
  - 3) Записываем закодированные данные в файл.
- **stroka**: Текст, который кодируем.

`binToDec`
- Функция конвертации байта в десятичное число. Например, если **byte** = 0b00000101, то получится 5.
- **byte**: двоичное представление байта.
- **return**: десятичный вид байта.

`file_parsing`
- Парсинг закодированного файла. Создаётся файл **decompress.txt**, который является раскодированным.
- **path_file**: Путь к закодированному файлу.

`huff_decompressing`
- Агрегирующая функция, когда программа запускается с флагом **-d filname.zip**.
- **path_file**: Путь к файлу со сжатым текстом.
### queue.c
`deallocating_the_queue`
- Очистка памяти от очереди с приоритетом. Сначала очищаем все внутренние узлы, после чего очищаем саму очередь.
- **queue**: Очередь, от которой избавляемся.

`realloc_the_memory`
- Перевыделение памяти для очереди с приоритетом. Перевыделение происходит, когда capacity становится степенью двойки.
- **queue**: Очередь, память в которой необходимо перевыделить.
- **type**: Тип перевыделения: на повышение объема памяти или понижение.

`heapify`
- Ребалансировка бинарного дерева. Более частые символы идут в конец, а менее частые - в начало.
- **queue**: Очередь, которую ребалансируем.
- **idx**: Текущий элемент, относительно которого происходит ребалансировка.

`build_the_queue`
- Инициализация и выделение памяти под объект структуры **prior_queue**.
- **return**: указатель на очередь с приоритетом.

`deleting_a_root`
- Удаление узла из очереди с заданным символом.
- **queue**: Очередь, откуда удаляем узел.
- **symb**: Символ, по которому ищем узел для удаления.

`Insert`
- Вставка элемента в очередь с приоритетом.
- **queue**: Элемент, который вставляем.
- **new_number**: То, что вставляем.
### tree_node.c
`swap_elements`
- Функция, которая меняет два указателя местами: **x** и **y**. Объекты, лежащие под ними остаются неизменными.

`build_the_node`
- Функция выделения памяти под один объект структуры **node**.
- Инициализирует поля **sym** и **freq** переданными аргументами.
- **sym**: символ, который кладем в node;
- **freq**: частота, с которой этот символ встретился в тексте;
- **return**: указатель на node.
### main.c
`firstMessage`
- Функция выводит сообщение о том, как нужно использовать эту программу.
