import os
import re

Import("env")

print("Building examples")

env.SConscript('examples/SConstruct', exports = 'env')

print("Build examples finished")

