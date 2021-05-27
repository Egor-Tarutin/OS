#include <iostream>
#include <unistd.h>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    std::string processes[] { "./A","./P","./M","./S" };
    std::cout << "Stop is \'17\'\nEnter Numbers:\n";
    int p[3];
    int pid = 0;
    for (int i = 0; i < 3; i++) {
        pipe(p);
        pid = fork();
        if (!pid) {
            dup2(p[1], 1);
            execlp(processes[i].c_str(), processes[i].c_str(), NULL);
            exit(0);
        }
        dup2(p[0],0);
        close(p[1]);
    }
    execlp(processes[3].c_str(), processes[3].c_str(), NULL);

    exit(0);
    return 0;


}