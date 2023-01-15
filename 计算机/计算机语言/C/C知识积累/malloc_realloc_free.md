# malloc, realloc and free


realloc可能会使原来的内存空间换位置，导致值改变，所以最好是双指针
```cpp
    bool**b = (bool**)malloc(3 * sizeof(bool*));
    *b = (bool*)malloc(4 * sizeof(bool));

    BigFamily->families = (Family**)realloc(BigFamily->families, BigFamily->numberOfFamilies * sizeof(Family*));
    
    for(int i=0;i < (Wild->numberOfAnimals);i++)
    {
        free(Wild->animals[i]);
    }
    free(Wild->animals);
```