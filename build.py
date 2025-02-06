import sys
import subprocess
import os
import zipfile
import requests
import shutil

def cloneRepo():
     # Specify the directory path
    raylibDir = "/raylib"

    # Check if the directory exists
    if os.path.isdir(raylibDir):
        print("raylib directory already exists")
        return
    else:
        url = "https://github.com/raysan5/raylib/archive/refs/heads/master.zip"
        output_zip = "raylib.zip"
        print("downloading raylib...")
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
    os.makedirs('lib', exist_ok=True)
    os.makedirs('include', exist_ok=True)
    if sys.platform == 'win32':
        if len(sys.argv) > 1:
            if sys.argv[1] == "clean":
                try:
                    winresult = subprocess.run('rmdir /s /q raylib include lib', shell=True, check=True, text=True, capture_output="True")
                except Exception as e:
                    print(e)
                    None
                return
        print('windows')
        cloneRepo()
        winresult = subprocess.run("cd raylib\\raylib-master\\src && make", shell=True, check=True, text=True, capture_output="True")
        print(winresult.stdout)
        shutil.copy('raylib/raylib-master/src/libraylib.a', 'lib')
        shutil.copy('raylib/raylib-master/src/raylib.h', 'include')
        winresult = subprocess.run("make PLATFORM=WIN", shell=True, check=True, text=True, capture_output="True")
        print(winresult.stdout)
    elif sys.platform == 'darwin':
        if len(sys.argv) > 1:
            if sys.argv[1] == "clean":
                macOSresult = subprocess.run("rm -rf raylib main include lib", shell=True, check=True, text=True, capture_output="True")
                return
        print('macOS')
        cloneRepo()
        macOSresult = subprocess.run("cd raylib/raylib-master/src && make", shell=True, check=True, text=True, capture_output="True")
        print(macOSresult.stdout)
        macOSresult = subprocess.run("cp raylib/raylib-master/src/libraylib.a lib", shell=True, check=True, text=True, capture_output="True")
        print(macOSresult.stdout)
        macOSresult = subprocess.run("cp raylib/raylib-master/src/raylib.h include", shell=True, check=True, text=True, capture_output="True")
        print(macOSresult.stdout)
        macOSresult = subprocess.run("make PLATFORM=MAC", shell=True, check=True, text=True, capture_output="True")
        print(macOSresult.stdout)
    else:
        print('none')

main()