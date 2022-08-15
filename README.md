# Fast-File-Duplication
This is a program for operating systems class
In this program, we duplicate a huge file (1GB) on tmpfs, a RAM-based file system, to focus on the OS-level overhead rather than the storage latency

## Objectives
* Understand the overheads involved in file operations
* Exploit kernel primitives to avoid (or to reduce) these overheads

## Overhead of file reading/writing
* Switching from the user mode to the kernel mode
* Copying data from the storage to kernel pages
* Copying data from the kernel pages to user buffer
* Switching from the kernel mode to the user mode

## Test Procedure
* Pre-conditioning
    * mount tmpfs: `mount -t tmpfs -o size=3G tmpfs <mountpoint>`
    * clear swap: `swapoff -a && swapon -a`
    * drop cache: `echo 3 > /proc/sys/vm/drop_caches`
* Run program
* Cleaning-up
    * diff: “diff source destination”

## Conclusion
Sendfile method will be faster than mmap method, both of them are faster than the baseline

