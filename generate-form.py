import os

final = ""

for file in os.listdir("src"):

    if file not in ["ge_dialogue.cpp"]:

        with open(os.path.join("src", file), "r") as f:
            final += file + ": \n" + f.read() + "\n\n"

for file in os.listdir("include"):

    if file not in ["ge_map_data.h"]:

        with open(os.path.join("include", file), "r") as f:
            final += file + ": \n" + f.read() + "\n\n"

with open("full-source.txt", "w") as f:
    f.write(final.strip())