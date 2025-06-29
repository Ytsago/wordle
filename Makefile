build:
	mkdir -p build
	cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -S . -B build
	make -j -C build
	cp build/compile_commands.json .
	mv build/wordlegui wordle

run: build
	build/wordlegui words.txt

clean:
	rm -rf build

.PHONY: build run clean
