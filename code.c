#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define SIZE 1000

char Heap[SIZE];

typedef struct Metadata {
    int size;
    char mark;
    struct Metadata *next;
} Metadata;

Metadata *head_ptr = (Metadata *)Heap;

void Initialize() {
    head_ptr->size = (SIZE - sizeof(Metadata));
    head_ptr->mark = 'f';
    head_ptr->next = NULL;
}

int Allocate(int request_size) {
    Metadata *ptr = head_ptr;
    Metadata *prev = NULL;
    int index = 0;

    while (ptr != NULL && (ptr->mark == 'a' || ptr->size < request_size)) {
        prev = ptr;
        ptr = ptr->next;
        index++;
    }

    if (ptr == NULL) {
        index = -1; // No block available   
        
    } else {
        if (ptr->size == request_size) {
            ptr->mark = 'a';
        } else {
            // Calculate the address for the new block
            Metadata *new_block = (Metadata *)((char *)ptr + sizeof(Metadata) + request_size);
            new_block->size = ptr->size - (request_size + sizeof(Metadata));
            new_block->mark = 'f';
            new_block->next = ptr->next;

            ptr->size = request_size;
            ptr->mark = 'a';
            ptr->next = new_block;
        }
    }
    return index;
}

void Merge() {
    Metadata *ptr = head_ptr;

    while (ptr != NULL && ptr->next != NULL) {
        if (ptr->mark == 'f' && ptr->next->mark == 'f') {
            ptr->size = ptr->size + ptr->next->size + sizeof(Metadata);
            ptr->next = ptr->next->next;
            // Don't move ptr here as we might need to merge again
        } else {
            ptr = ptr->next;
        }
    }
}

bool Free(int index) {
    Metadata *ptr = head_ptr;
    bool ret_val = false;

    while (index != 0 && ptr != NULL) {
        ptr = ptr->next;
        index--;
    }

    if (index == 0 && ptr != NULL && ptr->mark == 'a') {
        ptr->mark = 'f';
        ret_val = true;
        Merge();
    }

    return ret_val;
}

void Display_Heap() {
    Metadata *ptr = head_ptr;
    printf("Heap Details:\n");
    printf("Block Size\tBlock Status\tBlock Address\tBlock Index\n");
    printf("-----------------------------------------------------------\n");

    int index = 0;
    while (ptr != NULL) {
        printf("%d\t\t%c\t\t%p\t%d\n", 
               ptr->size, 
               ptr->mark, 
               (void *)ptr, 
               index);
        ptr = ptr->next;
        index++;
    }
    printf("\n");
}

int main() {
    Initialize();
    
    while (1) {
        printf("\nMemory Allocator Menu:\n");
        printf("1. Allocate memory\n");
        printf("2. De-allocate memory\n");
        printf("3. Display heap elements\n");
        printf("4. Quit\n");
        printf("Enter choice: ");
        
        int choice;
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n'); // Clear input buffer
            continue;
        }

        switch (choice) {
            case 1: {
                int size;
                printf("Enter the size of block to allocate: ");
                if (scanf("%d", &size) != 1 || size <= 0) {
                    printf("Invalid size. Please enter a positive number.\n");
                    while (getchar() != '\n');
                    break;
                }
                
                int ret_val = Allocate(size);
                if (ret_val == -1) {
                    printf("Failed to assign memory\n");
                } else {
                    printf("Memory successfully assigned at index: %d\n", ret_val);
                }
                break;
            }
            
            case 2: {
                int index;
                printf("Enter the index to free: ");
                if (scanf("%d", &index) != 1 || index < 0) {
                    printf("Invalid index. Please enter a non-negative number.\n");
                    while (getchar() != '\n');
                    break;
                }
                
                if (Free(index)) {
                    printf("De-allocation successful\n");
                } else {
                    printf("De-allocation failed\n");
                }
                break;
            }
            
            case 3:
                Display_Heap();
                break;
                
            case 4:
                printf("Exiting program\n");
                return 0;
                
            default:
                printf("Invalid choice. Please enter 1-4.\n");
        }
    }
    
    return 0;
}