board?=arduino:avr:uno
port?=/dev/ttyACM0

.PHONY: compile

compile:
	arduino-cli compile --fqbn $(board) ./

.PHONY: upload

upload:
	$(MAKE) compile
	sudo arduino-cli upload  --fqbn $(board) -p $(port) ./

.PHONY: clean

clean:
	rm -rf build/*
	rm -f *.hex *.elf