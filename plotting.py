import os
import matplotlib.pyplot as plt
import numpy as np

number_of_execution = 100
array_size = "40000"
thread_list = ["0", "1", "2", "5", "10"]
y_axis = []
x_axis = []

for i in range(number_of_execution):
    x_axis.append(0)
    x_axis.append(1)
    x_axis.append(2)
    x_axis.append(5)
    x_axis.append(10)
x = np.array(x_axis)


os.system("make")


for i in range(number_of_execution):
    for num_thread in thread_list:
        os.system(f"./myprogram.o {array_size} {num_thread}")
        cur_file = open(f"output{num_thread}.txt", "r")
        y_axis.append(float(cur_file.readlines()[-1]))

y = np.array(y_axis)

plt.scatter(x, y)
plt.xlabel("Number of threads")
plt.ylabel("Execution time")
plt.title("Array size = " + array_size)
plt.show()
