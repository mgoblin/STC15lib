import os

from SCons.Script import SConscript

Import("env")

print("Building utils")

env.SConscript('utils/SConstruct', exports = 'env')

print("Build utils finished")