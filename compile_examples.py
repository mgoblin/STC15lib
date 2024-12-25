import os

from SCons.Script import SConscript

Import("env")

print("Building examples")

env.SConscript('examples/SConstruct', exports = 'env')

print("Build examples finished")