import os

from SCons.Script import SConscript

Import("env")

print("Add examples to build configuration")

env.SConscript('examples/SConstruct', exports = 'env')
#env.Execute(['cd examples ; scons ; rm -rf build'])