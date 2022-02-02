# Lab1
POSIX calls 

Application -> Syscalls -> OS -> Hardware

-fork
-open
-read
-write

params should either be -> int | pointer

fork -> syscall(44, __ ) -> |4| | | 
open -> syscall(13, "file name", O_RD_WR ) -> | o_rd_wr | file(pointer) | 13 | | |
-> returns a file descriptor(fd)

syscall -> performs a TRAP -> pushes all the inputs to the stack

TRAP handler determines what should be pop out of the stack

## Operating System in 3 easy pieces

manage CPU | Disk | Memory
 
-Virtualization 
-> CPU (scheduling)
-> Memory (virtual) -> a machine 4gb RAM can run program that requires > 4 GB of RAM 

-Concurrency
-> multi-threading -> a process creates mutliple threads
-> Race conditions | semaphore | condition variables
 
-Persistence
-> filesystems crash recovery

## Example(CPU scheduling)

X86 

BIOS
-> runs
-> loads sector 0 of the boot media (mini loader) and runs it -> (hard drive(setor 0), master boot run)
-> mini loader loads a bigger loader(GRUB:linux) -> allows you choce either win/linux you want to load
-> linux image -> OS | filesystem
-> launches INIT -> login demon...

On Reset

|OS| | | Reset

ARM
intereact table

## OS

OS Manages 
-> IVT(syscall handler)
-> TVT(syscall)


x30 -> software IVT
x86 -> TRAP
ARM -> SWI

OS runs processes
requirements:
1. a protection -> from each other | from accessing os resources -> mode: user | supervisor
2. control -> os never gives up control of the system by using a Timer

Limited Direct Execution

OS @ boot
-> initialize trap table 
-> hardware remember address of syscall handler
-> start interrupt timer -> hardware start timer interrupt CPU X ms


OS @ run(kernel mode)
-> return from trap
-> restore regs from kernel stack move to user mode jump to main -> run main() -> call system trap into OS
-> save regs to kernel stack move to kernel mode jump to trap handler 
-> handle trap do work of syscall return-from-trap -> restore regs from kernel stack move to user mode jump to PC after trap -> return from main

LC3
RTI
-> pops 2 elements PC and PSR

ARM
ISR -> BXLR
-> |R0|R3|R12|LR|PC|PSR|

x86
return from trap

launch a program
OS -> push PC:eip(instruction pointer) to stack -> PC points to main
|main:code of the program|

## multiple processes

Process A -> timer went off -> OS gets control -> changes the stack pointer to B -> return-from-trap
Process B ->  

context switch: measures the performance of an OS
-> PA -> saves state of PA -> restores state of PB : context switch time
-> PB -> save state of PB -> restores state of PA 
-> OS


