import subprocess

for i in range(13):
    filename = "damage" + str(i) + ".png"
    filenameRight = "damageRight" + str(i) + ".png"
    filenameLeft = "damageLeft" + str(i) + ".png"
    subprocess.run(["mv", filename, filenameRight])
    subprocess.run(["convert", filenameRight, "-flop", filenameLeft])
# convert original.png -resize 100x100 new.png