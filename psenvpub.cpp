//
//  Pubsub envelope publisher
//  Note that the zhelpers.h file also provides s_sendmore
//
// Olivier Chamoux <olivier.chamoux@fr.thalesgroup.com>

#include "zhelpers.hpp"

int main () {
    //  Prepare our context and publisher
    zmq::context_t context(1);
    zmq::socket_t publisher(context, ZMQ_PUB);
    publisher.bind("tcp://*:5563");

    int do32 = 0;

    while (1) {
        zmq::message_t message(sizeof(int));
	memcpy(message.data(), &do32, sizeof(int));
	publisher.send(message);
	++do32;
    }
    return 0;
}
