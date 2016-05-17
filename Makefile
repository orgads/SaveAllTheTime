VER=1.0.0
IDE_VER=4.0.0
MAC_VER=10.11
PLUGINS_DIR="/Users/$(USER)/projects/qtcreator/qt-creator-$(IDE_VER)-test/bin/Qt Creator.app/Contents/PlugIns"
ZIP_MAC=/tmp/saveallthetime-$(VER)_qtcreator-$(IDE_VER)_mac-$(MAC_VER).zip

all: help

help:
	@echo make [clean run-mac zip-mac]

clean:
	rm -rf build/*

zip-mac:
	cd $(PLUGINS_DIR) && zip $(ZIP_MAC) libSaveAllTheTime.dylib

run-mac:
	open ~/projects/qtcreator/build/bin/Qt\ Creator.app/Contents/MacOS/Qt\ Creator
