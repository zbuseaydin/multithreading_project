import os
import matplotlib.pyplot as plt
import numpy as np

x_arr = []
for i in range(100):
    x_arr.append(1)
    x_arr.append(2)
    x_arr.append(5)
    x_arr.append(10)

x = np.array(x_arr)


os.system("make")

my_list = ["1", "2", "5", "10"]
y_axis = []
for i in range(100):
    for no in my_list:
        os.system("./myprogram.o 10000 " + no)
        my_file = open("output"+no+".txt", "r")
        y_axis.append(float(my_file.readlines()[-1]))

y = np.array(y_axis)

plt.scatter(x, y)
plt.xlabel("Number of threads")
plt.ylabel("Execution time")
plt.title("Array size = 10000")
plt.show()