PROGRAMNAME := lilacs
PREFIX := /usr/local
INSTALL_PATH := $(PREFIX)/bin

CMAKE_BUILD_TYPE ?= Debug

PROGRAM=$(addprefix $(BIN_PATH)/, $(PROGRAMNAME))



all: $(PROGRAM)

$(PROGRAM): $(OBJ)
	cmake -D CMAKE_BUILD_TYPE=$(CMAKE_BUILD_TYPE) -D CMAKE_EXPORT_COMPILE_COMMANDS=ON -S src -B cmake/$(CMAKE_BUILD_TYPE) -G Ninja
	cmake --build cmake/$(CMAKE_BUILD_TYPE)


install:
	chmod 755 $(PROGRAM)
	mkdir -p $(BIN_PATH)
	cp $(PROGRAM) $(INSTALL_PATH)/$(PROGRAMNAME)

uninstall:
	rm -f $(INSTALL_PATH)/$(PROGRAMNAME)

clean:
	rm -f $(PROGRAM) 
	rm -f $(OBJ_PATH)/*


.PHONY: all install uninstall clean makedir default
