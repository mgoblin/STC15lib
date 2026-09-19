# CLion JetBrains IDE integration

This folder contains files and instructions on how to use CLion for STC15 lib 
development.

# Import STC15 lib as a CMake Project

Clone https://github.com/STC15/stc15-lib.git. 
Use File → New → Project from Version Control → GitHub.
In the dialog that opens, enter the URL of the repository and click "Clone".

On the next step, select an import as a CMake Project.

After importing the project, you should configure the project to use 
SDCC compiler. Open Settings → Build, Execution, Deployment → Toolchains → 
Custom C Compiler. Select the checkbox Use custom compiler (yaml) and in editbox 
select ${Project path}/clion/sdcc_compiler_clion.yaml.

 Now you can compile the project and examples. But code checking is not working correctly.

Goto File → Settings → Language & Frameworks → C/C++ → Clangd. 
Open editbox below "Edit errors and warnings from clang" and add at the end of the list
on new lines.

```
-Dprintf_tiny=printf 
-ffreestanding
```










