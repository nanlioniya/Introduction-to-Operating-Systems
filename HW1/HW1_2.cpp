#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<iostream>

using namespace std;

int main(){
    pid_t pid;
    cout<<"Main Process ID: "<<getpid()<<"\n";


    if(!fork()){ //fork1
        cout<<"Fork 1. I'm the child "<<getpid()<<
        ", my parent is "<<getppid()<<"\n";

        if(!fork()){//fork2
            cout<<"Fork 2. I'm the child "<<getpid()<<
            ", my parent is "<<getppid()<<"\n";
            
            if(!fork()){//fork3
                cout<<"Fork 3. I'm the child "<<getpid()<<
                ", my parent is "<<getppid()<<"\n";
            }
            else{
                wait(NULL);
            }
        }
        else{
            wait(NULL);
        }
    }
    else{
        
        wait(NULL);
        if(!fork()){ //fork4
            cout<<"Fork 4. I'm the child "<<getpid()<<
            ", my parent is "<<getppid()<<"\n";
        }
        else{
            wait(NULL);
            if(!fork()){ //fork6
            cout<<"Fork 6. I'm the child "<<getpid()<<
            ", my parent is "<<getppid()<<"\n";
            }
        }
        
        wait(NULL);
        if(!fork()){ //fork5
            cout<<"Fork 5. I'm the child "<<getpid()<<
            ", my parent is "<<getppid()<<"\n";
        }
    }

    return 0;
}