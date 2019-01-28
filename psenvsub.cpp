//
//  Pubsub envelope subscriber
//
// Olivier Chamoux <olivier.chamoux@fr.thalesgroup.com>

#include "zhelpers.hpp"

int main (int argc, char* argv[]) {
    //  Prepare our context and subscriber
   const char* ch = argc > 1? argv[1]: "";
    zmq::context_t context(1);
    zmq::socket_t subscriber (context, ZMQ_SUB);
    subscriber.connect("tcp://localhost:5563");
   subscriber.setsockopt( ZMQ_SUBSCRIBE, ch, strlen(ch));

    while (1) {
 
		//  Read envelope with address
		std::string address = s_recv (subscriber);
		//  Read message contents
		std::string contents = s_recv (subscriber);
		
        std::cout << "[" << address << "] " << contents << std::endl;
    }
    return 0;
}
