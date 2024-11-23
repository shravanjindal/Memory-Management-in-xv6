#include "types.h"
#include "stat.h"
#include "user.h"

int main() {
    // Allocate a small array (e.g., 100 integers)
    int large_array[1000000];
    for (int i = 0; i < 1000000; i++) {
        large_array[i] = 0;  // Initialize the array to prevent optimization
    }

    // Use the array to avoid the "unused" warning
    int sum = 0;
    for (int i = 0; i < 1000000; i++) {
        sum += large_array[i];  // Access the array to prevent unused warning
    }

    // Get the number of virtual pages for the current process
    int num_pages = numvp();  
    printf(1, "large Process: Number of virtual pages: %d\n", num_pages);  
    exit();
}
