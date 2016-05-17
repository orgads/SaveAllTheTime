# Save All The Time QtCreator Plugin
![Alt text](doc/img/saveallthetime_screenshot.png?raw=true "Screenshot")

## Overview
This plugin will "Save All" your modified documents every second (or whatever interval you choose).
This was inspired by the continuous save feature in JetBrain's IDEs.

## Installation
Unpack the packaged dynamic library file into the QtCreator plugins directory.

#### Mac

    cd ~/Applications/Qt\ Creator\ 4.0.0/Qt\ Creator.app/Contents/PlugIns/
    && unzip ~/Downloads/saveallthetime-1.0.0_qtcreator-4.0.0_osx-10.11.zip

## Usage
From the menubar you can toggle it with Tools > Save All The Time.
If every second is too frequent for you, then set another interval
from the settings panel in Preferences > Save All The Time.

## Building
Get the QtCreator source package for the version you're targeting, such as 4.0.0.
Unpack it, build it, and make a test copy of the build.
Start the newly built QtCreator (not the test copy).
Then load the plugin .pro file, go to Projects > Run, set Executable to the test copy
build of QtCreator, and then build it to generate a .dylib file.
Running the plugin from the IDE will spawn your test QtCreator with the plugin loaded.

#### Building QtCreator

    VER=4.0.0 cd /tmp
    && wget https://github.com/qtproject/qt-creator/archive/v$VER.zip
    && unzip qt-creator-$VER.zip
    && mkdir build
    && cd build
    && qmake -r ../qt*$VER
    && make -j 4
    && cp -r . ../qt-creator-$VER-test

    # Now build the plugin with the build directory version of the IDE.
    open ./bin/Qt\ Creator.app/Contents/MacOS/Qt\ Creator

    # The executing test IDE, however, will be something like
	# /tmp/qt-creator-4.0.0-test/bin/Qt Creator.app/Contents/MacOS/Qt Creator

Details on building QtCreator are at http://wiki.qt.io/Building-Qt-Creator-from-Git.

## License
Public Domain

