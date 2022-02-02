# Files

fd = open("foo", O_RDWR | O_RDONLY | O_WRONLY | O_CREAT)
write(fd, "hi", 3)

file descriptor: handle that the OS returns for the user program to refer to the file 

PCB 
-pid
-status
-stack pointer
-file descriptor table

0 -> stdin
1 -> stdout
2 -> stderr
3 -> fd -> OS -> Disk


## dup

duplicate file descriptor talbe entries

dup2(oldfd, newfd)
close newfd
copies contentso fo oldfd to newfd

