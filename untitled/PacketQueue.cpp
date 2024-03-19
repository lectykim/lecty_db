//
// Created by root on 24. 3. 14.
//

#include "PacketQueue.h"

#include <utility>
PacketQueue* GPacketQueue = new PacketQueue();
void PacketQueue::Push(const PacketItem& packetItem) {
    _jobs.Push(std::make_shared<PacketItem>(packetItem));
}

void PacketQueue::Execute() {
        std::vector<std::shared_ptr<PacketItem>> jobs;
        _jobs.PopAll(jobs);
        for(auto &job:jobs){
            job->Execute();
        }
}
