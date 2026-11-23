#pragma once
#include <stdint.h>
#include <stddef.h>
namespace lord_sumi {
enum class MeshStatus { Accepted, Duplicate, Invalid, Expired, Full, Fault };
struct MeshPacket { uint16_t source; uint16_t destination; uint32_t sequence; uint8_t hops; uint8_t ttl; };
class MeshDeduplicator {
  struct Entry { uint16_t source; uint32_t sequence; };
  Entry seen_[16]; size_t used_; bool fault_;
public:
  MeshDeduplicator():used_(0),fault_(false){}
  bool fault() const {return fault_;}
  void reset(){used_=0;fault_=false;}
  MeshStatus accept(const MeshPacket& p){
    if(fault_) return MeshStatus::Fault;
    if(!p.source || !p.destination || p.ttl==0 || p.hops>p.ttl){fault_=true;return MeshStatus::Invalid;}
    if(p.hops==p.ttl) return MeshStatus::Expired;
    for(size_t i=0;i<used_;++i) if(seen_[i].source==p.source){
      if(p.sequence<=seen_[i].sequence) return MeshStatus::Duplicate;
      seen_[i].sequence=p.sequence;return MeshStatus::Accepted;
    }
    if(used_==16){fault_=true;return MeshStatus::Full;}
    seen_[used_++]={p.source,p.sequence};return MeshStatus::Accepted;
  }
};
}
