import os

ENV = Environment(CC='clang',
                  CCFLAGS=['-g',
                           '-std=c11',
                           '-Wall',
                           '-Wextra',
                           '-Wpedantic',
                           '-Wshadow',
                           '-Wstrict-overflow',
                           '-fno-strict-aliasing',
                           '-O2'
                          ])

# Set the include paths
ENV.Append(CPPPATH=['src', 'tests'])

ENV.VariantDir(variant_dir='build', src_dir='src', duplicate=0)
ENV.VariantDir(variant_dir='build/tests', src_dir='tests', duplicate=0)

#Sources directory
SDIR = 'src'
#Tests directory
TESTS_DIR = 'tests'

# Add build to the path so the .o files aren't created in source folder.
SOURCES = [os.path.join('build', f)
           for f in os.listdir(SDIR)
           if f.endswith('.c')]

TESTS_SOURCES = [os.path.join('build/tests', f)
                 for f in os.listdir(TESTS_DIR)
                 if f.endswith('.c')]

TESTS_SOURCES += SOURCES
#Remove quake.c from TESTS_SOURCES as we don't want the duplication of main.
for s in TESTS_SOURCES:
    if s.find('quake.c') > -1:
        TESTS_SOURCES.remove(s)
        break

#Libraries
L = ['X11', 'rt']
#Library paths
LP = ['/usr/lib', '/usr/local/lib']


ENV.Program('build/quake', SOURCES, LIBS=L, LIBPATH=LP)
ENV.Program('build/tests/test', TESTS_SOURCES, LIBS=L, LIBSPATH=LP)
