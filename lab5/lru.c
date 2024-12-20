#include <stdio.h>

#define maxsize 100

int main() {
    int pages[maxsize], frames[maxsize], frameCount, pageCount;
    int pageFaults = 0, leastRecentlyUsed[maxsize] = {0};
    int pageInFrameCount = 0; // Counter to track the number of pages currently in the frames

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

    // Simulate LRU Page Replacement
    printf("\nPage Reference\tFrames\tState\n");
    for (int i = 0; i < pageCount; i++) {
        int page = pages[i];
        int found = 0;

        // Check if the page is already in one of the frames
        for (int j = 0; j < frameCount; j++) {
            if (frames[j] == page) {
                found = 1; // Page hit, no need to replace
                leastRecentlyUsed[j] = i; // Update the most recent use of the page
                break;
            }
        }

        // If page not found in frames, it's a page fault
        if (!found) {
            if (pageInFrameCount < frameCount) {
                // If there is space in the frames, just add the page
                frames[pageInFrameCount] = page;
                leastRecentlyUsed[pageInFrameCount] = i; // Update the most recent use of the page
                pageInFrameCount++; // Increment the count of pages in frames
            } else {
                // Find the least recently used page to replace
                int replaceIndex = 0;
                int minLRU = leastRecentlyUsed[0];
                for (int j = 1; j < frameCount; j++) {
                    if (leastRecentlyUsed[j] < minLRU) {
                        minLRU = leastRecentlyUsed[j];
                        replaceIndex = j;
                    }
                }

                frames[replaceIndex] = page; // Replace the page in the frame
                leastRecentlyUsed[replaceIndex] = i; // Update the most recent use of the page
            }
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
