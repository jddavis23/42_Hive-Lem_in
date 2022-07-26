#!/usr/bin/python

from Tkinter import *
import sys
import re
from random import randint

if __name__ == '__main__':

    if len(sys.argv) == 2:
        fname = sys.argv[1]
    else:
        print('Error!')
        exit(1)
    window = Tk()
    window.title("LEM-IN VISUALIZER")
    canvas = Canvas(window, background = 'lavender')
    canvas.pack(fill = BOTH, expand = YES)
    fd = open(fname, 'r')
    data = fd.read()
    start = re.findall('##start\n\w+ ', data)
    nds = re.findall('\w+ \d+ \d+', data)
    lnks = re.findall('\w+-\w+', data)
    w = re.findall('L1-\w+', data)
    nodes = {}
    links = []
    way = []
    for i in start:
        x = i.split('\n')
        x = x[1].split()
        way.append(x[0])
    for i in w:
        x = i.split('L1-')
        way.append(x[1])
    for node in nds:
        if not '#' in node:
            x = node.split()
            nodes[x[0]] = (int(x[1]) * 50, int(x[2]) * 50) ## {room1 : (x1, y1), room2: (x2, y2), ...}
    for link in lnks:
        if not '#' in link:
            x  = link.split('-')
            if not 'L' in link:
                links.append(x)
    for i in links:
        n1 = nodes[i[0]]
        n2 = nodes[i[1]]
        canvas.create_line(n1[0], n1[1], n2[0], n2[1], width = 3, fill = 'lightslategray')
    for i, j in nodes.items():
        canvas.create_oval(j[0] - 20, j[1] - 20,
            j[0] + 20, j[1] + 20, fill = 'darkslateblue', outline = 'darkslateblue')
        canvas.create_text(j[0] + 20, j[1] + 20, text = i, font="Times 10 italic bold", fill = 'black')
    for i in way:
        n1 = nodes[i]
        canvas.create_oval(n1[0] - 20, n1[1] - 20, n1[0] + 20, n1[1] + 20, fill = 'khaki', outline = 'gold')
    window.mainloop()