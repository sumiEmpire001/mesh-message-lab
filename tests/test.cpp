#include "MeshFrame.h"
#include <cstdlib>
#include <iostream>
using namespace mesh;
void check(bool b){if(!b){std::cerr<<"FAIL\n";std::exit(1);}}
int main(){
 Frame f;f.origin=1;f.destination=2;f.sequence=7;f.ttl=3;f.length=3;f.payload[0]=42;f.payload[1]=0;f.payload[2]=255;
 uint8_t data[64]={};auto n=encode(f,data,sizeof(data));check(n==15);
 Frame out;check(decode(data,n,out)&&out.payload[2]==255&&out.sequence==7);
 Deduplicator d;check(d.accept(out)==Result::Accepted&&d.accept(out)==Result::Duplicate);
 check(forward(out)==Result::Accepted&&out.ttl==2);
 check(forward(out)==Result::Accepted&&forward(out)==Result::Expired);
 data[10]^=1;check(!decode(data,n,out));
 check(!decode(data,n-1,out));check(!decode(nullptr,n,out));
 check(encode(f,data,4)==0);f.origin=0;check(!valid(f));
 std::cout<<"mesh tests passed\n";
}
