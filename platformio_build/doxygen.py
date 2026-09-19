Import("env")
import os

def post_build_action(source, target, env):
    print("Generating Doxygen documentation")
    os.system("doxygen doxygen.conf")
    print("Generating Doxygen documentation finished")

env.AddPostAction("buildprog", post_build_action)    