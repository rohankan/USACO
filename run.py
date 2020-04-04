import os

os.system('xcrun clang++ -std=c++11 -stdlib=libc++ main.cpp')

print('Compiled! Enter your input here:')

os.system('./a.out')
