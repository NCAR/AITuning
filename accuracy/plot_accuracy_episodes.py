import numpy as np
import matplotlib.pyplot as plt
import argparse, re

def fillplot(ax, color, x, low, high, legend):
    # fill between the two curves
    ax.fill_between(x, low, high, facecolor=color, alpha=0.3)

    # Outline of the filled region
    ax.plot(x, low, c=color, alpha=0.8, label=legend)
    ax.plot(x, high, c=color, alpha=0.8)

def check_consistency(old, new, filename, old_episode):
    if not old is None:
        if ("episodes=" in new and "episodes=" in old):
            edited_new = re.sub("episodes=[0-9]*", "episodes="+str(old_episode), new)
        else:
            edited_new = new
        if old != edited_new:
            print("Problem in input file", filename, "gotten")
            print(new)
            print("while it was expected either (old)")
            print(old)
            print("Note that edited_new is")
            print(edited_new)
            raise Exception()
    return new

def parse(line, var):
    data = line.split("[")[1].replace("]", "").replace(",", " ")
    for i, datum in enumerate(data.split()):
        var[i].append(float(datum))

def append_episode(episodes, line):
    episode = -1
    if "episodes=" in line:
        m = re.search("episodes=[0-9]*", line)
        episode_str = re.sub("episodes=", "", m.group(0))
        episode = int(episode_str)
    if not episode in episodes:
        episodes.append(episode)

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('filenames', type=str, nargs='+', help='files to plot')
    args = parser.parse_args()

    conf = None
    target = None
    episodes = []
    target_values = [[], [], [], []]
    median = [[], [], [], []]
    mean = [[], [], [], []]
    max_acc = [[], [], [], []]
    min_acc = [[], [], [], []]
    stddev = [[], [], [], []]
    for fn in args.filenames:
        with open(fn) as f:
            for line in f:
                if line.startswith("Configuration Namespace"):
                    append_episode(episodes, line)
                    if len(episodes) == 1:
                        use_episode = -1
                    else:
                        use_episode = -2
                    conf = check_consistency(conf, line, fn, episodes[use_episode])
                if line.startswith("Target values: "):
                    target = check_consistency(target, line, fn, episodes[-1])
                    parse(line, target_values)
                if line.startswith("Relative accuracy (median):"):
                    parse(line, median)
                if line.startswith("Relative accuracy (mean):"):
                    parse(line, mean)
                if line.startswith("Relative accuracy (stddev):"):
                    parse(line, stddev)
                if line.startswith("Relative accuracy (max):"):
                    parse(line, max_acc)
                if line.startswith("Relative accuracy (min):"):
                    parse(line, min_acc)

    fig, ax = plt.subplots()
    print(target.strip())
    print(conf.strip())
    for i in range(len(target_values)):
        print("Max accuracty for target   ", set(target_values[i]), max_acc[i]) # , len(max_acc[0]))
        print("Min accuracty for target   ", set(target_values[i]), min_acc[i]) # , len(max_acc[0]))
        print("Median accuracty for target", set(target_values[i]), median[i]) # , len(max_acc[0]))
        print("Mean accuracty for target  ", set(target_values[i]), mean[i]) # , len(max_acc[0]))
        print("Stddev accuracty for target", set(target_values[i]), stddev[i]) # , len(max_acc[0]))
    print("episodes", episodes) #, len(episodes))

    colors = ['red', 'green', 'blue', 'gray']
    for i in range(len(target_values)):
        fillplot(ax, colors[i],   episodes, min_acc[i], max_acc[i], set(target_values[i]))
        ax.plot(episodes, median[i], c=colors[i], alpha=0.8)
    ax.legend(title="target parameter")
    plt.ylim(-2, 2)
    plt.xlabel('episodes')
    plt.ylabel('relative accuracy (1=100% error)')
    plt.title("Accuracy with " + re.search("noise_level=[0-9]*", conf).group(0) + '%')
    plt.savefig("foo.png")

if __name__ == '__main__':
    main()
