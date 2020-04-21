import os 


# Config for 'paths.py' script.


# All paths are defined relative to the DIR variable.
RELATIVE_PATHS = []


# Replace with your own directory.
DIR = ''  
PATHS = [os.path.join(DIR, x) for x in RELATIVE_PATHS]


# The file that you edit and build from.
EDITING_FILE = ''


# Absolute paths of templates.
TEMPLATES = {
    'gcj': ''
}


# Replace with key of TEMPLATES dictionary.
CURRENT_TEMPLATE = 'gcj'

