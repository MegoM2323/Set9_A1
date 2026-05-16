import csv
import os
from collections import defaultdict

import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt

RESULTS = "results.csv"
OUT_DIR = "plots"

ALGOS = [
    ("StandardQuickSort", "tab:red",    "--"),
    ("StandardMergeSort", "tab:orange", "--"),
    ("StringQuickSort",   "tab:blue",   "-"),
    ("StringMergeSort",   "tab:green",  "-"),
    ("MsdRadixSort",      "tab:purple", "-"),
    ("MsdRadixQuickSort", "tab:brown",  "-"),
]
TYPES = [
    ("random",   "Случайный массив"),
    ("reverse",  "Обратно отсортированный"),
    ("almost",   "Почти отсортированный"),
    ("prefixed", "С совпадающими префиксами"),
]


def load():
    data = defaultdict(lambda: defaultdict(lambda: ([], [], [])))
    with open(RESULTS, newline="") as f:
        for row in csv.DictReader(f):
            s, t, c = data[row["array_type"]][row["algorithm"]]
            s.append(int(row["size"]))
            t.append(float(row["time_ms"]))
            c.append(int(row["char_ops"]))
    return data


def grid_plot(data, value_index, ylabel, title, filename, logy=False):
    fig, axes = plt.subplots(2, 2, figsize=(14, 10))
    for ax, (atype, label) in zip(axes.flat, TYPES):
        for algo, color, style in ALGOS:
            series = data[atype][algo]
            sizes = series[0]
            values = series[value_index]
            ax.plot(sizes, values, style, color=color, label=algo, linewidth=1.8)
        ax.set_title(label)
        ax.set_xlabel("Размер массива, строк")
        ax.set_ylabel(ylabel)
        if logy:
            ax.set_yscale("log")
        ax.grid(True, alpha=0.3)
    axes.flat[0].legend(fontsize=9, loc="upper left")
    fig.suptitle(title, fontsize=14)
    fig.tight_layout()
    path = os.path.join(OUT_DIR, filename)
    fig.savefig(path, dpi=130)
    plt.close(fig)
    print("сохранён", path)


def main():
    os.makedirs(OUT_DIR, exist_ok=True)
    data = load()
    grid_plot(data, 1, "Время, мс",
              "Время выполнения сортировок строк", "time.png")
    grid_plot(data, 2, "Посимвольные операции",
              "Количество посимвольных операций", "char_ops.png")
    grid_plot(data, 2, "Посимвольные операции (лог. шкала)",
              "Количество посимвольных операций (логарифмическая шкала)",
              "char_ops_log.png", logy=True)


if __name__ == "__main__":
    main()
