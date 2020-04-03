# import os

# print("Enter the input code.")

# contents = []
# try:
# 	while True:
# 	    try:
# 	        line = input()
# 	    except EOFError:
# 	        break

# 	    contents.append(line)
# except KeyboardInterrupt:
# 	pass

# with open('input.txt', 'w') as f:
# 	f.write('\n'.join(contents))

# os.system('g++ -o main main.cpp && ./main input.txt')
# c++ -o ./output.txt main.cpp && ./output.txt input.txt


with open('main.cpp', 'r') as f:
	lines = f.readlines()

from pyperclip import copy

lines = ['#include <bits/stdc++.h>\n'] + lines[19:]
lines = [x for x in lines if "freopen" not in x]


program = ''.join(lines)

print(program)
copy(program)

print('Copied!')
