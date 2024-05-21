#!/usr/bin/env python

from matplotlib import pyplot as plt
from sys import argv

import csv

file = argv[1]
outfile = argv[2]
x_index = int(argv[3])
y_index = int(argv[4])
# file = "../build/data1.csv"
# outfile = "../images/img1.png"
# x_index = 0
# y_index = 3
print(f"{file=}")
print(f"{outfile=}")
print(f"{x_index=}")
print(f"{y_index=}")

x = list()
y = list()
header = list()

with open(file, "r") as f:
    csv_reader = csv.reader(f)
    header = next(csv_reader)
    for row in csv_reader:
        x.append(float(row[x_index]))
        y.append(float(row[y_index]))

plt.xlabel(header[x_index])
plt.ylabel(header[y_index])
plt.plot(x, y)
plt.savefig(outfile, bbox_inches='tight')

