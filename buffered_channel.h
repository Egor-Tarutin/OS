#pragma once

#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>

template<class T>
class BufferedChannel {
public:
    explicit BufferedChannel(int size) : size(size) {}

    void Send(T value) {
        std::unique_lock<std::mutex> lock(mtx);
        while(!free_space())
            cond_var.wait(lock);

        if (!is_open)
            throw std::runtime_error("Channel is closed, maafaka!");
        buff_queue.push(value);
        if (buff_queue.size() > size)
            is_open = false;
        lock.unlock();
        cond_var.notify_all();
    }

    std::pair<T, bool> Recv() {
        std::unique_lock<std::mutex> lock(mtx);
        while(!is_not_empty())
            cond_var.wait(lock);
        T value = buff_queue.front();
        buff_queue.pop();

        lock.unlock();
        cond_var.notify_all();
        return std::make_pair(value, is_open);
    }

    void Close() {
        std::unique_ptr<std::mutex> lock(mtx);
        is_open = false;
        lock.unlock();
        cond_var.notify_all();
    }

private:

    bool free_space() { return buff_queue.size() < size; }
    bool is_not_empty() { return !buff_queue.empty(); }

    std::mutex mtx;
    bool is_open = true;
    int size;
    std::condition_variable cond_var;
    std::queue<T> buff_queue;
};
