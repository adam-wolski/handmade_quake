import os

# Setup scons enviroment
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

# Copy build .o files in build directory.
# In paths later specify path like src is in build ex:
#   Instead of ./src/quake.c we will use ./build/quake.c
#
# Files aren't duplicated in there because of duplicate=0 but that's the path
# we need to specify in later references.
ENV.VariantDir(variant_dir='build', src_dir='src', duplicate=0)
ENV.VariantDir(variant_dir='build/tests', src_dir='tests', duplicate=0)

#Sources directory
SDIR = 'src'
#Tests directory
TESTS_DIR = 'tests'

# Create separate ENV.Object objects for all the .c files that are used in
# multiple programs. (Like in quake and tests)
COMMON_SOURCES = [ENV.Object(os.path.join('build', f))
                  for f in os.listdir(SDIR)
                  if f.endswith('.c') and f.find('quake.c') == -1]

# Main program sources
SOURCES = ['build/quake.c']
SOURCES += COMMON_SOURCES

# Test sources
TESTS_SOURCES = [os.path.join('build/tests', f)
                 for f in os.listdir(TESTS_DIR)
                 if f.endswith('.c')]
TESTS_SOURCES += COMMON_SOURCES

#Libraries
L = ['X11', 'rt']
#Library paths
LP = ['/usr/lib', '/usr/local/lib']


# --- Building
ENV.Program('build/quake', SOURCES, LIBS=L, LIBPATH=LP)
ENV.Program('build/tests/test', TESTS_SOURCES, LIBS=L, LIBSPATH=LP)
