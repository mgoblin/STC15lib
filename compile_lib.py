Import("env")

print("Building stc15 library")

env.SConscript('SConstruct', exports = 'env')
