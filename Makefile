INSTALL_DIR = ~/bin
APP_NAME = webframework 
src = $(wildcard src/*.cpp src/**/*.cpp)
#src = $(wildcard src/*.cpp)
obj = $(src:.cpp=.o)

#$(ccsrc:.cc=.o)  
libs 			= -lboost_filesystem -lboost_thread -lboost_system -lpthread
LDFLAGS 	= -lrt -lm $(libs)
CXXFLAGS 	= -Wall -g
CXXFLAGS▸+= -std=c++11

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
