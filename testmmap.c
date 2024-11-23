#include "types.h"
#include "stat.h"
#include "user.h"

#define PGSIZE 4096  // Page size is 4 KB

int main() {
    printf(1, "Initial state:\n");
    int vp_before = numvp();  // Get initial number of virtual pages
    int pp_before = numpp();  // Get initial number of physical pages
    printf(1, "Virtual pages: %d\n", vp_before);
    printf(1, "Physical pages: %d\n", pp_before);

    printf(1, "\nMapping 3 pages (12 KB)...\n");
    char *mmap_region = (char *)mmap(3 * PGSIZE);  // Map 3 pages
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
    mmap_region[0] = 'A';       // Access first page
    mmap_region[PGSIZE] = 'B';  // Access second page
    mmap_region[2 * PGSIZE] = 'C';  // Access third page

    printf(1, "After accessing mmap pages:\n");
    int vp_after_access = numvp();  // Get virtual page count after access
    int pp_after_access = numpp();  // Get physical page count after access
    printf(1, "Virtual pages: %d\n", vp_after_access);
    printf(1, "Physical pages: %d\n", pp_after_access);

    printf(1, "\nValidation complete. Exiting...\n");
    exit();
}
