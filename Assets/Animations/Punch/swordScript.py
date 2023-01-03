import subprocess

beginName1 = "attackRight1"
beginName2 = "attackRight2"
beginName3 = "attackRight3"

leftName1 = "attackLeft1"
leftName2 = "attackLeft2"
leftName3 = "attackLeft3"

for i in range(6):
    f1 = beginName1 + str(i) + ".png"
    f2 = leftName1 + str(i) + ".png"
    subprocess.run(["convert", f1, "-resize", "100x74", f1])
    subprocess.run(["convert", f1, "-flop", f2])

for i in range(4):
    f1 = beginName2 + str(i) + ".png"
    f2 = leftName2 + str(i) + ".png"
    subprocess.run(["convert", f1, "-resize", "100x74", f1])
    subprocess.run(["convert", f1, "-flop", f2])

for i in range(7):
    f1 = beginName3 + str(i) + ".png"
    f2 = leftName3 + str(i) + ".png"
    subprocess.run(["convert", f1, "-resize", "100x74", f1])
    subprocess.run(["convert", f1, "-flop", f2])