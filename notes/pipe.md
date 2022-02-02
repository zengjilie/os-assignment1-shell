# Pipe

is a uni-directional communication channel between related processes
parent - child | child - child
    
```
int pfd[2];

pipe(pfd)

pfd[0]
pfd[1]

$ ls | wc

pgid = 425

lpid = 425
ls
setpgid(lpid,0)

rpid = 500
wc
setpgid(0, lpid)

```

ls | wc -> ls stdout point to wc stdin
ls > wc -> write ls to a file called wc

name pipes