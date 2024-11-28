#include <iostream>
#include "autotune.h"
#include "../SoundTouch/include/SoundTouch.h"

using namespace soundtouch;

int main() {
    Autotune::fillNoteTable();
    Autotune* obj = new Autotune(1);
    int x = 3;
    obj->process("../src/Diner.wav");
    

}
