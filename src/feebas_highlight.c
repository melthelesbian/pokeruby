#include "global.h"
#include "metatile_behavior.h"
#include "fieldmap.h"
#include "wild_encounter.h"

#define NUM_FEEBAS_SPOTS    6

const u16 gRoute119WaterTileSectionData[3][3] =
{
    {0, 0x2D, 0},
    {0x2E, 0x5B, 0x83},
    {0x5C, 0x8B, 0x12A},
};

void HighlightFeebasSpots() {
    u16 nWaterTiles = 447;
    u16 nFeebasGenerated = 0;
    u16 nFeebasHighlighted = 0;
    u16 currentWaterTile = 0;
    u16 feebasTiles[NUM_FEEBAS_SPOTS];
    s16 x;
    s16 y;
    u16 randomTile;
    u8 section;
    u16 yMin;
    u16 yMax;
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

    for(section = 0; section < 3; section++) {
        yMin = gRoute119WaterTileSectionData[section][0];
        yMax = gRoute119WaterTileSectionData[section][1];
        currentWaterTile = gRoute119WaterTileSectionData[section][2];

        for(y = yMin; y <= yMax; y++) {
            for(x = 0; x < gMapHeader.mapLayout->width; x++) {
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
}
