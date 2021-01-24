CXX = g++  
CXXFLAGS = -Wall -L. -g 
LDFLAGS = -fPIC -shared 
RM = rm -rf   

all:firewall.exe
firewall:
	$(CXX) ${CXXFLAGS} ${LDFLAGS} string.cpp \
	field.cpp ip.cpp port.cpp  -o libfirewall.so

firewall.exe: firewall
	$(CXX) ${CXXFLAGS} main.cpp -o firewall.exe -lfirewall -linput

clean:
	-${RM} libfirewall.so firewall.exe