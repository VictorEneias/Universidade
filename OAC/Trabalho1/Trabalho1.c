#include <stdio.h>
#include <stdint.h>

//
// memoria ligada ao processador
//

#define MEM_SIZE 1024
#define DATA_SEG 512

int32_t lb(const uint32_t address, int32_t kte);

uint32_t lbu(const uint32_t address, int32_t kte);

int32_t lw(const uint32_t address, int32_t kte);

void sb(const uint32_t address, int32_t kte, int8_t dado);

void sw(const uint32_t address, int32_t kte, int32_t dado);

//
// memoria ligada ao processador
//

int8_t mem[MEM_SIZE];

int main (int argc, const char * argv[]) {
    int8_t b0, b1, b2, b3;
    int32_t w;

    scanf("%hhx, %hhx, %hhx, %hhx", &b0, &b1, &b2, &b3);    
    
    sb(0, 0, b0);           
    sb(0, 1, b1);           
    sb(0, 2, b2);           
    sb(0, 3, b3);           

    scanf("%hhx, %hhx, %hhx, %hhx", &b0, &b1, &b2, &b3);    
    
    sb(DATA_SEG, 0, b0);    
    sb(DATA_SEG, 1, b1);
    sb(DATA_SEG, 2, b2);    
    sb(DATA_SEG, 3, b3);

    scanf("%x", &w);                         
    
    sw(8, 0, w);            

    scanf("%x", &w);
    
    sw(12, 0, w);           

    printf("%08x\n", lw(0, 0));             
    printf("%08x\n", lw(DATA_SEG, 0));  
    printf("%08x\n", lb(DATA_SEG,0));       
    printf("%08x\n", lbu(DATA_SEG,1));      
    printf("%08x\n", lw(8, 0));             
    printf("%08x\n", lw(12, 0));            

    return 0;
}

/*********** Inserir codigo das funções a seguir. ****************/

int32_t lb(const uint32_t address, int32_t kte) {
    uint32_t addr = address + kte;
    return (int32_t) mem[addr];
}

uint32_t lbu(const uint32_t address, int32_t kte) {
    uint32_t addr = address + kte;
    return (uint32_t) ((uint8_t) mem[addr]);
}

int32_t lw(const uint32_t address, int32_t kte) {
    uint32_t addr = address + kte;

    uint32_t byte0 = (uint8_t) mem[addr];
    uint32_t byte1 = (uint8_t) mem[addr + 1];
    uint32_t byte2 = (uint8_t) mem[addr + 2];
    uint32_t byte3 = (uint8_t) mem[addr + 3];

    return (int32_t) ((byte3 << 24) | (byte2 << 16) | (byte1 << 8) | byte0);
}

void sb(const uint32_t address, int32_t kte, int8_t dado) {
    uint32_t addr = address + kte;
    mem[addr] = dado;
}

void sw(const uint32_t address, int32_t kte, int32_t dado) {
    uint32_t addr = address + kte;

    mem[addr]     = (int8_t) (dado & 0xFF);
    mem[addr + 1] = (int8_t) ((dado >> 8) & 0xFF);
    mem[addr + 2] = (int8_t) ((dado >> 16) & 0xFF);
    mem[addr + 3] = (int8_t) ((dado >> 24) & 0xFF);
}