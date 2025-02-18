import sys
import subprocess
import os
import zipfile
import requests
import shutil

WIN_CLEAN = (
    "if exist engine\\raylib rmdir /s /q engine\\raylib & "
    "if exist build\\main del build\\main & "
    "if exist build\\main.exe del build\\main.exe & "
    "if exist include\\raylib.h del include\\raylib.h & "
    "if exist lib\\libraylib.a del lib\\libraylib.a"
)

WIN_COPY_RAYLIB = 'cd engine\\raylib\\raylib-master\\src && make'
WIN_MAKE_ENGINE = "make engine PLATFORM=WIN"
MAC_MAKE_GAME = "make game PLATFORM=WIN"


MAC_CLEAN = "rm -rf engine/raylib main engine/include/raylib.h engine/lib/libraylib.a build/main build/main.exe"

MAC_COPY_RAYLIB = 'cd engine/raylib/raylib-master/src && make'
MAC_MAKE_ENGINE = "make engine PLATFORM=MAC"
MAC_MAKE_GAME = "make game PLATFORM=MAC"

NONE = ''

def cloneRepo():
    raylibDir = "engine/raylib"
    if os.path.isdir(raylibDir):
        print("Raylib directory already exists! Skipping download...")
        return
    else:
        url = "https://github.com/raysan5/raylib/archive/refs/heads/master.zip"
        output_zip = "engine/raylib.zip"
        print("Downloading raylib...")
        response = requests.get(url, stream=True)
        if response.status_code == 200:
            with open(output_zip, "wb") as file:
                for chunk in response.iter_content(chunk_size=1024):
                    file.write(chunk)
            print(f"Downloaded {output_zip}")
        else:
            print(f"Failed to download: HTTP {response.status_code}")
            exit()
        with zipfile.ZipFile(output_zip, "r") as zip_ref:
            extract_dir = output_zip.replace(".zip", "") 
            zip_ref.extractall(extract_dir)
        os.remove(output_zip)

def main():
    os.makedirs('engine/lib', exist_ok=True)
    os.makedirs('engine/include', exist_ok=True)
    os.makedirs('build', exist_ok=True)
    if len(sys.argv) > 1:
        if sys.argv[1] == "clean":
            result = subprocess.run(WIN_CLEAN if os.name == "nt" else MAC_CLEAN if os.uname().sysname == "Darwin" else NONE, shell=True, check=True, text=True, capture_output="True")
            return
    print('Building...')
    cloneRepo()
    macOSresult = subprocess.run(WIN_COPY_RAYLIB if os.name == "nt" else MAC_COPY_RAYLIB if os.uname().sysname == "Darwin" else NONE, shell=True, check=True, text=True, capture_output="True")
    print(macOSresult.stdout)
    shutil.copy('engine/raylib/raylib-master/src/libraylib.a', 'engine/lib')
    shutil.copy('engine/raylib/raylib-master/src/raylib.h', 'engine/include')
    macOSresult = subprocess.run(WIN_MAKE_ENGINE if os.name == "nt" else MAC_MAKE_ENGINE if os.uname().sysname == "Darwin" else NONE, shell=True, check=True, text=True, capture_output="True")
    macOSresult = subprocess.run(WIN_MAKE_GAME if os.name == "nt" else MAC_MAKE_GAME if os.uname().sysname == "Darwin" else NONE, shell=True, check=True, text=True, capture_output="True")
    print(macOSresult.stdout)

main()