import os
import matplotlib.pyplot as plt
import numpy as np

x_arr = []
for i in range(50):
    x_arr.append(1)
    x_arr.append(2)
    x_arr.append(5)
    x_arr.append(10)

x = np.array(x_arr)


os.system("make")

my_list = ["1", "2", "5", "10"]
y_axis = []
for i in range(50):
    for no in my_list:
        os.system("./myprogram.o 1000 " + no)
        my_file = open("output"+no+".txt", "r")
        y_axis.append(float(my_file.readlines()[-1]))

y = np.array(y_axis)
plt.scatter(x, y)
plt.title("Number of integers = 50")
plt.show()