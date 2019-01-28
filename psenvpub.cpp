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
	char buf[80]; sprintf(buf, "%d", do32++);
        s_send (publisher, buf);
    }
    return 0;
}
