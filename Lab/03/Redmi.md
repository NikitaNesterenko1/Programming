<p align="center">МИНИСТЕРСТВО НАУКИ  И ВЫСШЕГО ОБРАЗОВАНИЯ РОССИЙСКОЙ ФЕДЕРАЦИИ<br>
Федеральное государственное автономное образовательное учреждение высшего образования<br>
"КРЫМСКИЙ ФЕДЕРАЛЬНЫЙ УНИВЕРСИТЕТ им. В. И. ВЕРНАДСКОГО"<br>
ФИЗИКО-ТЕХНИЧЕСКИЙ ИНСТИТУТ<br>
Кафедра компьютерной инженерии и моделирования</p>
<br>
<h3 align="center">Отчёт по лабораторной работе № 3<br> по дисциплине "Программирование"</h3>
<br><br>
<p>студента 1 курса группы ПИ-б-о-202(1)<br>Нестеренко Никиты Сергеевич<br>
направления подготовки 09.03.04 "Программная инженерия"</p>
<br><br>
<table>
<tr><td>Научный руководитель<br> старший преподаватель кафедры<br> компьютерной инженерии и моделирования</td>
<td>(оценка)</td>
<td>Чабанов В.В.</td>
</tr>
</table>
<br><br>
<p align="center">Симферополь, 2020</p>
<hr>

## Цель

1. Закрепить навыки разработки программ с простым графическим интерфейсом пользователя на зыке Python при помощи библиотеки Tkinter;
2. Получить представление о разработке простых игровых приложений.

## Постановка задачи

1. Используя стандартный модуль для разработки программ с графическим интерфейсом Tkinter реализуйте игру Lines на зыке Python.
2. В качестве образца графического интерфейса использована [данная игра](http://game-shariki.ru/linii-2).

## Выполнение работы

В самом начале была задача сделать игровое поле, которое можно легко редактировать в реальном времени.
В первый раз игра была реализована с помощью класса Label, у которой имеется изображение клетки с
наложенным сверху шариком, однако столкнувшись с проблемой создания текста без своего фона в правой части,
было решено сделать один объект Canvas, помещённый в корневой frame, на котором и производятся все изменения.

Каждая клетка являвется экземпляром класса, который хранит цвет, размер и состояние, выбрана ли клетка и id объекта на canvas.
У каждого объекта есть функция, которая для неё генерирует новую картинку на основе полей экземпляра и
заменяет картинку на Canvas по уникальному id объекта.

Далее были реализованы надписи справа:
- название игры
- счёт
- подсказка
- кнопки "сделать ход" и "новая игра"

Для счёта запоминался id текста, который должен содержать текущий счёт (целое число) и по этому id изменялся счёт через функцию update_score().

Были реализованы функции генерации 3 случайных шариков самого большого размера (подсказки), которые помещались в специальный глобальный буфер, а так же
функция, которая перемещала шарики из буфера на игровое поле. Если нельзя разместить все шарики или после размещения шариков не оставалось пустых
клеток, то игра считается завершённой.

Кнопка "сделать ход" размещает шары из подсказки и генерирует новую.

Кнопка "новая игра" очищает поле, генерирует подсказку, размещает подсказку и снова её генерирует. Игра считается не завершённой.

При попытке перемещения клетки вызывается функция проверки, а можно ли из исходной клетки добраться до цели. Реализован алгоритм BFS (поиска в ширину),
заимствованный из ресурса GeeksForGeeks и переделанный под данное приложение.

После каждого хода делается проверка на 5 и более одинаковых шариков в ряд, столбец и диагональ, и за каждый удалённый шарик добавляется по 2 очка.
Это реализованно через массивы из массивов из ссылок на клетки игрового поля по вертикали, горизонтали и диагонали.

Скриншоты игрового процесса:

![](doc/начало.png)
   
   Рисунок 1. Игра "Шарики"


![](doc/удаление1.png)

![](doc/удаление2.png)
   
   Рисунок 2. Игрок удалил ряд из зеленых шаров 


![](doc/конец.png)
   
   Рисунок 3. Игрок проиграл 


Исходный код на Python: [Pyton.py](Pyton/Pyton/Pyton.py)

<details>
<summary>Спойлер!</summary>
    
```python
from tkinter import *
from PIL import Image, ImageTk
from random import randrange, shuffle
 
root = Tk()
board = []
line = []
N = 9
colors = 7
n_balls = 3
line_balls = 5
cost = 2
current_cell = None
assets = []
 
def is_empty(lbl):
    return lbl.color == -1

def set_image(lbl):
    global img_bgr_unselect, img_bgr_select
    bgr = img_bgr_select if lbl.selected else img_bgr_unselect
    if is_empty(lbl):
        img = ImageTk.PhotoImage(bgr)
    else:
        bgr = bgr.convert('RGBA')
        ball = Image.open(assets[lbl.color]).crop((0, 0, 55, 55)).convert('RGBA')
        pic_size_same_as_bgr = Image.new("RGBA", bgr.size)
        pic_size_same_as_bgr.paste(ball, (5,5)) # Маска не нужна
        ball_over_bgr = Image.alpha_composite(bgr, pic_size_same_as_bgr)
        img = ImageTk.PhotoImage(ball_over_bgr)
    lbl.image = img
    lbl.config(image=img)
    
def set_ball(lbl, color):
    lbl.color = color
    set_image(lbl)

def click_cell(event):
    global current_cell
    lbl = event.widget
    if lbl.selected:
        lbl.selected = False
        current_cell = None
    else:
        lbl.selected = True
        if current_cell:
            if is_empty(lbl) and not is_empty(current_cell):
                lbl.selected = False
                lbl.color = current_cell.color
                reset_cell(current_cell)
                current_cell = None
                check_lines()
            else:
                current_cell.selected = False
                set_image(current_cell)
                current_cell = lbl
        else:
            current_cell = lbl
    set_image(lbl)
        
def next_balls():
    for col in range(n_balls):
        set_ball(line[col], randrange(0, colors))

def show_game_over():
    global lbl_game_over
    lbl_game_over.grid(row=int(N/2-1), column=1, rowspan=3, columnspan=N-2)

def count_empty():
    count = 0
    for row in range(N):
        for col in range(N):
            if is_empty(board[row][col]):
                count+=1
    return count

def set_counter(count):
    global lbl_counter
    lbl_counter.counter = count
    lbl_counter.config(text="Count: {}".format(count))

def add_count(count):
    global lbl_counter
    set_counter(lbl_counter.counter + count)
    
def check_line(line, lines):
    if len(line) >= line_balls:
        lines.append(line.copy())
        for lbl in line:
            reset_cell(lbl)
            add_count(cost)

def check_cell(lbl, line, lines):
    if is_empty(lbl):
        check_line(line, lines)
        line.clear()
    elif len(line) == 0 or lbl.color == line[len(line)-1].color:
        if len(line) < 5:
            line.append(lbl)
    else:
        check_line(line, lines)
        line.clear()
        line.append(lbl)

def find_lines():
    lines = []
    buffer = [[],[],[],[]]
    for i in range(N-line_balls+1):
        for j in range(N-i):
            check_cell(board[i+j][j], buffer[0], lines)
            check_cell(board[i+j][N-1-j], buffer[1], lines)
            check_cell(board[N-1-i-j][j], buffer[2], lines)
            check_cell(board[N-1-i-j][N-1-j], buffer[3], lines)
        for line in buffer:
            check_line(line, lines)
            line.clear()

    buffer = [[],[]]
    for i in range(N):
        for j in range(N):
            check_cell(board[i][j], buffer[0], lines)
            check_cell(board[j][i], buffer[1], lines)
        for line in buffer:
            check_line(line, lines)
            line.clear()

    found = len(lines) > 0
    #for line in lines:
        #for lbl in line:
            #reset_cell(lbl)
            #add_count(cost)
    return found

def check_lines():
    if find_lines():
        return
    add_balls()
    if find_lines():
        return
    if count_empty() == 0:
        show_game_over()

def add_balls():
    count = count_empty()
    count = count if count < n_balls else n_balls
    for n in range(count):
        find = True
        while find:
            row = randrange(0, N)
            col = randrange(0, N)
            find = not is_empty(board[row][col])
        set_ball(board[row][col], line[n].color)
    next_balls()

def next_step(event):
    check_lines()
 
def reset_cell(lbl):
    lbl.selected = False
    lbl.color = -1
    set_image(lbl)

def restart_game(event):
    set_counter(0)
    lbl_game_over.grid_forget()
    for row in range(N):
        for col in range(N):
            reset_cell(board[row][col])
    next_step(None)

def init_board():
    global img_bgr_unselect, img_bgr_select, img_bgr, lbl_counter, lbl_game_over

    assets.append("assets/ball-aqua.png")
    assets.append("assets/ball-blue.png")
    assets.append("assets/ball-green.png")
    assets.append("assets/ball-pink.png")
    assets.append("assets/ball-red.png")
    assets.append("assets/ball-violet.png")
    assets.append("assets/ball-yellow.png")
    
    bgr = ImageTk.Image.open("assets/page-bgr.png")
    #root ? (image = bgr)

    tileset = ImageTk.Image.open("assets/cell-bgr.png")
    img_bgr_unselect = tileset.crop((1, 0, 67, 66))
    img_bgr_select = tileset.crop((1, 69, 67, 135))
    img_bgr = ImageTk.PhotoImage(tileset.crop((1, 0, 67, 66)))

    font="Arial 20"
    lbl_counter = Label(root, font=font)
    lbl_counter.grid(row=1, column=N, columnspan = 3)
    do_step = Button(root, text = "Next Step", font=font)
    do_step.grid(row = 3, column = N, columnspan = 3, sticky = 'nesw')
    do_step.bind("<Button-1>", next_step)
    new_game = Button(root, text = "New Game", font=font)
    new_game.grid(row = 6, column = N, columnspan = 3, sticky = 'nesw')
    new_game.bind("<Button-1>", restart_game)

    for col in range(n_balls):
        lbl = Label(root, borderwidth=0)
        lbl.grid(row = 4, column = N + col, padx=1, pady=1)
        reset_cell(lbl)
        line.append(lbl)
    
    for row in range(N):
        board.append([])
        for col in range(N):
            lbl = Label(root, borderwidth=0)
            lbl.bind("<Button-1>", click_cell)
            lbl.grid(row=row, column=col, padx=1, pady=1)
            reset_cell(lbl)
            board[row].append(lbl)

    lbl_game_over = Label(root, text="Game Over", font="Arial 50")
 
init_board()
next_balls()
restart_game(None)
 
root.mainloop()

```
## Вывод
Я продвинулся в своём знании Python и Tkinter, научился работать с объектами Canvas, Label, Button, создании классов и созданию простейших игр.