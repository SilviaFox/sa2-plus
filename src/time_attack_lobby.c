#include "time_attack_lobby.h"
#include "main.h"
#include "sprite.h"
#include "save.h"
#include "transition.h"
#include "game.h"
#include "malloc_vram.h"
#include "m4a.h"
#include "character_select.h"
#include "course_select.h"
#include "profile.h"
#include "constants/songs.h"
#include "title_screen.h"
#include "zones.h"

struct TimeAttackLobbyScreen {
    struct Unk_03002400 unk0;
    struct Unk_03002400 unk40;
    struct UNK_0808B3FC_UNK240 unk80;
    struct UNK_0808B3FC_UNK240 unkB0[5];
    struct UNK_802D4CC_UNK270 unk1A0;
    u8 unk1AC;
    u8 unk1AD;
    u8 unk1AE;
    u8 unk1AF;
};

extern const struct UNK_080E0D64 gUnknown_080E04D4[30];
extern const struct UNK_080E0D64 gUnknown_080E0474[10];
extern const struct UNK_080E0D64 gUnknown_080E04C4[2];

#define IsBossTimeAttack() (GetBit(gGameMode, 1))

void sub_8088944(struct TimeAttackLobbyScreen* lobbyScreen) {
    struct UNK_802D4CC_UNK270* transitionConfig;
    struct Unk_03002400* background;
    struct UNK_0808B3FC_UNK240* element;
    s8 lang = gLoadedSaveGame->unk6 - 1;
    u32 i;

    if (lang < 0) {
        lang = 0;
    }

    gDispCnt = 1;
    gDispCnt |= 0x1341;
    gBgCntRegs[0] = 0x1D05;
    gBgCntRegs[1] = 0x702;

    gUnknown_03004D80[0] = 0;
    gUnknown_03002280[0] = 0;
    gUnknown_03002280[1] = 0;
    gUnknown_03002280[2] = 0xff;
    gUnknown_03002280[3] = 32;
    gUnknown_03004D80[1] = 0;
    gUnknown_03002280[4] = 0;
    gUnknown_03002280[5] = 0;
    gUnknown_03002280[6] = 0xff;
    gUnknown_03002280[7] = 32;
    gUnknown_03004D80[2] = 0;
    gUnknown_03002280[8] = 0;
    gUnknown_03002280[9] = 0;
    gUnknown_03002280[10] = 0xff;
    gUnknown_03002280[11] = 32;

    gBgScrollRegs[0][0] = 0xFFF8;
    gBgScrollRegs[0][1] = 0;
    gBgScrollRegs[1][0] = 0;
    gBgScrollRegs[1][1] = 0;
    gBgScrollRegs[2][0] = 0;
    gBgScrollRegs[2][1] = 0;

    for (i = 0; i < 5; i++) {
        element = &lobbyScreen->unkB0[i + 1];
        if (i != 3) {
            if (i > 3) {
                element = &lobbyScreen->unkB0[i];
            }

            if (i == 2 && (gGameMode & GAME_MODE_BOSS_TIME_ATTACK)) {
                element = &lobbyScreen->unkB0[3];
                i = 3;
            }
            element->unk4 = VramMalloc(gUnknown_080E04D4[lang * 5 + i].unk0);
            element->unkA = gUnknown_080E04D4[lang * 5 + i].unk4;
            element->unk20 = gUnknown_080E04D4[lang * 5 + i].unk6;
            element->unk21 = 0xFF;
            element->unk16 = 0x78;
            element->unk18 = i * 0x10 + 0x18;
            if (i > 2) {
                element->unk18 -= 0x10;
            }
            element->unk1A = 0x100;
            element->unk8 = 0;
            element->unk14 = 0;
            element->unk1C = 0;
            element->unk22 = 0x10;
            element->unk25 = 0;
            element->unk28 = -1;
            element->unk10 = 0x1000;
            sub_8004558(element);
        }
    }

    element = &lobbyScreen->unk80;
    element->unk4 = NULL;
    element->unkA = 0x41B;
    element->unk20 = 5;
    element->unk21 = 0xFF;
    element->unk16 = 0;
    element->unk18 = 0;
    element->unk1A = 0x100;
    element->unk8 = 0;
    element->unk14 = 0;
    element->unk1C = 0;
    element->unk22 = 0x10;
    element->unk25 = 0;
    element->unk28 = -1;
    element->unk10 = 0x1000;
    sub_8004558(element);

    element = &lobbyScreen->unk80;
    element->unk4 = VramMalloc(gUnknown_080E0474[gSelectedCharacter].unk0);
    element->unkA = gUnknown_080E0474[gSelectedCharacter].unk4;
    element->unk20 = gUnknown_080E0474[gSelectedCharacter].unk6;
    element->unk21 = 0xFF;
    element->unk16 = 0x78;
    element->unk18 = 0x82;
    element->unk1A = 0x100;
    element->unk8 = 0;
    element->unk14 = 0;
    element->unk1C = 0;
    element->unk22 = 0x10;
    element->unk25 = 0;
    element->unk28 = -1;
    element->unk10 = 0x1400;
    sub_8004558(element);

    lobbyScreen->unkB0[0].unk4 = 0;

    if (gSelectedCharacter == CHARACTER_CREAM) {
        lobbyScreen->unk1AC = 1;
        element = &lobbyScreen->unkB0[0];
        element->unk4 = VramMalloc(gUnknown_080E04C4[0].unk0);
        element->unkA = gUnknown_080E04C4[0].unk4;
        element->unk20 = gUnknown_080E04C4[0].unk6;
        element->unk21 = 0xFF;
        element->unk16 = 100;
        element->unk18 = 0x6E;
        element->unk1A = 0x140;
        element->unk8 = 0;
        element->unk14 = 0;
        element->unk1C = 0;
        element->unk22 = 0x10;
        element->unk25 = 0;
        element->unk28 = -1;
        element->unk10 = 0x1400;
        sub_8004558(element);
    }

    background = &lobbyScreen->unk40;
    background->unk4 = BG_SCREEN_ADDR(8);
    background->unkA = 0;
    background->unkC = BG_SCREEN_ADDR(29);
    background->unk18 = 0;
    background->unk1A = 0;
    background->unk1C = 0x96;
    background->unk1E = 0;
    background->unk20 = 0;
    background->unk22 = 0;
    background->unk24 = 0;
    background->unk26 = 0x1C;
    background->unk28 = 0xC;
    background->unk2A = 0;
    background->unk2E = 0;
    sub_8002A3C(background);

    background = &lobbyScreen->unk0;
    background->unk4 = BG_SCREEN_ADDR(0);
    background->unkA = 0;
    background->unkC = BG_SCREEN_ADDR(7);
    background->unk18 = 0;
    background->unk1A = 0;
    background->unk1C = 0x97;
    background->unk1E = 0;
    background->unk20 = 0;
    background->unk22 = 0;
    background->unk24 = 0;
    background->unk26 = 0x20;
    background->unk28 = 0x20;
    background->unk2A = 0;
    background->unk2E = 1;
    sub_8002A3C(background);

    transitionConfig = &lobbyScreen->unk1A0;
    transitionConfig->unk0 = 1;
    transitionConfig->unk4 = 0;
    transitionConfig->unk2 = 2;
    transitionConfig->unk6 = 0x200;
    transitionConfig->unk8 = 0x3FFF;
    transitionConfig->unkA = 0;

    m4aSongNumStart(MUS_TIME_ATTACK_MENU);
    sub_802D4CC(transitionConfig);
}

void sub_8088EB4(void);

void sub_8088CC4(void) {
    struct TimeAttackLobbyScreen* lobbyScreen = TaskGetStructPtr(gCurTask);
    struct UNK_0808B3FC_UNK240* element;    
    u32 i;

    for (i = 0; i < 4; i++) {
        element = &lobbyScreen->unkB0[i + 1];
        if (i == lobbyScreen->unk1AD) {
            element->unk25 = 0;
        } else {
            element->unk25 = 1;
        }
        sub_80051E8(element);
    }
    element = &lobbyScreen->unk80;
    sub_8004558(element);
    sub_80051E8(element);
    
    if (lobbyScreen->unk1AC != 0) {
        element = &lobbyScreen->unkB0[0];
        sub_8004558(element);
        sub_80051E8(element);
    }

    if (sub_802D4CC(&lobbyScreen->unk1A0) == 1) {
        gCurTask->main = sub_8088EB4;
    }
}

void sub_8088D60(void) {
    struct TimeAttackLobbyScreen* lobbyScreen = TaskGetStructPtr(gCurTask);
    struct UNK_0808B3FC_UNK240* element;
    u32 i;
    // WTF?
    u32 one = 1;

    if (sub_802D4CC(&lobbyScreen->unk1A0) == 1) {
        TaskDestroy(gCurTask);
        switch(lobbyScreen->unk1AD) {
            case 0:
                sub_801A770();
                return;
            case 1:
                CreateCharacterSelectionScreen(gSelectedCharacter, gLoadedSaveGame->unk13 & CHARACTER_BIT(CHARACTER_AMY));
                gCurrentLevel = LEVEL_INDEX(ZONE_1, ACT_1);
                return;
            case 2:
                CreateTimeAttackLevelSelectScreen(gGameMode >> 1 & one, gSelectedCharacter, gCurrentLevel);
                return;
            case 3:
                CreateTitleScreenAndSkipIntro();
                return;
            default:
                return;
        }
    }

    for (i = 0; i < 4; i++) {
        element = &lobbyScreen->unkB0[i + 1];
        sub_80051E8(element);
    }

    element = &lobbyScreen->unk80;
    switch(lobbyScreen->unk1AD) {
        case 1:
            element->unk16 -= 4;
            break;
        case 0:
        case 2:
            element->unk16 += 4;
            break;
    }
    sub_8004558(element);
    sub_80051E8(element);

    if (lobbyScreen->unk1AC == 0) {
        return;
    }

    element = &lobbyScreen->unkB0[0];
    switch (lobbyScreen->unk1AD) {
        case 1:
            element->unk16 -= 2;
            break;
        case 0:
        case 2:
            element->unk16 += 3;
            break;
    }

    sub_8004558(element);
    sub_80051E8(element);
}