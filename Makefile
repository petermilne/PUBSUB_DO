
all: psenvpub psenvsub

psenvpub:  psenvpub.o
	$(CXX) -o $@ $^ -l zmq

psenvsub:  psenvsub.o
	$(CXX) -o $@ $^ -l zmq


clean:
	rm -f *.o psenvpub psenvsub

