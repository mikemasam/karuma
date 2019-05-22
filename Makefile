INSTALL_DIR = ~/bin
APP_NAME = webframework 
src = $(wildcard src/*.cpp src/**/*.cpp)
#src = $(wildcard src/*.cpp)
obj = $(src:.cpp=.o)

#$(ccsrc:.cc=.o)  
libs = 
LDFLAGS = -lrt -lm 
CXXFLAGS = -Wall -g 
#-O2 



$(APP_NAME): $(obj)
	    $(CXX) -o $@ $^ $(LDFLAGS)

clean:
	rm src/*.o src/**/*.o

install: $(APP_NAME)
	mkdir -p $(INSTALL_DIR)
	cp $< $(INSTALL_DIR)/$(APP_NAME)

uninstall:
	rm -f -R $(INSTALL_DIR)/$(APP_NAME)
