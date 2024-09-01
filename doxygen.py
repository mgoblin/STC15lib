Import("env")
import os

def post_build_action(source, target, env):
    os.system("doxygen doxygen.conf")

env.AddPostAction("buildprog", post_build_action)    