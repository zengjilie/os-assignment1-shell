
Interrupt Vector Table

TRAP Vector Table

TRAP x21
TRAP x25

LC3
| 0x0020 | ----- | TVT |
| ------ |
| 0x0100 | ----- |
| 0x0180 | kb--- | TVT |
| 0x01ff | ----- |

ARM
0x000...|reset| IVT
        |SWI--| IVT -> SWI #5

X86


## Context Save
a. user process 
        | TRAP (save the state of the current program) -> |----| stack
        V supervisor mode
    syscall handler -> service(sub routine) -> LC3(RIT) || ARM(BXLR) || x86() -> RESTORE
        |
        V user mode

b. user process
        ^ Timer Interrupt(SAVE) -> |----| stack
        | 
            Timer handler -> stack pointer points to the next process's stack ->RESTORE

LC3 -> save 2 registers (PC && PSR) 
ARM -> save 8 registers

## Scheduler
Scheduling: given n jobs/processes, decide who goes next

2 Attributes:
a. Execution time
b. Arrival time 

Workload Assumption
1. T_exec(i) = T_exec(j)
2. T_arr(i) = T_arr(j)
3. T_I/O(i) != 0
4. T_exec(i) is known priori

Assessment(metric)
a. Turn around time
    T_comp - T_arr
b. Response time
    T_firstrun - T_arr

### Metric a
example1
    i   T_exec  T_arr
0   A   10      0
1   B   10      0
2   C   10      0

0   10  20  30
|-A-|-B-|-C-|
AvgTRT = 20

example2
    i   T_exec  T_arr
0   A   100     0
1   B   10      0
2   C   10      0

0      100 110 120
|---A---|-B-|-C-|
               

AvgTRT = (100+110+120)/3 = 110

**better** SJF 
pick the shortest job first

0   10  20     120
|-B-|-C-|---A---|
              

AvgTRT = (10+20+120)/3 = 50

example3
    i   T_exec  T_arr
0   A   100     0
1   B   10      10
2   C   10      10

AvgTRT = (100 + (110 - 10) + (120 - 10))/3 = 310/3 = 

Relax "Run to completion" assumption -> prempt a job

0 
|-A-|-B-|-C-|---A---|
A   A90 A90 A90
    B10 C10
    C10

SRTF(shortest remaining time first) -> premptive algorithm
optimal -> wrt TRT && both exec and arr being unequal

TRT as ametric favors short jobs

Metric: b response time
T_firstrun - T_arr = responsetime

    i   T_exec  T_arr
0   A   5       0
1   B   5       0
2   C   5       0

|-A-|-B-|-C-|
0   5   10  5 
AvgResp = (0+5+10)/3 = 5

**Round-Robbin** : assigns a timeslice t_s = 1
|A|B|C|A|B|C|...
0 1 2...
AvgResp = (0+1+2)/3 = 1

RR favors interative jobs

### ALL OSs today use multi-level-feedback queue
level 
0   |_|->|_|->|_| RR in-level
1   |_|->|_| Across level priority based
2
.
.
.
N-1