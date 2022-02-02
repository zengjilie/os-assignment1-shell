# Group

files/dir -group  premissions specify who can access the file

## Process group
1.every process belongs to exactly 1 process group(PG)

2. on creation a process inherit the parents' pgid

3. a process can change/create its process group

```
setpgid(pid, pgid) -> sets the PGID of the process specified by pid to pgid.

setpgid(pid, 0) -> create a new PG whose id is the same as the calling process's pid


example:
$ ls | wc
setpgid(0,0) -> use my own pid 

setpgid(0, lpid) -> set the pgid to the left pgid

```
![img](Screen%20Shot%202022-01-30%20at%207.50.45%20PM.png)
