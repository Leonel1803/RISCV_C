// Number of words to advance
unsigned word = 2;
// Number of memory accesses pero loop
unsigned accessesPerTurn = 128;
// Number of loops
unsigned turns = 2;
// Starting address
unsigned* baseAddress = (unsigned*)0x10010000;

void main() 
{
    for(unsigned i = 0; i < turns; i++)
    {
        volatile unsigned* address = baseAddress;
        for(unsigned j = 0; j < accessesPerTurn; j ++)
        {
            // The first time this loop executes, 
            // all the accesses will be misses.
            // Further loops will be hits.
            *address = i;
            address += word;  
        }
        
        for(int c = 0; c < 50; c++);
    }
    
    while(1);
}