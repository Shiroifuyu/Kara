#include <stdint.h>
#include <vector>
using namespace std;

enum memoryArea{
    ROM,        //|
    SROM,       //| Cartridge ROM

    VRAM,       //| Internal RAM

    SRAM,       //| Cartridge RAM

    IRAM,       //|
    EIRAM,      //|
    SAM,        //| Internal RAM

    Empty,      //|
    IO,         //|
    Empty2,     //|
    IRAM,       //|
    IER         //| Special / I/O
};

enum registerType {
    Acumulator,
    Flags,
    GeneralPurpose,
    HL
};

struct memoryAddr {
    memoryArea area;
    uint8_t data;

    memoryAddr() : area(ROM), data(0) {}
    memoryAddr(memoryArea area, uint8_t data) : area(area), data(data) {}
};


class Memory {
    private:
        //size of memory areas in bytes
        vector<int> areaSize{16384, 16384, 8192, 8192, 8192, 8192, 160, 96, 76, 52, 127, 1};
        vector<memoryAddr> memory;
    
    public:
        Memory();
        uint8_t read_word(uint8_t H, uint8_t L);
        
};