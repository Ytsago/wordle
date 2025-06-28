build:
	mkdir -p build
	cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -S . -B build
	make -j -C build
	cp build/compile_commands.json .

run: build
	build/wordlegui words.txt

.PHONY: build run
