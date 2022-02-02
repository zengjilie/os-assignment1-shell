# Exec
1. fork -> exec
2. files (OS perspective) | filedescriper , file pointer
3. pip for redirection
4. pipe : Inter process communication (IPC)
5. Signals


fork: create a child -> exact copy of the parent

```
int main(){
    int cpid;
    char *inString;
    
    while(inString = realine("cmd:)){
        cpid = fork();
        if(cpid == 0){
            execlp (inString, inString, (char *)NULL);
        }else{
            wait()
        }
    }
}
```