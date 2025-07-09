import os

def main():
    cpp_files = [
        "main.cpp",
        "csvreader.cpp",
        "players.cpp"
    ]

    # Check if all cpp files exist
    missing_files = [f for f in cpp_files if not os.path.isfile(f)]
    if missing_files:
        print(f"Error: Missing files: {', '.join(missing_files)}")
        return

    command = f"g++ {' '.join(cpp_files)} -o main.exe"
    result = os.system(command)
    if result != 0 or not os.path.isfile("main.exe"):
        print("Compilation failed. Please check for errors above or ensure g++ is installed and in your PATH.")
        return
    os.system("main.exe") # use no prefix to run the file on vscode terminal or start for cmd

if __name__ == "__main__":
    main()