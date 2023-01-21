#include <nitro.h>
#include <string.h>

#include "struct_decls/struct_020508D4_decl.h"
#include "overlay005/struct_ov5_021E1890_decl.h"

#include "struct_defs/struct_0203CDB0.h"

#include "heap.h"
#include "unk_02039C80.h"
#include "unk_020508D4.h"
#include "unk_02054D00.h"
#include "overlay005/ov5_021D37AC.h"
#include "overlay005/ov5_021E15F4.h"
#include "overlay005/ov5_021EF75C.h"
#include "overlay006/ov6_02247D30.h"

typedef struct {
    VecFx32 unk_00;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 unk_0F;
    u8 unk_10[6];
} UnkStruct_ov6_02247D30;

static BOOL ov6_02247DAC(UnkStruct_020508D4 * param0);

static VecFx32 Unk_ov6_022498E4[6] = {
    {-((FX32_ONE * 4) + (FX32_ONE / 2)), FX32_ONE * 12, -((FX32_ONE * 4) + (FX32_ONE / 2))},
    {((FX32_ONE * 4) + (FX32_ONE / 2)), FX32_ONE * 12, -((FX32_ONE * 4) + (FX32_ONE / 2))},
    {-((FX32_ONE * 4) + (FX32_ONE / 2)), FX32_ONE * 12, 0x0},
    {((FX32_ONE * 4) + (FX32_ONE / 2)), FX32_ONE * 12, 0x0},
    {-((FX32_ONE * 4) + (FX32_ONE / 2)), FX32_ONE * 12, ((FX32_ONE * 4) + (FX32_ONE / 2))},
    {((FX32_ONE * 4) + (FX32_ONE / 2)), FX32_ONE * 12, ((FX32_ONE * 4) + (FX32_ONE / 2))}
};

void ov6_02247D30 (UnkStruct_0203CDB0 * param0, const u8 param1)
{
    BOOL v0;
    UnkStruct_ov5_021E1890 * v1;
    int v2;
    int v3 = 507;

    v0 = sub_020552B4(param0, v3, &v1, &v2);

    if (v0) {
        UnkStruct_ov6_02247D30 * v4 = AllocFromHeapAtEnd(4, sizeof(UnkStruct_ov6_02247D30));

        v4->unk_0C = param1;
        v4->unk_0D = 0;
        v4->unk_0E = 0;
        v4->unk_0F = 0;

        {
            VecFx32 v5;

            sub_020553A4(v2, sub_02039E10(param0->unk_2C), &v5);
            v4->unk_00 = ov5_021E1894(v1);
            v4->unk_00.x += v5.x;
            v4->unk_00.z += v5.z;
        }

        sub_02050944(param0->unk_10, ov6_02247DAC, v4);
    } else {
        GF_ASSERT(FALSE);
    }
}

static BOOL ov6_02247DAC (UnkStruct_020508D4 * param0)
{
    UnkStruct_0203CDB0 * v0 = sub_02050A60(param0);
    UnkStruct_ov6_02247D30 * v1 = (UnkStruct_ov6_02247D30 *)sub_02050A64(param0);

    switch (v1->unk_0F) {
    case 0:
    {
        NNSG3dResMdl * v2;
        NNSG3dResFileHeader ** v3;
        NNSG3dRenderObj * v4;

        v3 = ov5_021EF9E8(517, v0->unk_30);
        v2 = NNS_G3dGetMdlByIdx(NNS_G3dGetMdlSet(*v3), 0);

        ov5_021D41C8(v0->unk_50, v0->unk_54, 0x10, 517, NULL, v2, ov5_021EFAA0(v0->unk_30), 1, 1, 0);
    }
        (v1->unk_0F)++;
        break;
    case 1:
    {
        UnkStruct_ov5_021E1890 * v5;
        NNSG3dRenderObj * v6;
        VecFx32 v7;
        VecFx32 v8 = {0, 0, 0};

        v7.x = v1->unk_00.x + Unk_ov6_022498E4[v1->unk_0D].x;
        v7.y = v1->unk_00.y + Unk_ov6_022498E4[v1->unk_0D].y;
        v7.z = v1->unk_00.z + Unk_ov6_022498E4[v1->unk_0D].z;

        v1->unk_10[v1->unk_0D] = ov5_021E19CC(v0->unk_A4, v0->unk_30, 517, &v7, &v8, v0->unk_50);
        v5 = ov5_021E18E0(v0->unk_A4, v1->unk_10[v1->unk_0D]);
        v6 = ov5_021E18BC(v5);
        ov5_021D4220(v0->unk_54, 0x10, v1->unk_0D, v6);
        (v1->unk_0F)++;
    }
    break;
    case 2:
        if (v1->unk_0E < 15) {
            v1->unk_0E++;
            break;
        } else {
            v1->unk_0E = 0;
        }

        v1->unk_0D++;

        if (v1->unk_0D < v1->unk_0C) {
            (v1->unk_0F) = 1;
        } else {
            (v1->unk_0F)++;
        }
        break;
    case 3:
        ov5_021D4250(v0->unk_54, 0x10, 0);
        (v1->unk_0F)++;
        break;
    case 4:
        if ((ov5_021D42F0(v0->unk_54, 0x10))) {
            u8 v9;

            ov5_021D42B0(v0->unk_50, v0->unk_54, 0x10);

            for (v9 = 0; v9 < v1->unk_0C; v9++) {
                ov5_021E1674(v1->unk_10[v9], v0->unk_A4);
            }

            (v1->unk_0F)++;
        }
        break;
    case 5:
        FreeToHeap(v1);
        return 1;
    }

    return 0;
}
