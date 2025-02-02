compiler = clang++
frameworks = -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL
flags = $(frameworks) -std=c++23 -Iinclude -Llib -Wall -Wextra -lraylib
sources = $(wildcard src/*.cpp)
output = snake
app_name = Snake.app

define info_plist
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
<plist version="1.0">
    <dict>
        <key>CFBundleExecutable</key>
        <string>$(output)</string>
    </dict>
</plist>
endef

snake:
	$(compiler) $(flags) $(sources) -o $(output)

export info_plist
app:
	rm -rf $(app_name)
	mkdir $(app_name)
	mkdir $(app_name)/Contents
	mkdir $(app_name)/Contents/MacOS
	mkdir $(app_name)/Contents/MacOS/assets
	mkdir $(app_name)/Contents/MacOS/Resources
	echo "$$info_plist" > $(app_name)/Contents/MacOS/Info.plist
	cp -r assets $(app_name)/Contents/MacOS

	$(compiler) $(flags) $(sources) -o $(app_name)/Contents/MacOS/$(output)

clean:
	rm -f $(output)
	rm -rf $(app_name)
