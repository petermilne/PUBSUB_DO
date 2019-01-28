//
//  Pubsub envelope subscriber
//
// Olivier Chamoux <olivier.chamoux@fr.thalesgroup.com>

#include "zhelpers.hpp"

#include <assert.h>

// /mnt/local/mmap --fill_incr=0 --writel -f /dev/mem -l 0x10000 -M $base --offset $reg
//

#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

volatile unsigned *reg32;

unsigned getenv_default(const char* key, unsigned def) {
	const char* val = getenv(key);
	if (val){
		fprintf(stderr, "%s := %s\n", key, val);
		return strtoul(val, 0, 0);
	}else{
		return def;
	}
}

void mmap32()
{
    const char* fname = 	"/dev/mem";
    unsigned length = 		getenv_default("POKE_MAP_LEN", 0x10000);
    unsigned map_offset = 	getenv_default("POKE_MAP_OFFSET", 0x40010000);

    unsigned reg = 		getenv_default("POKE_MAP_REG", 0x1000);
    int open_mode = O_RDWR;
    int mmap_mode = PROT_READ|PROT_WRITE;
    int fd;

    if ( (fd = open( fname, open_mode)) < 0 ){
        fprintf( stderr, "mmap: failed to open device \"%s\" - ", fname );
        perror( "" );
        exit(1);
    }

    void *region = mmap( NULL, length, mmap_mode, MAP_SHARED, fd, map_offset);
    if ( region == (caddr_t)-1 ){
        perror( "mmap" );
        exit(1);
    }
    reg32 = ((volatile unsigned*)region + reg/sizeof(int));
}



int main (int argc, char* argv[]) {
    const char* uri = argc > 1? argv[1]: "tcp://localhost:5563"; 
    int limit = argc > 2? atoi(argv[2]): -1;

    std::cout << uri << " limit:" << limit << std::endl;
    zmq::context_t context(1);
    zmq::socket_t subscriber (context, ZMQ_SUB);
    subscriber.connect(uri);
    subscriber.setsockopt( ZMQ_SUBSCRIBE, "", 0);

    int do32;

    mmap32();
    while (limit == -1 || --limit > 0) {
    	zmq::message_t message;
	subscriber.recv(&message);
	assert(message.size() == sizeof(int));
	memcpy(&do32, message.data(), sizeof(int));
	*reg32 = do32;
		
//        std::cout << do32 << std::endl;
    }
    return 0;
}
