# encoding: utf-8

import matplotlib.pyplot as plt
from collections import defaultdict


def show_cluster(center_num):
    cluster_list = [[] for _ in range(center_num)]
    with open("dataset") as fd:
        for line in fd:
            line = line.strip().split(" ")
            cluster_id = int(line[-1])
            cluster_list[cluster_id].append((float(line[0]), float(line[1])))

    center_list = []
    with open("center_list") as fd:
        for line in fd:
            line = line.strip().split(" ")
            center_list.append((float(line[0]), float(line[1])))

    color_list = ["r", "c", "b", "y", "beige", "coral", "g", "darkmagenta"]
    for i in range(center_num):
        _len = len(cluster_list[i])
        center = center_list[i]
        if _len == 0:
            continue
        x, y = zip(*cluster_list[i])
        plt.scatter(x, y, c=color_list[i], alpha=1)
        plt.scatter([center[0]], [center[1]], s=100, c=color_list[i], alpha=1, marker="v")
        plt.text(center[0], center[1], str(i))

    plt.show()