files/dirs -group
Process group : 
1. Every process(pid) belongs to exactly 1 process group(PG)
2. On creation a process inherits the parents pgid
3. A process can change its process group/create a process group

setpgid(pid, pgid) -> set the process of process whose pid its to pgid

Creat 
Setpgid (pid, null) -> create a new PG whose id it the same as the calling process's pid

```
$ ls | wc

pgid = 425

lpid = 425
ls
setpgid(lpid,0)

rpid = 500
wc
setpgid(0, lpid)

```


