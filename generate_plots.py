import sys

import matplotlib.pyplot as plt


def generate_plots(img_name, suffix):
    with open("out/" + img_name + "_histogram_" + suffix.lower() + ".csv", encoding='utf-8') as histogram:
        rows = [row.split(",") for row in histogram.read().splitlines()]
        color_values = [int(row[0]) for row in rows]
        original_frequencies = [int(row[1]) for row in rows]
        new_frequencies = [int(row[2]) for row in rows]

    fig = plt.subplots()
    plt.bar(color_values, original_frequencies, label='Original')
    plt.bar(color_values, new_frequencies, label='Equalized')
    plt.legend()
    plt.xlabel("Color value")
    plt.ylabel("Frequencies")
    plt.title("Histogram (" + suffix + ")")
    plt.savefig(img_name + "_histogram_" + suffix.lower() + "_plot.png")


if __name__ == '__main__':
    if len(sys.argv) != 2:
        raise ValueError("Use: python generate_plots.py [image_name]")

    image_name = sys.argv[1]

    generate_plots(image_name, "Parallel")
    generate_plots(image_name, "Sequential")
