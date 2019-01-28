//
//  Pubsub envelope subscriber
//
// Olivier Chamoux <olivier.chamoux@fr.thalesgroup.com>

#include "zhelpers.hpp"

#include <assert.h>

int main (int argc, char* argv[]) {
    const char* uri = argc > 1? argv[1]: "tcp://localhost:5563"; 
    int limit = argc > 2? atoi(argv[2]): -1;

    std::cout << uri << " limit:" << limit << std::endl;
    zmq::context_t context(1);
    zmq::socket_t subscriber (context, ZMQ_SUB);
    subscriber.connect(uri);
    subscriber.setsockopt( ZMQ_SUBSCRIBE, "", 0);

    int do32;

    while (limit == -1 || --limit > 0) {
    	zmq::message_t message;
	subscriber.recv(&message);
	assert(message.size() == sizeof(int));
	memcpy(&do32, message.data(), sizeof(int));
		
        std::cout << do32 << std::endl;
    }
    return 0;
}
