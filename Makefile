#-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------#
PROG_NAME1=base64decoder
PROG_VERSION1=0.0.6
PROG_NAME2=base64encoder
PROG_VERSION2=0.0.6
PROG_URL=https://github.com/progman/base64codec
#-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------#
CXX=gcc
LN=g++
#-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------#
#-D_FILE_OFFSET_BITS=64 -D_LARGEFILE64_SOURCE
CFLAGS_x32DBG=-m32 -ggdb -pg -pedantic -O0 -std=c++11 -Wall -Wextra -Wlong-long -Wunused
CFLAGS_x32REL=-m32           -pedantic -O3 -std=c++11 -Wall -Wextra -Wlong-long -Wunused
CFLAGS_x64DBG=-m64 -ggdb -pg -pedantic -O0 -std=c++11 -Wall -Wextra -Wlong-long -Wunused
CFLAGS_x64REL=-m64           -pedantic -O3 -std=c++11 -Wall -Wextra -Wlong-long -Wunused
# --analyze
#-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------#
LFLAGS_x32DBG=-m32 -ggdb
LFLAGS_x32REL=-m32 -s
LFLAGS_x64DBG=-m64 -ggdb
LFLAGS_x64REL=-m64 -s
#-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------#
help:
	@echo "use make [x32 | x64 | x32dbg | x64dbg | clean]";
#-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------#
x32dbg: base64decoder.cpp base64encoder.cpp Makefile
	@if [ ! -e bin ]; then    (mkdir bin;)     fi

	@$(CXX) base64.cpp   -c -o bin/base64.o   -D'PROG_NAME="$(PROG_NAME1)"' -D'PROG_VERSION="$(PROG_VERSION1)"' -D'PROG_TARGET="$(@)"' -D'PROG_FULL_NAME="$(PROG_NAME1)-$(@)-$(PROG_VERSION1)"' -D'PROG_URL="$(PROG_URL)"' $(CFLAGS_x32DBG)

	@$(CXX) base64decoder.cpp -c -o bin/base64decoder.o -D'PROG_NAME="$(PROG_NAME1)"' -D'PROG_VERSION="$(PROG_VERSION1)"' -D'PROG_TARGET="$(@)"' -D'PROG_FULL_NAME="$(PROG_NAME1)-$(@)-$(PROG_VERSION1)"' -D'PROG_URL="$(PROG_URL)"' $(CFLAGS_x32DBG)
	@$(LN) bin/base64.o bin/base64decoder.o -o bin/$(PROG_NAME1)-$(@)-$(PROG_VERSION1) $(LFLAGS_x32DBG)
	@ln -sf $(PROG_NAME1)-$(@)-$(PROG_VERSION1) bin/$(PROG_NAME1)
	@objdump -Dslx bin/$(PROG_NAME1)-$(@)-$(PROG_VERSION1) > bin/$(PROG_NAME1)-$(@)-$(PROG_VERSION1).dump;

	@$(CXX) base64encoder.cpp -c -o bin/base64encoder.o -D'PROG_NAME="$(PROG_NAME2)"' -D'PROG_VERSION="$(PROG_VERSION2)"' -D'PROG_TARGET="$(@)"' -D'PROG_FULL_NAME="$(PROG_NAME2)-$(@)-$(PROG_VERSION2)"' -D'PROG_URL="$(PROG_URL)"' $(CFLAGS_x32DBG)
	@$(LN) bin/base64.o bin/base64encoder.o -o bin/$(PROG_NAME2)-$(@)-$(PROG_VERSION2) $(LFLAGS_x32DBG)
	@ln -sf $(PROG_NAME2)-$(@)-$(PROG_VERSION2) bin/$(PROG_NAME2)
	@objdump -Dslx bin/$(PROG_NAME2)-$(@)-$(PROG_VERSION2) > bin/$(PROG_NAME2)-$(@)-$(PROG_VERSION2).dump;
#-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------#
x32:    base64decoder.cpp base64encoder.cpp Makefile
	@if [ ! -e bin ]; then    (mkdir bin;)     fi

	@$(CXX) base64.cpp   -c -o bin/base64.o   -D'PROG_NAME="$(PROG_NAME1)"' -D'PROG_VERSION="$(PROG_VERSION1)"' -D'PROG_TARGET="$(@)"' -D'PROG_FULL_NAME="$(PROG_NAME1)-$(@)-$(PROG_VERSION1)"' -D'PROG_URL="$(PROG_URL)"' $(CFLAGS_x32REL)

	@$(CXX) base64decoder.cpp -c -o bin/base64decoder.o -D'PROG_NAME="$(PROG_NAME1)"' -D'PROG_VERSION="$(PROG_VERSION1)"' -D'PROG_TARGET="$(@)"' -D'PROG_FULL_NAME="$(PROG_NAME1)-$(@)-$(PROG_VERSION1)"' -D'PROG_URL="$(PROG_URL)"' $(CFLAGS_x32REL)
	@$(LN) bin/base64.o bin/base64decoder.o -o bin/$(PROG_NAME1)-$(@)-$(PROG_VERSION1) $(LFLAGS_x32REL)
	@ln -sf $(PROG_NAME1)-$(@)-$(PROG_VERSION1) bin/$(PROG_NAME1)

	@$(CXX) base64encoder.cpp -c -o bin/base64encoder.o -D'PROG_NAME="$(PROG_NAME2)"' -D'PROG_VERSION="$(PROG_VERSION2)"' -D'PROG_TARGET="$(@)"' -D'PROG_FULL_NAME="$(PROG_NAME2)-$(@)-$(PROG_VERSION2)"' -D'PROG_URL="$(PROG_URL)"' $(CFLAGS_x32REL)
	@$(LN) bin/base64.o bin/base64encoder.o -o bin/$(PROG_NAME2)-$(@)-$(PROG_VERSION2) $(LFLAGS_x32REL)
	@ln -sf $(PROG_NAME2)-$(@)-$(PROG_VERSION2) bin/$(PROG_NAME2)
#-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------#
x64dbg: base64decoder.cpp base64encoder.cpp Makefile
	@if [ ! -e bin ]; then    (mkdir bin;)     fi

	@$(CXX) base64.cpp   -c -o bin/base64.o   -D'PROG_NAME="$(PROG_NAME1)"' -D'PROG_VERSION="$(PROG_VERSION1)"' -D'PROG_TARGET="$(@)"' -D'PROG_FULL_NAME="$(PROG_NAME1)-$(@)-$(PROG_VERSION1)"' -D'PROG_URL="$(PROG_URL)"' $(CFLAGS_x64DBG)

	@$(CXX) base64decoder.cpp -c -o bin/base64decoder.o -D'PROG_NAME="$(PROG_NAME1)"' -D'PROG_VERSION="$(PROG_VERSION1)"' -D'PROG_TARGET="$(@)"' -D'PROG_FULL_NAME="$(PROG_NAME1)-$(@)-$(PROG_VERSION1)"' -D'PROG_URL="$(PROG_URL)"' $(CFLAGS_x64DBG)
	@$(LN) bin/base64.o bin/base64decoder.o -o bin/$(PROG_NAME1)-$(@)-$(PROG_VERSION1) $(LFLAGS_x64DBG)
	@ln -sf $(PROG_NAME1)-$(@)-$(PROG_VERSION1) bin/$(PROG_NAME1)
	@objdump -Dslx bin/$(PROG_NAME1)-$(@)-$(PROG_VERSION1) > bin/$(PROG_NAME1)-$(@)-$(PROG_VERSION1).dump;

	@$(CXX) base64encoder.cpp -c -o bin/base64encoder.o -D'PROG_NAME="$(PROG_NAME2)"' -D'PROG_VERSION="$(PROG_VERSION2)"' -D'PROG_TARGET="$(@)"' -D'PROG_FULL_NAME="$(PROG_NAME2)-$(@)-$(PROG_VERSION2)"' -D'PROG_URL="$(PROG_URL)"' $(CFLAGS_x64DBG)
	@$(LN) bin/base64.o bin/base64encoder.o -o bin/$(PROG_NAME2)-$(@)-$(PROG_VERSION2) $(LFLAGS_x64DBG)
	@ln -sf $(PROG_NAME2)-$(@)-$(PROG_VERSION2) bin/$(PROG_NAME2)
	@objdump -Dslx bin/$(PROG_NAME2)-$(@)-$(PROG_VERSION2) > bin/$(PROG_NAME2)-$(@)-$(PROG_VERSION2).dump;
#-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------#
x64:    base64decoder.cpp base64encoder.cpp Makefile
	@if [ ! -e bin ]; then    (mkdir bin;)     fi

	@$(CXX) base64.cpp   -c -o bin/base64.o   -D'PROG_NAME="$(PROG_NAME1)"' -D'PROG_VERSION="$(PROG_VERSION1)"' -D'PROG_TARGET="$(@)"' -D'PROG_FULL_NAME="$(PROG_NAME1)-$(@)-$(PROG_VERSION1)"' -D'PROG_URL="$(PROG_URL)"' $(CFLAGS_x64REL)

	@$(CXX) base64decoder.cpp -c -o bin/base64decoder.o -D'PROG_NAME="$(PROG_NAME1)"' -D'PROG_VERSION="$(PROG_VERSION1)"' -D'PROG_TARGET="$(@)"' -D'PROG_FULL_NAME="$(PROG_NAME1)-$(@)-$(PROG_VERSION1)"' -D'PROG_URL="$(PROG_URL)"' $(CFLAGS_x64REL)
	@$(LN) bin/base64.o bin/base64decoder.o -o bin/$(PROG_NAME1)-$(@)-$(PROG_VERSION1) $(LFLAGS_x64REL)
	@ln -sf $(PROG_NAME1)-$(@)-$(PROG_VERSION1) bin/$(PROG_NAME1)

	@$(CXX) base64encoder.cpp -c -o bin/base64encoder.o -D'PROG_NAME="$(PROG_NAME2)"' -D'PROG_VERSION="$(PROG_VERSION2)"' -D'PROG_TARGET="$(@)"' -D'PROG_FULL_NAME="$(PROG_NAME2)-$(@)-$(PROG_VERSION2)"' -D'PROG_URL="$(PROG_URL)"' $(CFLAGS_x64REL)
	@$(LN) bin/base64.o bin/base64encoder.o -o bin/$(PROG_NAME2)-$(@)-$(PROG_VERSION2) $(LFLAGS_x64REL)
	@ln -sf $(PROG_NAME2)-$(@)-$(PROG_VERSION2) bin/$(PROG_NAME2)
#-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------#
clean:
	@if [ -e bin ]; then    rm -rf bin;    fi
#-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------#
