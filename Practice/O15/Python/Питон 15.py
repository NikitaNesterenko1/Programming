import random

while True:
    secret = int(random.random() * 101)
    win = False

    print("введите  догадку")

    for i in range(5):
        guess = int(input())
        if guess > secret:
            print("число меньше")
        elif guess < secret:
            print("число больше")
        else:
            print("вы выиграли!")
            win = True
            break

    if not win:
        print("вы проиграли. Загаданное число:", secret)

    if not 1 == int(input("хотите начать сначала? \n")):
        break