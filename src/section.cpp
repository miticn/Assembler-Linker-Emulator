#include "../inc/section.hpp"

void Section::incPosition() {
    current_position += 4;
    if( current_position > size){
        size = current_position;
    }
}
