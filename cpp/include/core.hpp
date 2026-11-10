#pragma once
#include <cstddef>
#include <cstdint>
#include <cstring>
namespace lord_sumi {
struct Frame { uint16_t source, destination, sequence; uint8_t ttl; char payload[33]; };
class MeshQueue {
 Frame slots_[8]{}; size_t count_=0; uint16_t seenSource_[8]{}; uint16_t seenSeq_[8]{}; size_t seenCount_=0;
public:
 enum Result { Accepted, Duplicate, Invalid, Full };
 Result ingest(const Frame& f) {
  if (!f.source || !f.destination || !f.ttl || f.ttl>16 || !std::memchr(f.payload,0,sizeof f.payload)) return Invalid;
  for(size_t i=0;i<seenCount_;++i) if(seenSource_[i]==f.source && seenSeq_[i]==f.sequence) return Duplicate;
  if(count_==8 || seenCount_==8) return Full;
  slots_[count_++]=f; seenSource_[seenCount_]=f.source; seenSeq_[seenCount_++]=f.sequence; return Accepted;
 }
 bool forward(Frame& out) {
  if(!count_) return false;
  out=slots_[0]; for(size_t i=1;i<count_;++i) slots_[i-1]=slots_[i]; --count_;
  if(out.ttl<=1) return false;
  --out.ttl; return true;
 }
 size_t pending() const { return count_; }
 void reset() { count_=seenCount_=0; }
};
}