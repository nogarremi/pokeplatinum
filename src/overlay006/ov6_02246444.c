#include <nitro.h>
#include <string.h>

#include "struct_decls/struct_0202440C_decl.h"
#include "trainer_info.h"
#include "struct_decls/struct_0202E4D4_decl.h"
#include "struct_decls/struct_0202E768_decl.h"
#include "struct_decls/struct_0202E794_decl.h"
#include "overlay006/struct_ov6_022465F4_decl.h"

#include "field/field_system.h"

#include "unk_020021B0.h"
#include "heap.h"
#include "savedata/save_table.h"
#include "unk_02025E08.h"
#include "trainer_info.h"
#include "unk_0202E2CC.h"
#include "overlay006/ov6_02246444.h"

struct UnkStruct_ov6_022465F4_t {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 unk_03;
    u16 unk_04[8];
    UnkStruct_0202E4D4 * unk_14;
};

static void ov6_02246444 (UnkStruct_ov6_022465F4 * param0)
{
    MI_CpuClear8(param0, sizeof(UnkStruct_ov6_022465F4));
}

static void ov6_02246450 (UnkStruct_ov6_022465F4 * param0, int param1)
{
    param0->unk_03 = param1;
}

static void ov6_02246454 (UnkStruct_ov6_022465F4 * param0, int param1)
{
    param0->unk_02 = param1;
}

static void ov6_02246458 (UnkStruct_ov6_022465F4 * param0, int param1)
{
    param0->unk_01 = param1;
}

static void ov6_0224645C (UnkStruct_ov6_022465F4 * param0, const u16 * param1)
{
    sub_020021D0(param0->unk_04, param1, 7 + 1);
}

static void ov6_02246468 (UnkStruct_ov6_022465F4 * param0, UnkStruct_0202E4D4 * param1)
{
    param0->unk_00 = sub_0202E55C(param1);
    param0->unk_14 = param1;
}

void ov6_0224647C (UnkStruct_ov6_022465F4 * param0)
{
    if (param0->unk_14 != NULL) {
        sub_0202E560(param0->unk_14);
    }
}

int ov6_0224648C (const UnkStruct_ov6_022465F4 * param0)
{
    return param0->unk_03;
}

int ov6_02246490 (const UnkStruct_ov6_022465F4 * param0)
{
    return param0->unk_02;
}

const u16 * ov6_02246494 (const UnkStruct_ov6_022465F4 * param0)
{
    return param0->unk_04;
}

void * ov6_02246498 (UnkStruct_ov6_022465F4 * param0)
{
    return sub_0202E574(param0->unk_14);
}

int ov6_022464A4 (const UnkStruct_ov6_022465F4 * param0)
{
    return param0->unk_00;
}

static UnkStruct_ov6_022465F4 * ov6_022464A8 (FieldSystem * param0, UnkStruct_0202E794 * param1)
{
    UnkStruct_ov6_022465F4 * v0 = Heap_AllocFromHeap(4, sizeof(UnkStruct_ov6_022465F4));

    ov6_02246444(v0);
    ov6_0224645C(v0, sub_0202E4C8(param1));
    ov6_02246454(v0, sub_0202E4CC(param1));
    ov6_02246458(v0, sub_0202E4D0(param1));
    ov6_02246468(v0, sub_0202E4D4(param1));

    return v0;
}

static UnkStruct_ov6_022465F4 * ov6_022464F8 (FieldSystem * param0, UnkStruct_0202E768 * param1)
{
    TrainerInfo * v0 = SaveData_GetTrainerInfo(param0->saveData);
    UnkStruct_ov6_022465F4 * v1 = Heap_AllocFromHeap(4, sizeof(UnkStruct_ov6_022465F4));

    ov6_02246444(v1);
    ov6_0224645C(v1, TrainerInfo_Name(v0));
    ov6_02246450(v1, TrainerInfo_Gender(v0));
    ov6_02246454(v1, GAME_LANGUAGE);
    ov6_02246458(v1, GAME_VERSION);
    ov6_02246468(v1, sub_0202E4D8(param1));

    return v1;
}

static UnkStruct_ov6_022465F4 * ov6_02246550 (FieldSystem * param0, int param1)
{
    TrainerInfo * v0 = SaveData_GetTrainerInfo(param0->saveData);
    UnkStruct_ov6_022465F4 * v1 = Heap_AllocFromHeap(4, sizeof(UnkStruct_ov6_022465F4));

    ov6_02246444(v1);
    v1->unk_00 = param1;
    ov6_0224645C(v1, TrainerInfo_Name(v0));
    ov6_02246450(v1, TrainerInfo_Gender(v0));
    ov6_02246454(v1, GAME_LANGUAGE);
    ov6_02246458(v1, GAME_VERSION);

    v1->unk_14 = NULL;
    return v1;
}

UnkStruct_ov6_022465F4 * ov6_022465A0 (FieldSystem * param0, int param1, int param2)
{
    TVBroadcast * v0 = SaveData_TVBroadcast(param0->saveData);

    if ((param1 == 4) || (param1 == 5)) {
        return ov6_02246550(param0, param2);
    }

    if (sub_0202E7C0(param2) == 0) {
        UnkStruct_0202E794 * v1 = sub_0202E794(v0, param1, param2);
        return ov6_022464A8(param0, v1);
    } else {
        UnkStruct_0202E768 * v2 = sub_0202E768(v0, param1, param2);
        return ov6_022464F8(param0, v2);
    }
}

void ov6_022465F4 (UnkStruct_ov6_022465F4 * param0)
{
    Heap_FreeToHeap(param0);
}
