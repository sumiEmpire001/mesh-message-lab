#pragma once
#include <cstdint>
#include <cstddef>
#include <cstring>
namespace mesh {
constexpr size_t MaxPayload=48;
struct Frame {uint16_t origin=0,destination=0,sequence=0;uint8_t ttl=0,length=0;uint8_t payload[MaxPayload]={};};
enum class Result {Accepted, Invalid, Duplicate, Expired, Full};
inline uint16_t crc16(const uint8_t* p,size_t n){uint16_t crc=0xffff;for(size_t i=0;i<n;++i){crc^=uint16_t(p[i])<<8;for(int j=0;j<8;++j)crc=uint16_t((crc&0x8000)?(crc<<1)^0x1021:crc<<1);}return crc;}
inline bool valid(const Frame& f){return f.origin!=0&&f.destination!=0&&f.length<=MaxPayload&&f.ttl>0;}
class Deduplicator {
 public:
 Result accept(const Frame& f){
  if(!valid(f))return Result::Invalid;
  for(size_t i=0;i<count_;++i)if(origin_[i]==f.origin&&seq_[i]==f.sequence)return Result::Duplicate;
  origin_[next_]=f.origin;seq_[next_]=f.sequence;next_=(next_+1)%Capacity;if(count_<Capacity)++count_;
  return Result::Accepted;
 }
 private:
 static const size_t Capacity=16;
 uint16_t origin_[Capacity]={},seq_[Capacity]={};size_t count_=0,next_=0;
};
inline Result forward(Frame& f){if(!valid(f))return Result::Invalid;if(f.ttl<=1)return Result::Expired;--f.ttl;return Result::Accepted;}
inline size_t encode(const Frame& f,uint8_t* out,size_t cap){
 if(!valid(f)||!out||cap<size_t(f.length)+12)return 0;
 out[0]=0xA5;out[1]=1;
 out[2]=uint8_t(f.origin>>8);out[3]=uint8_t(f.origin);
 out[4]=uint8_t(f.destination>>8);out[5]=uint8_t(f.destination);
 out[6]=uint8_t(f.sequence>>8);out[7]=uint8_t(f.sequence);
 out[8]=f.ttl;out[9]=f.length;
 std::memcpy(out+10,f.payload,f.length);
 uint16_t crc=crc16(out,10+f.length);
 out[10+f.length]=uint8_t(crc>>8);out[11+f.length]=uint8_t(crc);
 return size_t(f.length)+12;
}
inline bool decode(const uint8_t* data,size_t n,Frame& output){
 if(!data||n<12||n>MaxPayload+12||data[0]!=0xA5||data[1]!=1)return false;
 uint8_t len=data[9];if(len>MaxPayload||n!=size_t(len)+12)return false;
 uint16_t actual=crc16(data,n-2),expected=uint16_t(data[n-2]<<8)|data[n-1];
 if(actual!=expected)return false;
 Frame f;f.origin=uint16_t(data[2]<<8)|data[3];f.destination=uint16_t(data[4]<<8)|data[5];
 f.sequence=uint16_t(data[6]<<8)|data[7];f.ttl=data[8];f.length=len;
 std::memcpy(f.payload,data+10,len);if(!valid(f))return false;output=f;return true;
}
}
