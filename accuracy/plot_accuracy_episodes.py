import numpy as np
import matplotlib.pyplot as plt

def fillplot(ax, color, x, low, high):
    # fill between the two curves
    ax.fill_between(x, low, high, facecolor=color, alpha=0.3)

    # Outline of the filled region
    ax.plot(x, low, c=color, alpha=0.8)
    ax.plot(x, high, c=color, alpha=0.8)

def main():
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

    fillplot(ax, 'red',   x, y1_l, y1_h)
    fillplot(ax, 'green', x, y2_l, y2_h)
    fillplot(ax, 'blue',  x, y3_l, y3_h)
    fillplot(ax, 'gray',  x, y4_l, y4_h)

    plt.savefig("foo.png")

if __name__ == '__main__':
    main()
