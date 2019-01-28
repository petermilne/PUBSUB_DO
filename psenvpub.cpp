//
//  Pubsub envelope publisher
//  Note that the zhelpers.h file also provides s_sendmore
//
// Olivier Chamoux <olivier.chamoux@fr.thalesgroup.com>

#include "zhelpers.hpp"

int main (int argc, const char* argv[]) {
    const char* uri = argc > 1? argv[1]: "tcp://*:5563";
    int limit = argc > 2? atoi(argv[2]): -1;

    std::cout << "publish " << uri << std::endl;

    //  Prepare our context and publisher
    zmq::context_t context(1);
    zmq::socket_t publisher(context, ZMQ_PUB);
    publisher.bind(uri);

    int do32 = 0;

    while (1) {
        zmq::message_t message(sizeof(int));
	memcpy(message.data(), &do32, sizeof(int));
	publisher.send(message);
	++do32;
    }
    return 0;
}
