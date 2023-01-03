import subprocess

def convertNmbr(n):
    strnum = str(n)
    if(n < 10):
        strnum = '0' + strnum
    return strnum

beginName = "frame_"
endName = "_delay-0.2s.png"
# delay is 0.2s
# resize to 100x100

for i in range(16):
    f1 = beginName + convertNmbr(i) + endName
    f2 = "flamingSword" + str(i) + ".png"
    subprocess.run(["convert", f1, "-resize", "100x100", f1])
    subprocess.run(["mv", f1, f2])
for i in range(15, -1, -1):
    f1 = "flamingSword" + str(i) + ".png"
    f2 = "flamingSword" + str(31 - i) + ".png"
    subprocess.run(["cp", f1, f2])