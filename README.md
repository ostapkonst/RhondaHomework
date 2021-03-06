# Rhonda Homework

Задание №1 из сборника практических задач по курсу «Введение в разработку встроенных систем» (0.4).

## Описание практического задания

Напишите программу, выполняющую сортировку чисел из входного текстового файла по возрастанию. Вывод отсортированной последовательности чисел должен осуществляться в отдельный выходной текстовый файл.

### Формат входного и выходного файлов

1. По одному целому неотрицательному 32-разрядному десятичному числу в строке без пробелов.
2. Строки могут быть отделены друг от друга как символом '\n', так и символами '\r\n'.
3. Пустая строка в конце файла может как присутствовать, так и отсутствовать.

### Ограничения на размер файла

Размер входного файла может быть как небольшим, так и может превышать размер доступного ОЗУ на целевом устройстве. Это требуется учитывать при выполнении работы.

## Доказательство запуска на встроенной системе

Одним из требований была указана возможность запуска на встроенной системе. В качестве таковой, была выбранна Raspberry PI.

![Confirmation of running code on an embedded system](raspberrypi_build_success.jpg)
