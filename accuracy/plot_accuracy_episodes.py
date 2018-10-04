import numpy as np
import matplotlib.pyplot as plt

x = [i for i in range(10)]
y1_l = [i/2 for i in x]
y1_h = [i+10 for i in y1_l]
y2_l = [i**2 for i in x]
y2_h = [i+10 for i in y2_l]
y3_l = [1 - i for i in x]
y3_h = [i+10 for i in y3_l]
y4_l = [10 - 5 * i for i in x]
y4_h = [i+10 for i in y4_l]

fig, ax = plt.subplots()

ax.fill_between(x, y1_l, y1_h, facecolor='red', alpha=0.3)
ax.fill_between(x, y2_l, y2_h, facecolor='green', alpha=0.3)
ax.fill_between(x, y3_l, y3_h, facecolor='blue', alpha=0.3)
ax.fill_between(x, y4_l, y4_h, facecolor='gray', alpha=0.3)

# Outline of the region we've filled in
ax.plot(x, y1_l, c='r', alpha=0.8)
ax.plot(x, y1_h, c='r', alpha=0.8)
ax.plot(x, y2_l, c='g', alpha=0.8)
ax.plot(x, y2_h, c='g', alpha=0.8)
ax.plot(x, y3_l, c='b', alpha=0.8)
ax.plot(x, y3_h, c='b', alpha=0.8)
ax.plot(x, y4_l, c='gray', alpha=0.8)
ax.plot(x, y4_h, c='gray', alpha=0.8)
#ax.plot([x[0], x[-1]], [y1[0], y1[-1]], c='b', alpha=0.8)
#ax.plot([x[0], x[-1]], [y2[0], y2[-1]], c='r', alpha=0.8)

plt.savefig("foo.png")
