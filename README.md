# Memory Allocator in C

##  Overview

This is a **simple memory allocator** implemented in C that simulates memory allocation, deallocation, and heap management using a statically defined heap (`char Heap[SIZE]`). It mimics the behavior of `malloc()` and `free()` using a custom linked list-based metadata management system.

This program is ideal for understanding how dynamic memory management and heap allocation strategies like **first-fit** and **block merging** work behind the scenes.

---

##  Key Concepts

- Simulated memory allocation in a static array (`Heap`)
- Custom metadata structure (`Metadata`) for tracking block size, status, and links
- Allocation via **first-fit strategy**
- Block **splitting** on allocation
- **Merging** adjacent free blocks during deallocation
- CLI-based interactive menu to test allocation and deallocation

---

##  Features

- ✅ Allocate a memory block of custom size  
- ✅ Free a previously allocated memory block  
- ✅ Automatic merging of adjacent free blocks  
- ✅ Display heap blocks with:
  - Block size
  - Allocation status
  - Memory address
  - Block index

---

## 🛠️ Compilation and Execution

### 🔧 Compile:
```bash
gcc memory_allocator.c -o memory_allocator
