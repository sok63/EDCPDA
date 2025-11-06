#include "ALVRenderHAL.h"

void ALVRenderHAL::renderDataToSprite(ADisplaySpriteHAL *, uint8_t *data_sequence)
{
    uint32_t shift = 0;

    // FIXME: Naive read until END type
    while (true)
    {

        // Got next type    
        auto type = ALVRenderHAL::getNextType(data_sequence,shift);
        // Apply it
        switch (type)
        {
        case eLVTypes::INDEXED_LINE:
            /* code */
            break;
        
        default:
            break;
        }
    }
}



eLVTypes ALVRenderHAL::getNextType(uint8_t *data_sequence, uint32_t shift)
{
    return eLVTypes();
}
