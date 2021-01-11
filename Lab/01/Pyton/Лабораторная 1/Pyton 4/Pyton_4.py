
# вывод текущей погоды 
from tkinter import *
import requests
import json
 
url0 = "http://d4fbcacda726.ngrok.io/raw"


def change(event):
    load()


def load():
    # load weather
    # data = {"name":"Simf","weather":"Cloudy","temp":10}
    response = requests.get(url0)
    data = response.json()
    city['text'] = data["name"]
    weather['text'] = data["weather"][0]["main"]
    t = data["temp"] 
    # add +
    temp['text'] = "{}℃".format(t)
 
 
root = Tk()

city = Label(text="City",
                width=30, height=5, 
             bg='yellow', fg='black')
city.pack()
weather = Label(text="-",
                width=30, height=1, 
             bg='yellow', fg='black')
weather.pack()
temp = Label(text="-", 
             width=30, height=10)
temp.pack()

load()

root.bind('<Button-1>', change)

root.mainloop()