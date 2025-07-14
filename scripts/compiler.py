import os
import subprocess

BASE_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.abspath(os.path.join(BASE_DIR, ".."))

SRC_DIR = os.path.join(PROJECT_ROOT, "source")
INCLUDE_DIR = os.path.join(PROJECT_ROOT, "include")
BUILD_DIR = os.path.join(PROJECT_ROOT, "build")
EXECUTABLE_NAME = "main.exe"
OUTPUT_PATH = os.path.join(BUILD_DIR, EXECUTABLE_NAME)

cpp_files = [
    os.path.join(SRC_DIR, "main.cpp"),
    os.path.join(SRC_DIR, "csvreader.cpp"),
    os.path.join(SRC_DIR, "players.cpp"),
    os.path.join(SRC_DIR, "tournament.cpp"),
    os.path.join(SRC_DIR, "matchmaking.cpp"),
    os.path.join(SRC_DIR, "round.cpp"),
    os.path.join(SRC_DIR, "console_utils.cpp")
]

# Create build folder if missing
if not os.path.exists(BUILD_DIR):
    os.makedirs(BUILD_DIR)

# Build g++ command
compile_command = ["g++", "-std=c++17", "-I", INCLUDE_DIR] + cpp_files + ["-o", OUTPUT_PATH]

# Compile
print("Compiling...")
result = subprocess.run(compile_command, capture_output=True, text=True)

if result.returncode == 0:
    print(f"Compilation successful: {OUTPUT_PATH}")
    subprocess.run(["start", "", OUTPUT_PATH], shell=True) 

else:
    print("Compilation failed:\n")
    print(result.stderr)