import config
import shutil
import sys


if __name__ == '__main__':
    args = sys.argv[1:]
    
    if args[0] == 'r':  # Read
        shutil.copyfile(config.PATHS[int(args[1])], config.EDITING_FILE)
    elif args[0] == 'w':  # Write
        shutil.copyfile(config.EDITING_FILE, config.PATHS[int(args[1])]) 
        shutil.copyfile(config.TEMPLATES[config.CURRENT_TEMPLATE], config.EDITING_FILE)
    elif args[0] == 'o':  # Override
        key = config.CURRENT_TEMPLATE if len(args) == 1 else args[1]
        shutil.copyfile(config.TEMPLATES[key], config.EDITING_FILE) 
    elif args[0] == 'c':  #  Temporary copy
        name = '/'.join(config.EDITING_FILE.split('/')[:-1] + ['temp' + args[1]])
        shutil.copyfile(config.EDITING_FILE, name)

