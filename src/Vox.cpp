#include "Vox.hpp"
int Vox::constrain(int v, int l, int h) {
    if(v < l)
        return l;
    if(v > h)
        return h;
    return v;
}

int Vox::getParameterMax(int id) {
    switch(id) {
        case P_CC_CHANNEL:
            return 15;
        case P_NOTE_CHANNEL:
            return 15;
        case P_TRANSPOSE:
            return 10;
        case P_FIRST_KEY:
            return 127;
        case P_LAST_KEY:
            return 127;
    }
    return getCustomParameterMax(id);
}
int Vox::getParameterMin(int id) {
    switch(id) {
        case P_CC_CHANNEL:
            return 0;
        case P_NOTE_CHANNEL:
            return 0;
        case P_TRANSPOSE:
            return -10;
        case P_FIRST_KEY:
            return 0;
        case P_LAST_KEY:
            return 0;
    }
    return getCustomParameterMin(id);
}

int Vox::getParameter(int id) {
    switch(id) {
        case P_CC_CHANNEL:
            return ccChannel;
        case P_NOTE_CHANNEL:
            return channel;
        case P_TRANSPOSE:
            return transpose;
        case P_FIRST_KEY:
            return startingNote;
        case P_LAST_KEY:
            return endingNote;
    }
    return getCustomParameter(id);
}
const char* _names[] = {
    "Control Channel",
    "Key/Pitchbend Channel",
    "Transpose by Octaves",
    "First Key",
    "Last Key"
};
const char* Vox::getParameterName(int id) {
    if( id < P_CUSTOM) {
        return _names[id];
    }
    return getCustomParameterName(id);
}

void Vox::setParameter(int id, int value) {
    value = constrain(value, getParameterMin(id), getParameterMax(id));
    updateParameterDisplay(id, value);
    switch(id) {
        case P_CC_CHANNEL:
            ccChannel = value;
            break;
        case P_NOTE_CHANNEL:
            channel = value;
            break;
        case P_TRANSPOSE:
            transpose = value;
            break;
        case P_FIRST_KEY:
            startingNote = value;
            break;
        case P_LAST_KEY:
            endingNote = value;
            break;
        default:
            setCustomParameter(id, value);
            break;
    }
}