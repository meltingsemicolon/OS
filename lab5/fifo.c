#include <stdio.h>

#define maxsize 100

int main() {
    int pages[maxsize], frames[maxsize], frameCount, pageCount;
    int pageFaults = 0, nextReplaceIndex = 0;

    // Input number of frames
    printf("Enter the number of frames: ");
    scanf("%d", &frameCount);
    // Initialize all frames to -1 (indicating they are empty)
    for (int i = 0; i < frameCount; i++) {
        frames[i] = -1;
    }
    // Input number of pages
    printf("Enter the number of pages: ");
    scanf("%d", &pageCount);
    // Input pages
    printf("Enter the pages:\n");
    for (int i = 0; i < pageCount; i++) {
        scanf("%d", &pages[i]);
    }
    // Simulate FIFO Page Replacement
    printf("\nPage Reference\tFrames\tstate\n");
    for (int i = 0; i < pageCount; i++) {
        int page = pages[i];
        int found = 0;
        // Check if the page is already in one of the frames
        for (int j = 0; j < frameCount; j++) {
            if (frames[j] == page) {
                found = 1; // Page hit, no need to replace
                break;
            }
        }

        // If page not found in frames, it's a page fault
        if (!found) {
            frames[nextReplaceIndex] = page; // Replace the oldest page in the frame
            nextReplaceIndex = (nextReplaceIndex + 1) % frameCount; // Move to the next frame to replace
            pageFaults++; // Increment page fault counter
        }

        // Display the current state of the frames
        printf("%d\t\t", page);
        for (int j = 0; j < frameCount; j++) {
            if (frames[j] != -1)
                printf("%d ", frames[j]);
            else
                printf("- "); // Empty frame
        }
        printf("\t%s\n", found ? "+" : "*"); // Indicate page fault with '*'
    }
    // Display the number of page faults
    printf("\nTotal Page Faults: %d\n", pageFaults);

    return 0;
}
