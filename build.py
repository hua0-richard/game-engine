import sys
import subprocess
import os
import zipfile
import requests
import shutil
from pathlib import Path

# Platform-specific commands
COMMANDS = {
    'windows': {
        'clean': (
            "if exist engine\\raylib rmdir /s /q engine\\raylib & "
            "if exist build\\main del build\\main & "
            "if exist build\\main.exe del build\\main.exe & "
            "if exist include\\raylib.h del include\\raylib.h & "
            "if exist lib\\libraylib.a del lib\\libraylib.a"
        ),
        'make_raylib': 'cd engine\\raylib\\raylib-master\\src && make',
        'make_engine': 'make engine PLATFORM=WIN',
        'make_game': 'make game PLATFORM=WIN'
    },
    'darwin': {
        'clean': "rm -rf engine/raylib main engine/include/raylib.h engine/lib/libraylib.a build/main build/main.exe",
        'make_raylib': 'cd engine/raylib/raylib-master/src && make',
        'make_engine': 'make engine PLATFORM=MAC',
        'make_game': 'make game PLATFORM=MAC'
    }
}

def get_platform_commands():
    """Get commands for current platform."""
    if os.name == "nt":
        return COMMANDS['windows']
    elif os.uname().sysname == "Darwin":
        return COMMANDS['darwin']
    return dict.fromkeys(['clean', 'make_raylib', 'make_engine', 'make_game'], '')

def download_raylib():
    """Download and extract raylib if not already present."""
    raylib_dir = Path("engine/raylib")
    if raylib_dir.is_dir():
        print("Raylib directory already exists! Skipping download...")
        return

    url = "https://github.com/raysan5/raylib/archive/refs/heads/master.zip"
    zip_path = Path("engine/raylib.zip")
    
    print("Downloading raylib...")
    response = requests.get(url, stream=True)
    if response.status_code != 200:
        print(f"Failed to download: HTTP {response.status_code}")
        sys.exit(1)
        
    # Download zip file
    with open(zip_path, "wb") as file:
        for chunk in response.iter_content(chunk_size=1024):
            file.write(chunk)
    print(f"Downloaded {zip_path}")
    
    # Extract and cleanup
    extract_dir = zip_path.parent / zip_path.stem
    with zipfile.ZipFile(zip_path, "r") as zip_ref:
        zip_ref.extractall(extract_dir)
    zip_path.unlink()

def run_command(cmd, error_msg="Command failed"):
    """Run a shell command and handle errors."""
    if not cmd:
        return
    try:
        result = subprocess.run(cmd, shell=True, check=True, text=True, capture_output=True)
        if result.stdout:
            print(result.stdout)
    except subprocess.CalledProcessError as e:
        print(f"{error_msg}:")
        print(e.stderr)
        sys.exit(1)

def copy_raylib_files():
    """Copy raylib files to engine directories."""
    src_dir = Path("engine/raylib/raylib-master/src")
    lib_dir = Path("engine/lib")
    include_dir = Path("engine/include")
    
    shutil.copy(src_dir / "libraylib.a", lib_dir)
    shutil.copy(src_dir / "raylib.h", include_dir)

def main():
    # Create necessary directories
    Path('engine/lib').mkdir(parents=True, exist_ok=True)
    Path('engine/include').mkdir(parents=True, exist_ok=True)

    commands = get_platform_commands()
    
    # Handle clean command
    if len(sys.argv) > 1 and sys.argv[1] == "clean":
        run_command(commands['clean'])
        return

    print('Building...')
    download_raylib()
    run_command(commands['make_raylib'], "Failed to build raylib")
    copy_raylib_files()
    run_command(commands['make_engine'], "Failed to build engine")
    run_command(commands['make_game'], "Failed to build game")

if __name__ == "__main__":
    main()