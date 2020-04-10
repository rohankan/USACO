import os

DIR = '.'

filenames = (os.path.join(DIR, x) for x in os.listdir(DIR) if x.endswith('.cpp'))
date, recent = max((os.stat(x).st_mtime, x) for x in filenames)

os.system('xcrun clang++ -std=c++11 -stdlib=libc++ ' + recent)

print('Compiled! Enter your input here:')

os.system('./a.out')
