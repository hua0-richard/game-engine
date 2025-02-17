import sys
import subprocess
import os
import zipfile
import requests
import shutil

def cloneRepo():
    raylibDir = "raylib"
    if os.path.isdir(raylibDir):
        print("Raylib directory already exists! Skipping download...")
        return
    else:
        url = "https://github.com/raysan5/raylib/archive/refs/heads/master.zip"
        output_zip = "raylib.zip"
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
    if sys.platform == 'win32':
        if len(sys.argv) > 1:
            if sys.argv[1] == "clean":
                winresult = subprocess.run('if exist engine\\raylib rmdir /s /q engine\\raylib', shell=True, check=True, text=True, capture_output="True")
                winresult = subprocess.run('if exist build\\main del build\\main', shell=True, check=True, text=True, capture_output="True")
                files_to_delete = ["build\\main.exe", "include\\raylib.h", "lib\\libraylib.a"]
                for file in files_to_delete:
                    subprocess.run(f'if exist {file} del {file}', shell=True, text=True, capture_output=True)
                return
        print('Building on Windows...')
        cloneRepo()
        winresult = subprocess.run("cd raylib\\raylib-master\\src && make", shell=True, check=True, text=True, capture_output="True")
        print(winresult.stdout)
        shutil.copy('raylib/raylib-master/src/libraylib.a', 'engine\\lib')
        shutil.copy('raylib/raylib-master/src/raylib.h', 'engine\\include')
        winresult = subprocess.run("make PLATFORM=WIN", shell=True, check=True, text=True, capture_output="True")
        print(winresult.stdout)
    elif sys.platform == 'darwin':
        if len(sys.argv) > 1:
            if sys.argv[1] == "clean":
                macOSresult = subprocess.run("rm -rf engine/raylib main engine/include/raylib.h engine/lib/libraylib.a build/main build/main.exe", shell=True, check=True, text=True, capture_output="True")
                return
        print('Building on macOS...')
        cloneRepo()
        macOSresult = subprocess.run("cd raylib/raylib-master/src && make", shell=True, check=True, text=True, capture_output="True")
        print(macOSresult.stdout)
        shutil.copy('raylib/raylib-master/src/libraylib.a', 'engine/lib')
        shutil.copy('raylib/raylib-master/src/raylib.h', 'engine/include')
        macOSresult = subprocess.run("make PLATFORM=MAC", shell=True, check=True, text=True, capture_output="True")
        print(macOSresult.stdout)
    else:
        print('Unsupported Operating System')

main()