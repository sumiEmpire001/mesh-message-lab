#include "core.hpp"
#include <cassert>
int main(){lord_sumi::MeshQueue q; lord_sumi::Frame f{1,2,7,3,"hello"};assert(q.ingest(f)==lord_sumi::MeshQueue::Accepted);assert(q.ingest(f)==lord_sumi::MeshQueue::Duplicate);lord_sumi::Frame out{};assert(q.forward(out)&&out.ttl==2);assert(!q.forward(out));f.ttl=0;assert(q.ingest(f)==lord_sumi::MeshQueue::Invalid);}