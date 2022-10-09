#pragma once

#include <atomic>
#include <cstdint>

namespace tlgs
{

struct Counter
{
    Counter(std::atomic<size_t>& counter)
        : counter_(&counter)
    {
        count_ = counter_->fetch_add(1, std::memory_order_acq_rel);
    }

    Counter(Counter&& other)
    {
        other.counter_ = counter_;
        other.count_ = count_;
        counter_ = nullptr;
    }

    size_t count() const
    {
        return count_;
    }

    ~Counter()
    {
        if(counter_ != nullptr)
            counter_->fetch_sub(1, std::memory_order_acq_rel);
    }

    size_t release()
    {
        if(!counter_)
            return -1;
        size_t n = counter_->fetch_sub(1, std::memory_order_acq_rel)-1;
        counter_ = nullptr;
        count_ = -1;
        return n;
    }

    size_t count_ = -1;
    std::atomic<size_t>* counter_;
};

}
