## Signal

a mechanism of 'event' communication

```
more infloop.c

//this program will run infinatly
int main(){
    while(1);
}

^C -> SIGINT 
```
Every process has signal disposition
- Default
- Ignore
- Specify action

Signal ( <what> <disposition>)
                SIG-IGN | function pointer
 
```
void signit_handler(int sig){
    write(STDOUT_FILENO, "doh\n", 4);
}

int main(){
    signal(SIGINT, sigint_handler);
    while(1);
}

^C -> cann't terminate the program 
kill -TERM pid -> 
```

## Kill

kill is a syscall used to send signals

kill(pid, Signal)

kill (<>, Signal)

if <> is "-", it implies pgid

if <> is "+", it implies pid

```yash

# ./looper
# ^Z -> Stop the cmd, SIGTSTP

# bg -> yash sends looper a signal to continue in background(SIGCONT)

# fg -> yash must give terminal control to looper and wait on it

# kill +pid | -pgid signal -> positive means pid, negative means negative number
```



## Terminal Control
At anytime only one job/process has control over the terminal -> it can read/write to the terminal

A process that does not control the ternimal must not do i/o
if it does, it gets a SIGTTIN or SIGTTOUT

tcsetpgrp(0, pgid (of the group that now owns the terminal))

```
fork()
if(cpid == 0){
    setpgid(0,0);
    exec(...)
}
tcsetpgip(0, cpid);
waitpid( , WUNTRACED);


```




