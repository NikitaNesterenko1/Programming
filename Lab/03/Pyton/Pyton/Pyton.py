from tkinter import *
from PIL import Image, ImageTk
from random import randrange, shuffle
 
root = Tk()
board = []
buffer = []
N = 9
colors = 0
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
    
def in_search(i, j, buffer):
    return buffer[i][j] == 0

# проверяем содержимое ячейки
def check_empty_cell(i, j, buffer):
    if i < 0 or j < 0 or i >= N or j >= N:
        return False
    if in_search(i, j, buffer):
        if is_empty(board[i][j]):
            buffer[i][j] = 1
            return True
        else :
            buffer[i][j] = 2
    return False

# проверяем пустые ячейки вокруг текущей
def check_empty(i, j, buffer):
    found = False
    search = [[1,0],[0,1],[-1,0],[0,-1]]
    for n in search:
        if check_empty_cell(i+n[0], j+n[1], buffer):
            found = True

    buffer[i][j] = 2
    return found

# ищем путь между двумя ячейками
def find_path(source, target):
    buffer =  [[0 for i in range(N)] for j in range(N)]
    buffer[source.row][source.col] = 1
    find = True
    while find:
        find = False
        for i in range(N):
            for j in range(N):
                if buffer[i][j] == 1:
                    if target.row == i and target.col == j:
                        return True
                    if check_empty(i, j, buffer):
                        find = True
    return False

def show_game_over():
    global lbl_game_over
    lbl_game_over.grid(row=int(N/2-1), column=1, rowspan=3, columnspan=N-2)

def set_count(count):
    global lbl_counter

    lbl_counter.counter = count
    lbl_counter.config(text="Count: {}".format(count))

def add_count(count):
    global lbl_counter
    set_count(lbl_counter.counter + count)
    
# очищаем ячейки в лиинии, подсчитываем очки
def found_line(line):
    for lbl in line:
        reset_cell(lbl)
        add_count(cost)

# ПРОВЕРЯЕМ НАЙДЕНА ЛИ ЛИНИЯ
def check_line(line, lines):
    if len(line) >= line_balls:
        lines.append(line.copy())
        # считаем и убираем шарики как только нашли
        found_line(line)

def check_cell(lbl, line, lines):
    if is_empty(lbl):
        check_line(line, lines)
        line.clear()
    elif len(line) == 0 or lbl.color == line[len(line)-1].color:
        # собираем  не больше 5 шариков
        if len(line) < 5:
            line.append(lbl)
    else:
        check_line(line, lines)
        line.clear()
        line.append(lbl)

# ищем линии из 5 шариков
def find_lines():
    lines = []
    # поиск линий по вертикалям
    buffer = [[],[],[],[]]
    for i in range(N-line_balls+1):
        for j in range(N-i):
            check_cell(board[i+j][j], buffer[0], lines)
            check_cell(board[i+j][N-1-j], buffer[1], lines)
            check_cell(board[j][i+j], buffer[2], lines)
            check_cell(board[j][N-1-i-j], buffer[3], lines)
        for line in buffer:
            check_line(line, lines)
            line.clear()

    # поиск линий по вертикалям и горизонталям 
    buffer = [[],[]]
    for i in range(N):
        for j in range(N):
            check_cell(board[i][j], buffer[0], lines)
            check_cell(board[j][i], buffer[1], lines)
        for line in buffer:
            check_line(line, lines)
            line.clear()

    found = len(lines) > 0
    # подсчет и очитка - но сейчас это происходит раньше
    for line in lines:
        found_line(line)
    return found
 
def reset_cell(lbl):
    lbl.selected = False
    lbl.color = -1
    set_image(lbl)

def check_lines():
    if find_lines():
        return
    add_balls()
    if find_lines():
        return
    if count_empty() == 0:
        show_game_over()

# подсчет пустых ячеек
def count_empty():
    count = 0
    for row in range(N):
        for col in range(N):
            if is_empty(board[row][col]):
                count+=1
    return count

def add_balls():
    count = count_empty()
    count = count if count < n_balls else n_balls
    for n in range(count):
        find = True
        while find:
            row = randrange(0, N)
            col = randrange(0, N)
            find = not is_empty(board[row][col])
        set_ball(board[row][col], buffer[n].color)
    next_balls()
            
def next_balls():
    for col in range(n_balls):
        set_ball(buffer[col], randrange(0, colors))

def click_cell(event):
    global current_cell

    lbl = event.widget
    if lbl.selected:
        # сбрасываем текущую ячейку
        lbl.selected = False
        current_cell = None
    else:
        if current_cell:
            if is_empty(lbl) and not is_empty(current_cell):
                if not find_path(current_cell, lbl):
                    return
                # передвигаем шарик
                lbl.color = current_cell.color
                reset_cell(current_cell)
                current_cell = None
                set_image(lbl)
                check_lines()
            else:
                # меняем текущую ячейку
                lbl.selected = True
                current_cell.selected = False
                set_image(current_cell)
                current_cell = lbl
                set_image(lbl)
        else:
            # устанавливаемтекущую ячейку
            lbl.selected = True
            current_cell = lbl
            set_image(lbl)

def next_step(event):
    check_lines()

def restart_game(event):
    global current_cell

    set_count(0)
    lbl_game_over.grid_forget()
    next_balls()
    current_cell = None
    for row in range(N):
        for col in range(N):
            reset_cell(board[row][col])
    next_step(None)

def init_board():
    global img_bgr_unselect, img_bgr_select, lbl_counter, lbl_game_over, colors

    assets.append("assets/ball-aqua.png")
    assets.append("assets/ball-blue.png")
    assets.append("assets/ball-green.png")
    assets.append("assets/ball-pink.png")
    assets.append("assets/ball-red.png")
    assets.append("assets/ball-violet.png")
    assets.append("assets/ball-yellow.png")
    colors = len(assets)
    
    bgr = ImageTk.Image.open("assets/page-bgr.png")
    #root.config(image = bgr)

    tileset = ImageTk.Image.open("assets/cell-bgr.png")
    img_bgr_unselect = tileset.crop((1, 0, 67, 66))
    img_bgr_select = tileset.crop((1, 69, 67, 135))

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
        buffer.append(lbl)
    
    for row in range(N):
        board.append([])
        for col in range(N):
            lbl = Label(root, borderwidth=0)
            lbl.bind("<Button-1>", click_cell)
            lbl.grid(row=row, column=col, padx=1, pady=1)
            lbl.row = row
            lbl.col = col
            board[row].append(lbl)

    lbl_game_over = Label(root, text="Game Over", font="Arial 50")
 
init_board()
restart_game(None)
 
root.mainloop()
