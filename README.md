# ThreadPool
c++ / cpp Thread Pool designed to reduce thread creation overhead

See src/main.cpp for example usage.

```c++
#include <iostream>
#include <ThreadPool.hpp>

using namespace std;

int main(){
    ThreadPool tp(2);
    tp.schedule([](){
        cout << "hello\n";
        throw 1;
    });
    tp.schedule([](){cout << "world\n";});
    tp.schedule([](){cout << "1\n";});
    tp.schedule([](){cout << "2\n";});
    tp.schedule([](){cout << "3\n";});
    tp.forwardExceptions = false;
    tp.wait();
    return 0;
}
```


The makefile will build and run the main file. (modify the main file to try out the library)


To use this project with a dependency manager install the cpp-dependency-manager project from https://github.com/TAR-ALEX/Cpp-Dependency-Manager.git

and create a vendor.txt file and add the following entries:

```
git "https://github.com/TAR-ALEX/Semaphore.git" main "./include" "./vendor/include",
git "https://github.com/TAR-ALEX/Thread-Safe-Queue.git" main "./include" "./vendor/include",
git "https://github.com/TAR-ALEX/io_tools.git" master "./include" "./vendor/include",
git "https://github.com/TAR-ALEX/ThreadPool.git" master "./include" "./vendor/include",
```

