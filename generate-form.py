import os

final = ""

for file in os.listdir("src"):
    with open(os.path.join("src", file), "r") as f:
        final += file + ": \n" + f.read() + "\n\n"

for file in os.listdir("include"):
    with open(os.path.join("include", file), "r") as f:
        final += file + ": \n" + f.read() + "\n\n"

with open("full-source.txt", "w") as f:
    f.write(final.strip())