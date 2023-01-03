import subprocess

n1 = "frame_"
n2 = "_delay-0.1s.png"
def cvrtNmbr(n):
    strnum = str(n)
    if(n < 10):
        strnum = '0' + strnum
    return strnum

for i in range(31):
    print('\tgameOverFrames.push_back(al_load_bitmap("Assets' + '\\' + '\\' + 'GameOver' + "\\" + '\\' + 'frame' + str(i) + '.png"));')

exit()
for i in range(2, 32+1):
    fName1 = n1 + cvrtNmbr(i) + n2
    fName2 = "frame" + str(i - 2) + ".png"
    subprocess.run(["mv", fName1, fName2])
    subprocess.run(["convert", fName2, "-resize", "700x406", fName2])