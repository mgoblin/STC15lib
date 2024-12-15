import os

Import("env")

print("Add examples to build configuration")

env.Execute(['cd examples ; scons ; rm -rf build'])