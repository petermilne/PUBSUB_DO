//
//  Pubsub envelope subscriber
//
// Olivier Chamoux <olivier.chamoux@fr.thalesgroup.com>

#include "zhelpers.hpp"

int main (int argc, char* argv[]) {
    //  Prepare our context and subscriber
    int limit = argc > 1? atoi(argv[1]): -1;
    zmq::context_t context(1);
    zmq::socket_t subscriber (context, ZMQ_SUB);
    subscriber.connect("tcp://localhost:5563");
    subscriber.setsockopt( ZMQ_SUBSCRIBE, "", 0);

    while (limit == -1 || --limit > 0) {
	std::string do32 = s_recv (subscriber);
		
        std::cout << do32 << std::endl;
    }
    return 0;
}
