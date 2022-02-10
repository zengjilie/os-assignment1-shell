## Scheduling

MLFQ

level = priority
High

level
0 -> |_|->|_|->|_|
1 -> |_|->|_|
2
.
.
.
N-1

Low

**Motivation :** Do good by both metrics
Metrics:

1. Turn around time -> favor short jobs
2. Response time -> favor interactie jobs

MLFQ Schedular:

1. If Priority(A) > Priority(B), A runs (B doesn't)
2. If Priority(A) = Priority(B), A & B run in RR -> timeslice
3. When a job enters the system, it is placed at the highest priority
4. Once a job used up its time allotment(slice) at a given level (regardless of how many times it has given up the CPU -> perform I/O),its priority is reduced(i.e., it moves down on queue)
5. Priority boost: periodic reset -> all processes start back at highest priority 'S'

interactive jobs perform I/O

2 Problems

1. Degrades to RR to lowest level
2. No accomodation for changing in behavior

**Game the system** (classic MLFQ)
when I/O is performed, your timeslice is reset -> hard to accounting, maintain timing inside PCB
Solution -> perform true accounting, cumulative time use at a given level

`
main(){
    work() -> timeslice
    i/o()
}
`
## In Practice
Solaris
-Boost is customizable(default 30s)
-Each level had a different TS(timeslice:10ms)
Pick a job -> O(n)

Linux
-O(1)

BSD
-Priority Mathmatical function
cp = a*recent_runtime + (1-a)*runtime_sofar


## Process Launch

`
main(int argc, char*argv[]){

}
`
ls -l foo

stack 4 bytes
     |return address|
     |3| -> argc
     |0xbff-ffe4| ->argv
ffe4 |0xbff-fff6| ->argv[0]
ffe8 |0xbff-fff9| ->argv[1]
ffec |0xbff-fffc| ->argv[2]
fff0 |null      | ->argv[3]
fff4 |00-ls     | -> 00 paddings
fff8 |\0-l\0    |
fffc |foo\0     |
c000 |end       | -> SYS-BASE

Address space of a process

0x000...|code| -> code
        |heap| -> bass
0xc00...|stack| ->
0xfff...|OS|

timer_handler(){
    choose B  
    return from TRAP
}

A
|C| <- timer
|S|
|H|


B
|C|
|S|
|H|


## Virtual address space

0x000   |code| a -> x 
        |code| b -> y 
        |code| c -> z
0x0ff   |code| d -> w
0xc00   |heap| 
        |stack| 
0xfff...|OS|

OS Maintain
All addresses generates by a process are virtual
PageTable(map virtual memory to physical memory)
Hardware uses the table to convert virtual code to 



