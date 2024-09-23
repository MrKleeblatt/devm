#include "x-watcher/array.h"

#define arr_foreach(array, index) if(array != nullptr) for(size_t index = 0; index < arr_count(array); ++index)
