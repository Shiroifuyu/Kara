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

struct memoryAddr {
    memoryArea area;        //Redundant data, but it will be convinient. Consider organizing the area sectos in a more memory efficient way.
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

        //Instructions to modify main memory
        //Temporal Naive implementation
        uint8_t read_byte(unsigned addr) { return memory[addr].data; };
        uint8_t read_byte(uint16_t addr) { return memory[addr].data; };
        void write_byte(unsigned addr, uint8_t value) { this->memory[addr].data = value; };

};