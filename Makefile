
CXX=arm-linux-gnueabihf-g++
CXXFLAGS+=-I. -I../../../buildroot/output/build/zeromq-4.2.5/include/
CXXFLAGS+=-L../../../buildroot/output/target/usr/lib

all: psenvpub psenvsub

psenvpub:  psenvpub.o
	$(CXX) $(CXXFLAGS) -o $@ $^ -l zmq

psenvsub:  psenvsub.o
	$(CXX) $(CXXFLAGS) -o $@ $^ -l zmq


clean:
	rm -f *.o psenvpub psenvsub

