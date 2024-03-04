import shutil
from zipfile import ZipFile
import os

with ZipFile('mkbundle.zip', 'w') as z:
    z.write('build/HuskyMod.bin')
    z.write('flash-list.json')

shutil.move('mkbundle.zip', 'build/mkbundle.kfpkg')
