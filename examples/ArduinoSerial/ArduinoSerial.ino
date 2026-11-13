#include "../../include/MeshFrame.h"
// Serial loopback demonstration only; no radio transmission.
mesh::Deduplicator seen;
void setup(){Serial.begin(115200);}
void loop(){
 static bool once=false;if(once)return;once=true;
 mesh::Frame f;f.origin=1;f.destination=2;f.sequence=1;f.ttl=3;f.length=2;f.payload[0]='O';f.payload[1]='K';
 uint8_t bytes[64];size_t n=mesh::encode(f,bytes,sizeof(bytes));
 mesh::Frame parsed;
 if(n&&mesh::decode(bytes,n,parsed)&&seen.accept(parsed)==mesh::Result::Accepted)Serial.println("frame validated");
}
