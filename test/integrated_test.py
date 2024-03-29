import subprocess
import os

def check_condition(cond: bool):
    if not cond:
        raise RuntimeError("Error when checking")
    return True

def main():
    if not os.path.isdir("../build"):
        raise RuntimeError("I can't see build dir")
    
    if not os.path.exists("../build/lru_cache"):
        raise RuntimeError("I can't see lru_cache exe file")
    
    subprocess.run(['../build/lru_cache'])

    file = open('output.txt')
    lines = file.readlines()
    check_condition(lines[0] == 'A=1\n')
    check_condition(lines[1] == 'B=1\n')
    check_condition(lines[2] == 'C=1')
    print("Tests passed...")

if __name__ == '__main__':
    main()