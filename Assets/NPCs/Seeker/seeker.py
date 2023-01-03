import subprocess

names = ["attack", "damage", "death", "idle", "walk"]

for i in range(len(names)):
    f1 = names[i] + "Right.png"
    f2 = names[i] + "Left.png"
    subprocess.run(["convert", f1, "-flop", f2])
