
from tkinter import *
import requests
import json
 
url0 = "http://api.openweathermap.org/data/2.5/weather?q=Simferopol&units=metric&appid=e77a594c893b3114f6e35c0c3aab4509"


def change(event):
    load()


def load():
    # load weather
    # data = {"name":"Simf","weather":"Cloudy","temp":10}
    response = requests.get(url0)
    data = response.json()
    city['text'] = data["name"]
    weather['text'] = data["weather"][0]["main"]
    t = data["main"]["temp"] 
    # add +
    temp['text'] = "{}℃".format(t)
 
 
root = Tk()

city = Label(text="City",
                width=50, height=5)
city.pack()
weather = Label(text="-",
                width=50, height=5)
weather.pack()
temp = Label(text="-", 
             width=50, height=10, 
             bg='black', fg='white')
temp.pack()

load()

root.bind('<Button-1>', change)

root.mainloop()