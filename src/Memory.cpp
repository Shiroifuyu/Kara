#include "Memory.h"

Memory::Memory() {
    for (int i = 0; i < areaSize.size(); ++i) {
        for (size_t j = 0; j < areaSize[i]; ++j) {
            memoryAddr a(static_cast<memoryArea>(i), 0);
            memory.push_back(a);
        }
    }
}