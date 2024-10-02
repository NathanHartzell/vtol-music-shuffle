import os

path = "YOUR_PATH_HERE"
prefix = "vtol_"

for filename in os.listdir(path):
    if(filename.endswith(".mp3") and filename.startswith(prefix)):
        start = len(prefix) + 4
        src = path + filename
        dst = path + filename[start:]

        os.rename(src, dst)
    