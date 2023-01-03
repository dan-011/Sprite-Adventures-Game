import subprocess

beginName = "adventurer-idle-2-0"

for i in range(4):
    f1 = beginName + str(i) + ".png"
    f2 = "idleRightSword" + str(i) + ".png"
    subprocess.run(["mv", f1, f2])
    subprocess.run(["convert", f2, "-resize", "100x74", f2])
    f3 = "idleLeftSword" + str(i) + ".png"
    subprocess.run(["convert", f2, "-flop", f3])