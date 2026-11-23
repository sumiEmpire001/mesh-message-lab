#include "MeshMessage.h"
#include <cassert>
using namespace lord_sumi;
int main(){
 MeshDeduplicator d;
 assert(d.accept({1,2,1,0,4})==MeshStatus::Accepted);
 assert(d.accept({1,2,1,0,4})==MeshStatus::Duplicate);
 assert(d.accept({1,2,2,1,4})==MeshStatus::Accepted);
 assert(d.accept({2,1,1,4,4})==MeshStatus::Expired);
 assert(d.accept({0,1,1,0,4})==MeshStatus::Invalid);
 assert(d.fault());
 assert(d.accept({3,1,1,0,4})==MeshStatus::Fault);
 d.reset();assert(d.accept({3,1,1,0,4})==MeshStatus::Accepted);
 for(unsigned i=4;i<=18;++i) assert(d.accept({(uint16_t)i,1,1,0,4})==MeshStatus::Accepted);
 assert(d.accept({19,1,1,0,4})==MeshStatus::Full);
}
