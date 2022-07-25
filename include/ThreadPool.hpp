// BSD 3-Clause License

// Copyright (c) 2022, Alex Tarasov
// All rights reserved.

// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:

// 1. Redistributions of source code must retain the above copyright notice, this
//    list of conditions and the following disclaimer.

// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.

// 3. Neither the name of the copyright holder nor the names of its
//    contributors may be used to endorse or promote products derived from
//    this software without specific prior written permission.

// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#pragma once

#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <thread>
#include <mutex>
#include <memory>
#include <vector>
#include <functional>

#include <ThreadSafeQueue.h>
#include <Semaphore.h>
#include <condition_variable>

using namespace std;

/**
 * ThreadPool class creates a pool of threads that pick up and exacute jobs
 * the class will keep the threads alive as long as there is at least one job running or on the queue. 
 * If there are no jobs the queue will close and all threads will stop picking up new tasks and 
 * eventually terminate. scheduling to a queue in this state will throw errors
 */

class ThreadPool
{
private:
    int numThreads = 0;
    void allocateThreads(int num){
        numThreads = num;
        for(int i = 0; i < num; i++){
            threads.emplace_back([this](){
                auto queuePtr = this->tasks;
                auto& queue = *queuePtr;
                auto err = this->errors;

                std::function<void()> task;

                while(queue >> task) {
                    try{
                        // cerr << "got task\n";
                        task();
                    }catch(std::exception& e){
                        err->push(std::runtime_error(e.what()));
                    }catch(...){
                        err->push(std::runtime_error("Unknown exception caught."));
                    }
                    numTasks--;
                    taskChange.notify();
                    // cerr << "task ended\n";
                }
            });
        }
    }

    inline void init(){
        tasks = make_shared<ThreadSafeQueue<std::function<void()>>>();
        errors = make_shared<ThreadSafeQueue<std::runtime_error>>();
    }

    atomic_int32_t numTasks = 0;
    Semaphore taskChange;
    shared_ptr<ThreadSafeQueue<std::function<void()>>> tasks;
    shared_ptr<ThreadSafeQueue<std::runtime_error>> errors;
    vector<thread> threads;
public:
    bool forwardExceptions = true;
    ThreadPool(){
        numThreads = 1;
        init();
    }
    ThreadPool(const ThreadPool& toCpy){
        numThreads = toCpy.numThreads;
        init();
    }
    ThreadPool(int th){
        numThreads = th;
        init();
    }

    inline int getNumThreads(){
        return numThreads;
    }

    inline void schedule(std::function<void()> f){
        numTasks++;
        taskChange.notify();
        tasks->push(f);
    }

    inline void wait(){
        allocateThreads(numThreads);

        while(numTasks > 0) taskChange.wait();
        tasks->close();
        for(auto& t : threads) t.join();
        threads.clear();
        errors->close();

        tasks = make_shared<ThreadSafeQueue<std::function<void()>>>();

        std::runtime_error e("");

        if(forwardExceptions && *errors >> e){
            errors = make_shared<ThreadSafeQueue<std::runtime_error>>();
            throw e;
        }else{
            errors = make_shared<ThreadSafeQueue<std::runtime_error>>();
        }
        
    }
};

#endif // THREAD_POOL_H
