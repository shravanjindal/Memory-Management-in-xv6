#include "types.h"
#include "stat.h"
#include "user.h"

#define PGSIZE 4096  // Page size is 4 KB

int main() {
    printf(1, "Enter the number of pages to map: ");
    char buffer[16];
    int bytes_read = read(0, buffer, sizeof(buffer));
    if (bytes_read <= 0) {
        printf(1, "Failed to read input.\n");
        exit();
    }
    buffer[bytes_read - 1] = '\0';  // Remove the newline character
    int num_pages = atoi(buffer);
    if (num_pages <= 0) {
        printf(1, "Invalid number of pages.\n");
        exit();
    }

    printf(1, "Initial state:\n");
    int vp_before = numvp();  // Get initial number of virtual pages
    int pp_before = numpp();  // Get initial number of physical pages
    printf(1, "Virtual pages: %d\n", vp_before);
    printf(1, "Physical pages: %d\n", pp_before);

    printf(1, "\nMapping %d pages (%d KB)...\n", num_pages, num_pages * PGSIZE / 1024);
    char *mmap_region = (char *)mmap(num_pages * PGSIZE);  // Map user-specified pages
    if (!mmap_region) {
        printf(1, "mmap failed!\n");
        exit();
    }

    printf(1, "After mmap, before access:\n");
    int vp_after_mmap = numvp();  // Get virtual page count after mmap
    int pp_after_mmap = numpp();  // Get physical page count after mmap
    printf(1, "Virtual pages: %d\n", vp_after_mmap);
    printf(1, "Physical pages: %d\n", pp_after_mmap);

    printf(1, "\nAccessing mapped memory...\n");
    for (int i = 0; i < num_pages; i++) {
        mmap_region[i * PGSIZE] = 'A' + i;  // Access each page
    }

    printf(1, "After accessing mmap pages:\n");
    int vp_after_access = numvp();  // Get virtual page count after access
    int pp_after_access = numpp();  // Get physical page count after access
    printf(1, "Virtual pages: %d\n", vp_after_access);
    printf(1, "Physical pages: %d\n", pp_after_access);

    printf(1, "\nValidation complete. Exiting...\n");
    exit();
}
