import subprocess

indices = [11,12,13,14,21,22,23,24,31,32,33,34,35]

for i in indices:
    f1 = "punchRight" + str(i) + ".png"
    f2 = "punchLeft" + str(i) + ".png"
    subprocess.run(["convert", f1, "-flop", f2])
