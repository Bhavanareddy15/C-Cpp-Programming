#include <stdio.h>

int TestBit(unsigned int word, int i) {
    return(word & (1 << i));
}
void SetBit(unsigned int *word, int i) {
    *word |= 1 << i;
}
void ClearBit(unsigned int *word, int i) {
    *word &= ~(1 << i);
}
unsigned int GetField(unsigned int word, int lsb, int length) {
    return(word >> lsb) & ((1 << length) -1);
}


void SetField(unsigned int *word, int lsb, int length, int value){
    unsigned int mask = (((1 << length) -1))<<lsb;
    *word = ((*word & ~mask) | ((value<<lsb) & mask));
}

// Helper to print a word in binary (just for visualizing test results)
void PrintBinary(unsigned int word) {
    for (int i = 31; i >= 0; i--) {
        printf("%d", (word >> i) & 1);
        if (i % 8 == 0 && i != 0) printf(" ");
    }
    printf("\n");
}

int main(void) {
    unsigned int myWord = 0;

    printf("Initial value:\n");
    PrintBinary(myWord);

    // Test SetBit
    SetBit(&myWord, 3);
    printf("\nAfter SetBit(&myWord, 3):\n");
    PrintBinary(myWord);

    SetBit(&myWord, 7);
    printf("\nAfter SetBit(&myWord, 7):\n");
    PrintBinary(myWord);

    // Test TestBit
    printf("\nTestBit(myWord, 3) = %d (expect 1)\n", TestBit(myWord, 3));
    printf("TestBit(myWord, 7) = %d (expect 1)\n", TestBit(myWord, 7));
    printf("TestBit(myWord, 5) = %d (expect 0)\n", TestBit(myWord, 5));

    // Test ClearBit
    ClearBit(&myWord, 3);
    printf("\nAfter ClearBit(&myWord, 3):\n");
    PrintBinary(myWord);

    printf("\nTestBit(myWord, 3) = %d (expect 0, since we cleared it)\n", TestBit(myWord, 3));
    printf("TestBit(myWord, 7) = %d (expect 1, still set)\n", TestBit(myWord, 7));

    myWord = 0;

    printf("Initial value:\n");
    PrintBinary(myWord);

    // --- Test SetField ---
    // Set a 4-bit field starting at bit 4, value = 0b1011 (11)
    SetField(&myWord, 4, 4, 0b1011);
    printf("\nAfter SetField(&myWord, lsb=4, length=4, value=11):\n");
    PrintBinary(myWord);
    printf("Expect bits 4-7 = 1011 -> myWord should show ...00001011 0000\n");

    // Set another field: 3 bits starting at bit 12, value = 0b101 (5)
    SetField(&myWord, 12, 3, 0b101);
    printf("\nAfter SetField(&myWord, lsb=12, length=3, value=5):\n");
    PrintBinary(myWord);

    // --- Test GetField ---
    unsigned int f1 = GetField(myWord, 4, 4);
    printf("\nGetField(myWord, lsb=4, length=4) = %u (expect 11)\n", f1);

    unsigned int f2 = GetField(myWord, 12, 3);
    printf("GetField(myWord, lsb=12, length=3) = %u (expect 5)\n", f2);

    unsigned int f3 = GetField(myWord, 0, 4);
    printf("GetField(myWord, lsb=0, length=4) = %u (expect 0, untouched bits)\n", f3);

    // --- Test overwrite: SetField should clear old bits in that field first ---
    SetField(&myWord, 4, 4, 0b0000);
    printf("\nAfter SetField(&myWord, lsb=4, length=4, value=0) (clear that field):\n");
    PrintBinary(myWord);
    printf("GetField(myWord, lsb=4, length=4) = %u (expect 0)\n", GetField(myWord, 4, 4));
    printf("GetField(myWord, lsb=12, length=3) = %u (expect 5, unaffected)\n", GetField(myWord, 12, 3));

    // --- Edge case: length=1 (single bit field, like TestBit) ---
    SetField(&myWord, 31, 1, 1);
    printf("\nAfter SetField(&myWord, lsb=31, length=1, value=1):\n");
    PrintBinary(myWord);
    printf("GetField(myWord, lsb=31, length=1) = %u (expect 1)\n", GetField(myWord, 31, 1));

    // --- Edge case: length=32, lsb=0 (whole word) ---
    unsigned int wholeWord = 0;
    SetField(&wholeWord, 0, 32, 0xFFFFFFFF);
    printf("\nAfter SetField(&wholeWord, lsb=0, length=32, value=0xFFFFFFFF):\n");
    PrintBinary(wholeWord);
    // NOTE: this is UB-adjacent in C (1 << 32 is undefined) - flagged below

    // --- Value larger than field: should be masked/truncated ---
    unsigned int truncTest = 0;
    SetField(&truncTest, 0, 4, 0xFF);  // 0xFF = 11111111, but field is only 4 bits
    printf("\nAfter SetField(&truncTest, lsb=0, length=4, value=0xFF):\n");
    PrintBinary(truncTest);
    printf("GetField(truncTest, lsb=0, length=4) = %u (expect 15, truncated to 4 bits)\n",
           GetField(truncTest, 0, 4));

    return 0;
}