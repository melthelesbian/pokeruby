#include "global.h"
#include "metatile_behavior.h"
#include "fieldmap.h"
#include "wild_encounter.h"

#define NUM_FEEBAS_SPOTS    6

void HighlightFeebasSpots() {
    u16 nWaterTiles = 447;
    u16 nFeebasGenerated = 0;
    u16 nFeebasHighlighted = 0;
    u16 currentWaterTile = 0;
    u16 feebasTiles[NUM_FEEBAS_SPOTS];
    s16 x;
    s16 y;
    u16 randomTile;
    u8 index;

    // Seed Feebas RNG
    FeebasSeedRng(gSaveBlock1.easyChatPairs[0].unk2);

    for(nFeebasGenerated = 0; nFeebasGenerated != NUM_FEEBAS_SPOTS;) {
        randomTile = FeebasRandom() % nWaterTiles;
        if(randomTile == 0) {
            randomTile = nWaterTiles;
        }
        if(randomTile == 0 || randomTile > 3) {
            feebasTiles[nFeebasGenerated] = randomTile;
            nFeebasGenerated++;
        }
    }

    for(y = 0; y < gMapHeader.mapLayout->height + 7; y++) {
        for(x = 0; x < gMapHeader.mapLayout->width + 7; x++) {
            u8 metatileBehavior = MapGridGetMetatileBehaviorAt(x, y);
            u8 feebasEncounterable = MetatileBehavior_IsFeebasEncounterable(metatileBehavior);
            if (feebasEncounterable == TRUE) {
                currentWaterTile++;
                // check each feebas spot to see if it matches
                if(nFeebasHighlighted < NUM_FEEBAS_SPOTS) {
                    for(index = 0; index < NUM_FEEBAS_SPOTS; index++) {
                        if(currentWaterTile == feebasTiles[index]) {
                            MapGridSetMetatileIdAt(x, y, 0x147);
                            nFeebasHighlighted++;
                        }
                    }
                }
            }
        }
    }
}
