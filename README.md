# Tape Sorter
### Приложение, которое выполняет сортировку данных с входной ленты, на выходную, с использованием ограниченного количества оперативной памяти.

**Формат запуска:**

`./TapeSort <input filename> <out filename> <bytes amount>`

`input filename` - имя файла, с входными данными (каждое число на новой строке)

`out filename` - имя выходного файла

`bytes amount` - максимальное число байт, используемое программой

**Также для работы приложения необходима конфигурация в формате:**

```
read_delay: 1
write_delay: 2
move_delay: 3
```

Задержка задается в наносекундах.

> Примечание:
> Размером векторов для хранения временных лент пренебрегаем, тк считаем, что ленты физические. 

> В момент времени должно быть доступно минимум `число временных файлов * sizeof(HeapNode) = tmp * 8` байт. 
> Это необходимо для корректного слияния при сортировке. 

Так же написаны юнит тесты для проверки основных аспектов работы приложения при помощи **GTest**.
