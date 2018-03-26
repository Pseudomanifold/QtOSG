[![Build Status](https://travis-ci.org/Submanifold/QtOSG.svg?branch=master)](https://travis-ci.org/Submanifold/QtOSG) [![CII Best Practices](https://bestpractices.coreinfrastructure.org/projects/1074/badge)](https://bestpractices.coreinfrastructure.org/projects/1074)

# QtOSG: combining Qt and OSG in a thread-safe manner

This repository contains a widget based on `QOpenGLWidget` that is able
to wrap a viewer from the [OpenSceneGraph](http://www.openscenegraph.org) library.
This makes it possible to combine both toolkits in a thread-safe manner.

Moreover, the widget demonstrates several interaction mechanisms:

1. Rectangular selection processing
2. Pick handling
3. Node file writing (for debug purposes)

# Requirements

* Linux or MacOS X (see below for a brief discussion on supporting
  Microsoft Windows)
* A recent C++ compiler with support for C++11
* `CMake` (minimum version 2.8.11)
* `Qt5`
* `OpenSceneGraph`

## What about Microsoft Windows

I am not familiar enough with graphics programming for Microsoft Windows
to fully support this as a target platform. In [issue 7](https://github.com/Submanifold/QtOSG/issues/7), it was briefly
discussed that some modifications are required for QtOSG to fully
compile/work under Microsoft Windows. If you want to target this
platform, I would be glad for the help!

Thanks to [Martial Tola](https://github.com/mtola), support for
compiling under Microsoft Windows has been added to the project
and I am looking forward to any comments.

# Building QtOSG

    $ git clone https://github.com/Submanifold/QtOSG
    $ cd QtOSG
    $ mkdir build
    $ cd build
    $ cmake ../
    $ make

Additional build options can be configured by issuing `ccmake .` in the
build directory. In particular, you can toggle the following options:

* `WITH_PICK_HANDLER`: toggle to compile with/without support for point
  picking
* `WITH_SELECTION_PROCESSING`: toggle to compile with/without support
  for rectangular selections

# Using QtOSG

The demo application merely demonstrates basic usage of the widget.
Don't expect too much! Start the application by issuing `./qtosg` in the
build directory.

The following key bindings are active:

* `d`: writes the current scene graph to `/tmp/sceneGraph.osg`
* `h`: resets the view to home 
* `s`: toggles selection processing (if compiled); if active, hold left
  mouse button down to draw a selection rectangle; selected objects will
  be shown on the console

# How to contribute

Please see the [contribution guidelines](CONTRIBUTING.md) for more
information and a list of the contributors.

# Licence

`QtOSG` uses the MIT licence. Pleas see the file
[LICENSE.md](LICENSE.md) in the main directory of the repository for
more information.
