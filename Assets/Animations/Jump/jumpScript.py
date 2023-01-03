import subprocess

beginName = "adventurer-jump-0"
endName = "-1.3.png"

for i in range(4):
    f1 = beginName + str(i) + endName
    f2 = "jumpSwordRight" + str(i) + ".png"
    subprocess.run(["mv", f1, f2])
    subprocess.run(["convert", f2, "-resize", "100x74", f2])
    f3 = "jumpSwordLeft" + str(i) + ".png"
    subprocess.run(["convert", f2, "-flop", f3])