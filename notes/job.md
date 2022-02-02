# Job
Shell concept
Process: OS concept
job is a command given to a shell

Job -> STOPPED | RUNNING
Procerss -> Ready | Running | Waiting

```
$ progl | foo | bar > file
```

```
Struct job{
    char jshr[80;]
    int pgid;
    int lpid, rpid;
        Statues: STOPPED | RUNNING
    switch job *next;
};
```

swtich job * jlist;