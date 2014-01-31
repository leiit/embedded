An example to get you started with pre-project
==============================================

This repository is for you to get started. Refer noppa and course wiki (link in noppa) for more information what to do. These files are related to development environment on linux.


Git
---

Git is suggested to be used for project management. It helps you to share core on car-project state and also keeps history of code versions. Remember to tag or branch working version of your code, so when you try to demo on last day, you know which version did work.

You can click `Fork` on [home page](/t-106-5300/example) to fork this project and use this gitlab as git remote. Alternatively you can press [Download](/t-106-5300/example/repository/archive) to get these files.

For more help with git, use the google...


Requirements
------------

All these requirements are fulfilled in exercise lab, so you can skip this part there.

On Windows you need to refer wiki for help. Course assistance do not provide any help with Windows tools or development environments. Actual coding is the same, thus help is provided for that.

With linux based systems (like exercise lab computers) following packages are needed:

debian & ubuntu | description
--- | ---
gcc-avr | Compiler and other utilities
avr-libc | C libraries
avrdude | Used to program the AVR device
yaamake | Required to use `Makefile` (read more below). Packages for yaamake is not yet in distributions repositories so get it from [github source](https://github.com/raphendyr/yaamake)


Files
-----

### .gitignore

This file contains files to be ignored by git. These files are build result and other binary files. You shouldn't ever but this type of files in git.

### Makefile

`Makefile` contains definitions and rules for `make` program. We use `yaamake` to do all the heavy lifting so our `Makefile` is quite sort. Some more information and configuration variables can be show with `make help`.

When you change the `simpleled.c` filename to something else or add another source file, you need to edit `SRC` line in this file.

### Makefile.alternative

This another makefile is not used, but is provided as alternative. If you want to use this instead the other, then rename this to `Makefile` (overwrite the other file). If you dom't want to replace the other you could run `make -f Makefile.alternative` in place of `make`.

You would use this version if you don't want to or can't use yaamake or if there seems to be problem with it yaamake.

### simpleled.c

Example source file to show you the most basic things. This is far from complete solution for pre-project, but works for testing the development environment.


Yaamake makefile usage
----------------------

Makefile uses yaamake makefile system to simplify things. Yaamake contains all the information how to do things and `Makefile` only configurations for them.

### Actions

command | description
--: | ---
`make` | runs `make build`
`make build` | compiles and links your source files
`make clean` | removes all build files (created by above command)
`make program_check` | validate that avr device is connected and is programmable
`make program` | program the AVR board (remember to connect the usb cable first)
`make help` | yaamake's help message about these commands and variables to be defined in `Makefile`
`make listen` | can be used to open serial listener (can be used to listen serial bytes send from your avr program. For that you need to implement USART functions. google `avr usart`)


### Created files

All of this files are more or less useless to you. Basically these are used to get your code to the actual aVR device. You get rid of these by running `make clean`

This files are listed here, to give some reference.

command | description
--: | ---
`simpleled.elf` | Binary in ELF format (result of compiling and linking)
`simpleled.hex` | Binary in hex format (raw binary bytes as hex). This is used to program the device.
`simpleled.lss` | Disassembly (assembly code matched to your c code) Some what human readable, compared to elf and hex.
`simpleled.map` | Object map
`simpleled.sym` | Symbol map
`.cache/*` | Build support files (object files, dependencies, etc.)


Alternative makefile
--------------------

Alternative makefile is easy to extend, but offers less features. It is totally sufficient to pass the project.

### Actions

command | description
--: | ---
`make` | compiles and links your source files
`make clean` | removes all build files (created by above command)
`make program_check` | validate that avr device is connected and is programmable
`make program` | program the AVR board (remember to connect the usb cable first)
`make sizedummy` | prints some size statistics of your binary

### Created files

command | description
--: | ---
`simpleled.elf` | same as above
`simpleled.hex` | same as above
`simpleled.d` | source file dependencies for Makefile
`simpleled.o` | compiled source file (object file)
