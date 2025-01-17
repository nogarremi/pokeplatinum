#include <nitro.h>
#include <string.h>

#include "inlines.h"

#include "struct_decls/struct_0200112C_decl.h"
#include "message.h"
#include "struct_decls/struct_02013A04_decl.h"
#include "struct_decls/sys_task.h"
#include "strbuf.h"
#include "pokemon.h"
#include "struct_decls/struct_0207D3C0_decl.h"
#include "overlay005/struct_ov5_021DC1A4_decl.h"
#include "overlay005/struct_ov5_021F7ED8_decl.h"

#include "struct_defs/struct_02013A04_t.h"
#include "field/field_system.h"
#include "struct_defs/struct_0205AA50.h"
#include "overlay084/struct_ov84_02240FA8.h"

#include "unk_0200112C.h"
#include "unk_02005474.h"
#include "message.h"
#include "string_template.h"
#include "unk_0200D9E8.h"
#include "unk_0200DA60.h"
#include "unk_0200F174.h"
#include "heap.h"
#include "unk_02018340.h"
#include "strbuf.h"
#include "unk_0202631C.h"
#include "field_script_context.h"
#include "unk_0203E880.h"
#include "unk_02054884.h"
#include "constants/species.h"
#include "constants/forms.h"
#include "pokemon.h"
#include "party.h"
#include "unk_0207D3B8.h"
#include "overlay005/ov5_021DC018.h"
#include "overlay005/ov5_021F77A8.h"

typedef struct {
    u16 moveID;
    u8 unk_02;
    u8 unk_03;
    u8 unk_04;
    u8 unk_05;
    u32 shardColor; // the type of underground shard you use to trade to the move tutors
} TeachableMove;

static const TeachableMove sTeachableMoves[] = {
    { MOVE_DIVE,          0x2, 0x4, 0x2, 0x0, 0x0 },
    { MOVE_MUD_SLAP,      0x4, 0x4, 0x0, 0x0, 0x1 },
    { MOVE_FURY_CUTTER,   0x0, 0x8, 0x0, 0x0, 0x0 },
    { MOVE_ICY_WIND,      0x0, 0x6, 0x0, 0x2, 0x0 },
    { MOVE_ROLLOUT,       0x4, 0x2, 0x0, 0x2, 0x1 },
    { MOVE_THUNDER_PUNCH, 0x2, 0x6, 0x0, 0x0, 0x0 },
    { MOVE_FIRE_PUNCH,    0x2, 0x6, 0x0, 0x0, 0x0 },
    { MOVE_SUPERPOWER,    0x8, 0x0, 0x0, 0x0, 0x1 },
    { MOVE_ICE_PUNCH,     0x2, 0x6, 0x0, 0x0, 0x0 },
    { MOVE_IRON_HEAD,     0x6, 0x0, 0x2, 0x0, 0x1 },
    { MOVE_AQUA_TAIL,     0x6, 0x0, 0x0, 0x2, 0x1 },
    { MOVE_OMINOUS_WIND,  0x0, 0x6, 0x0, 0x2, 0x0 },
    { MOVE_GASTRO_ACID,   0x4, 0x0, 0x2, 0x2, 0x1 },
    { MOVE_SNORE,         0x2, 0x0, 0x4, 0x2, 0x2 },
    { MOVE_SPITE,         0x0, 0x0, 0x8, 0x0, 0x2 },
    { MOVE_AIR_CUTTER,    0x2, 0x4, 0x0, 0x2, 0x0 },
    { MOVE_HELPING_HAND,  0x2, 0x0, 0x4, 0x2, 0x2 },
    { MOVE_ENDEAVOR,      0x4, 0x0, 0x4, 0x0, 0x1 },
    { MOVE_OUTRAGE,       0x6, 0x0, 0x2, 0x0, 0x1 },
    { MOVE_ANCIENT_POWER, 0x6, 0x0, 0x0, 0x2, 0x1 },
    { MOVE_SYNTHESIS,     0x0, 0x0, 0x2, 0x6, 0x2 },
    { MOVE_SIGNAL_BEAM,   0x2, 0x2, 0x2, 0x2, 0x1 },
    { MOVE_ZEN_HEADBUTT,  0x0, 0x4, 0x4, 0x0, 0x0 },
    { MOVE_VACUUM_WAVE,   0x2, 0x4, 0x0, 0x2, 0x0 },
    { MOVE_EARTH_POWER,   0x6, 0x0, 0x0, 0x2, 0x1 },
    { MOVE_GUNK_SHOT,     0x4, 0x2, 0x0, 0x2, 0x1 },
    { MOVE_TWISTER,       0x6, 0x0, 0x0, 0x2, 0x1 },
    { MOVE_SEED_BOMB,     0x4, 0x0, 0x0, 0x4, 0x1 },
    { MOVE_IRON_DEFENSE,  0x4, 0x2, 0x2, 0x0, 0x1 },
    { MOVE_MAGNET_RISE,   0x0, 0x2, 0x4, 0x2, 0x2 },
    { MOVE_LAST_RESORT,   0x0, 0x0, 0x0, 0x8, 0x2 },
    { MOVE_BOUNCE,        0x4, 0x0, 0x2, 0x2, 0x1 },
    { MOVE_TRICK,         0x0, 0x4, 0x4, 0x0, 0x0 },
    { MOVE_HEAT_WAVE,     0x4, 0x2, 0x0, 0x2, 0x1 },
    { MOVE_KNOCK_OFF,     0x4, 0x4, 0x0, 0x0, 0x0 },
    { MOVE_SUCKER_PUNCH,  0x0, 0x6, 0x2, 0x0, 0x0 },
    { MOVE_SWIFT,         0x0, 0x2, 0x2, 0x4, 0x2 },
    { MOVE_UPROAR,        0x0, 0x0, 0x6, 0x2, 0x2 }
};

#define MOVESET_MASK_SIZE (s32)((NELEMS(sTeachableMoves) + 7) / 8)

// Each of the bits in this array correspond to a move in sTeachableMoves
// Therefore the size is dependent on how many teachable moves exist

typedef struct {
    u8 maskData[MOVESET_MASK_SIZE];
} MovesetMask;

const MovesetMask sTeachableMovesets[MOVESET_MAX] = {
    { 0x6,  0x20, 0x10, 0x8,  0x4  },
    { 0x6,  0x20, 0x10, 0x8,  0x4  },
    { 0x6,  0x20, 0x14, 0x8,  0x4  },
    { 0x66, 0x20, 0x0,  0x0,  0x12 },
    { 0x66, 0x20, 0x0,  0x0,  0x12 },
    { 0x66, 0xA8, 0x4,  0x4,  0x12 },
    { 0x1B, 0x25, 0x40, 0x10, 0x0  },
    { 0x1B, 0x25, 0x40, 0x10, 0x0  },
    { 0x1B, 0x25, 0x64, 0x10, 0x0  },
    { 0x0,  0x20, 0x0,  0x0,  0x0  },
    { 0x0,  0x0,  0x0,  0x10, 0x0  },
    { 0x0,  0xA8, 0x20, 0x4,  0x10 },
    { 0x0,  0x0,  0x0,  0x0,  0x0  },
    { 0x0,  0x0,  0x0,  0x10, 0x0  },
    { 0x4,  0xA8, 0x2,  0x0,  0x14 },
    { 0x2,  0xA8, 0x0,  0x4,  0x32 },
    { 0x2,  0xA8, 0x0,  0x4,  0x32 },
    { 0x2,  0xA8, 0x0,  0x4,  0x32 },
    { 0xA,  0x20, 0x42, 0x40, 0x18 },
    { 0xA,  0x20, 0x42, 0x40, 0x18 },
    { 0x2,  0xA8, 0x0,  0x4,  0x12 },
    { 0x2,  0xA8, 0x0,  0x4,  0x12 },
    { 0x0,  0x74, 0x0,  0xA,  0x0  },
    { 0x0,  0x74, 0x0,  0xA,  0x0  },
    { 0x32, 0x20, 0x21, 0x20, 0x14 },
    { 0x32, 0x20, 0x21, 0x20, 0x14 },
    { 0x16, 0x20, 0x0,  0x1,  0x14 },
    { 0x16, 0x20, 0x0,  0x1,  0x14 },
    { 0x2,  0x20, 0x1,  0x0,  0x0  },
    { 0x2,  0x20, 0x1,  0x0,  0x0  },
    { 0xEE, 0x25, 0x5,  0x1,  0x20 },
    { 0x2,  0x20, 0x1,  0x0,  0x8  },
    { 0x2,  0x20, 0x1,  0x0,  0x8  },
    { 0xEE, 0x25, 0x5,  0x1,  0x28 },
    { 0x7A, 0x21, 0x63, 0xC0, 0x5  },
    { 0x7A, 0x21, 0x63, 0xC0, 0x5  },
    { 0x0,  0x68, 0x40, 0x0,  0x12 },
    { 0x0,  0x68, 0x40, 0x0,  0x12 },
    { 0x7A, 0x21, 0x3,  0xC0, 0x4  },
    { 0x7A, 0x21, 0x3,  0xC0, 0x4  },
    { 0x0,  0xA8, 0x40, 0x4,  0x32 },
    { 0x0,  0xA8, 0x40, 0x4,  0x32 },
    { 0x0,  0x30, 0x10, 0x8,  0x0  },
    { 0x0,  0x30, 0x10, 0x8,  0x0  },
    { 0x0,  0x30, 0x10, 0x8,  0x0  },
    { 0x4,  0x20, 0x10, 0x8,  0x4  },
    { 0x4,  0x20, 0x10, 0x8,  0x4  },
    { 0x0,  0x20, 0x60, 0x0,  0x10 },
    { 0x0,  0xA8, 0x60, 0x4,  0x10 },
    { 0x2,  0x20, 0x0,  0x1,  0x8  },
    { 0x2,  0x20, 0x0,  0x1,  0x8  },
    { 0xA,  0x60, 0x0,  0x4A, 0x34 },
    { 0xA,  0x60, 0x0,  0x4A, 0x34 },
    { 0xB,  0x25, 0x60, 0x0,  0x10 },
    { 0xF,  0x25, 0x60, 0x0,  0x10 },
    { 0x62, 0x41, 0x87, 0xA,  0x30 },
    { 0x62, 0x41, 0x87, 0xA,  0x30 },
    { 0x2,  0x20, 0x1,  0x0,  0x12 },
    { 0x2,  0x22, 0x1,  0x0,  0x12 },
    { 0x9,  0x20, 0x1,  0x0,  0x0  },
    { 0xB,  0x21, 0x1,  0x0,  0x0  },
    { 0xB,  0x21, 0x81, 0x0,  0x0  },
    { 0x60, 0x21, 0x60, 0x0,  0x5  },
    { 0x60, 0x21, 0x60, 0x0,  0x5  },
    { 0x60, 0x21, 0x60, 0x0,  0x5  },
    { 0xE2, 0x21, 0x81, 0x0,  0x0  },
    { 0xE2, 0x21, 0x81, 0x0,  0x0  },
    { 0xE2, 0x21, 0x81, 0x0,  0x0  },
    { 0x0,  0x30, 0x10, 0x8,  0xC  },
    { 0x0,  0x30, 0x10, 0x8,  0xC  },
    { 0x0,  0x30, 0x10, 0x8,  0xC  },
    { 0x9,  0x20, 0x0,  0x0,  0x4  },
    { 0x9,  0x20, 0x0,  0x0,  0x4  },
    { 0xF2, 0x20, 0x8,  0x1,  0x8  },
    { 0xF2, 0x20, 0x8,  0x1,  0x8  },
    { 0xF6, 0x22, 0x8,  0x1,  0x8  },
    { 0x0,  0x20, 0x0,  0x80, 0x12 },
    { 0x0,  0x20, 0x0,  0x80, 0x12 },
    { 0xB,  0x24, 0x60, 0x0,  0x11 },
    { 0xF,  0x25, 0x60, 0x10, 0x11 },
    { 0x10, 0x20, 0x20, 0x30, 0x10 },
    { 0x10, 0x20, 0x20, 0x30, 0x10 },
    { 0x6,  0xA8, 0x0,  0x44, 0x36 },
    { 0x2,  0xA0, 0x2,  0x0,  0x34 },
    { 0x2,  0xA0, 0x2,  0x0,  0x34 },
    { 0x9,  0x24, 0x20, 0x0,  0x0  },
    { 0x9,  0x24, 0x20, 0x0,  0x0  },
    { 0x62, 0x21, 0x0,  0x2,  0x0  },
    { 0x62, 0x21, 0x0,  0x2,  0x0  },
    { 0x9,  0x20, 0x0,  0x10, 0x10 },
    { 0x9,  0x20, 0x20, 0x10, 0x10 },
    { 0x68, 0x69, 0x0,  0x0,  0x2D },
    { 0x68, 0x69, 0x0,  0x0,  0x2D },
    { 0x68, 0x69, 0x0,  0x0,  0x2D },
    { 0x12, 0x22, 0x8,  0x5,  0x0  },
    { 0x60, 0x1,  0x60, 0x0,  0x1  },
    { 0x60, 0x1,  0x60, 0x0,  0x1  },
    { 0x8F, 0x20, 0x8,  0x10, 0x4  },
    { 0x8F, 0x20, 0x8,  0x10, 0x4  },
    { 0x10, 0x20, 0x20, 0x20, 0x18 },
    { 0x10, 0x20, 0x20, 0x20, 0x18 },
    { 0x10, 0x20, 0x18, 0x8,  0x20 },
    { 0x10, 0x20, 0x58, 0x8,  0x0  },
    { 0x6E, 0x20, 0x2,  0x11, 0x24 },
    { 0x6E, 0x20, 0x6,  0x11, 0x24 },
    { 0x82, 0x20, 0x81, 0x80, 0x1C },
    { 0x62, 0x21, 0x81, 0x0,  0x10 },
    { 0x7A, 0x25, 0x40, 0x0,  0x4  },
    { 0x10, 0x60, 0x0,  0x0,  0x20 },
    { 0x10, 0x60, 0x0,  0x0,  0x20 },
    { 0x9A, 0x64, 0xA,  0x1,  0x20 },
    { 0xFE, 0x65, 0xE,  0x1,  0x20 },
    { 0x7A, 0x21, 0x43, 0x40, 0x0  },
    { 0x0,  0x20, 0x18, 0x8,  0x4  },
    { 0x6E, 0x65, 0x7,  0x0,  0x28 },
    { 0x9,  0x20, 0x24, 0x84, 0x10 },
    { 0x9,  0x20, 0x24, 0x84, 0x10 },
    { 0xF,  0x24, 0x0,  0x80, 0x14 },
    { 0xF,  0x24, 0x0,  0x80, 0x14 },
    { 0x19, 0x20, 0x20, 0x4,  0x10 },
    { 0x19, 0x20, 0x20, 0x4,  0x11 },
    { 0x62, 0x21, 0x61, 0x10, 0x1  },
    { 0x4,  0x28, 0x0,  0x0,  0x14 },
    { 0xA,  0x21, 0x61, 0x0,  0x1  },
    { 0x62, 0x21, 0x21, 0x20, 0x10 },
    { 0x62, 0x20, 0x1,  0x0,  0x2  },
    { 0x84, 0x20, 0x0,  0x10, 0x4  },
    { 0x8,  0x62, 0x47, 0x0,  0x20 },
    { 0x0,  0x0,  0x0,  0x80, 0x0  },
    { 0x9,  0x66, 0x4,  0x84, 0x20 },
    { 0x9,  0x26, 0x6C, 0x0,  0x0  },
    { 0x0,  0x0,  0x0,  0x0,  0x0  },
    { 0x2,  0x20, 0x1,  0x40, 0x10 },
    { 0xB,  0x24, 0x21, 0x40, 0x10 },
    { 0x2,  0x20, 0x21, 0x60, 0x10 },
    { 0x82, 0x20, 0x1,  0x40, 0x12 },
    { 0x8,  0x20, 0x60, 0x40, 0x11 },
    { 0x19, 0x20, 0x8,  0x11, 0x4  },
    { 0x19, 0x20, 0x8,  0x11, 0x4  },
    { 0x1A, 0x20, 0x8,  0x11, 0x4  },
    { 0x9F, 0x24, 0x8,  0x11, 0x4  },
    { 0x0,  0xAE, 0x8,  0x5,  0x12 },
    { 0xFA, 0x23, 0x44, 0x4A, 0x0  },
    { 0xA,  0xA8, 0x28, 0x4,  0x10 },
    { 0x2,  0xA8, 0x28, 0x4,  0x12 },
    { 0x2,  0xA8, 0x8,  0x4,  0x12 },
    { 0x8,  0x24, 0x4,  0x4,  0x10 },
    { 0x8,  0x24, 0x4,  0x4,  0x10 },
    { 0xEF, 0xAF, 0x4,  0x4,  0x12 },
    { 0x6A, 0x25, 0x60, 0x0,  0x11 },
    { 0xFF, 0xFF, 0xFF, 0xFF, 0x3F },
    { 0x6,  0x20, 0x18, 0x8,  0x0  },
    { 0x6,  0x20, 0x18, 0x8,  0x0  },
    { 0x6,  0x20, 0x1C, 0x8,  0x0  },
    { 0x12, 0x20, 0x0,  0x0,  0x12 },
    { 0x16, 0x20, 0x0,  0x0,  0x12 },
    { 0x76, 0x20, 0x0,  0x0,  0x12 },
    { 0x8B, 0x65, 0x8,  0x0,  0x20 },
    { 0x8F, 0x61, 0x8,  0x0,  0x20 },
    { 0x8F, 0x65, 0xC,  0x0,  0x20 },
    { 0x76, 0x25, 0x1,  0x40, 0x3C },
    { 0x76, 0x25, 0x1,  0x40, 0x3C },
    { 0x2,  0x88, 0x40, 0x4,  0x32 },
    { 0x2,  0x88, 0x40, 0x4,  0x32 },
    { 0x30, 0xA9, 0x0,  0x0,  0x34 },
    { 0x30, 0xA9, 0x0,  0x0,  0x34 },
    { 0x0,  0x0,  0x20, 0x80, 0x8  },
    { 0x0,  0x0,  0x20, 0x80, 0x8  },
    { 0x0,  0xA8, 0x40, 0x4,  0x32 },
    { 0x9,  0x20, 0x20, 0x80, 0x8  },
    { 0x9,  0x24, 0x20, 0x80, 0x8  },
    { 0x12, 0x20, 0x21, 0x20, 0x30 },
    { 0x1A, 0x20, 0x63, 0x40, 0x21 },
    { 0x1A, 0x20, 0x3,  0xC0, 0x20 },
    { 0x12, 0x20, 0x6A, 0x40, 0x31 },
    { 0x12, 0xA8, 0x6A, 0x44, 0x13 },
    { 0x0,  0xA8, 0x60, 0x4,  0x1B },
    { 0x0,  0xA8, 0x60, 0x4,  0x1B },
    { 0x0,  0x20, 0x20, 0x20, 0x10 },
    { 0x60, 0x20, 0x20, 0x20, 0x10 },
    { 0x60, 0x20, 0x24, 0x20, 0x10 },
    { 0x0,  0x30, 0x10, 0x8,  0x20 },
    { 0x9B, 0x25, 0x1,  0x0,  0x14 },
    { 0x9B, 0x25, 0x1,  0x0,  0x14 },
    { 0x72, 0x21, 0x1,  0x1,  0x8  },
    { 0xB,  0x20, 0x1,  0x80, 0x0  },
    { 0x0,  0x20, 0x11, 0x88, 0x0  },
    { 0x0,  0x20, 0x11, 0x88, 0x0  },
    { 0x0,  0x20, 0x11, 0x88, 0x0  },
    { 0x66, 0x61, 0x0,  0xCA, 0x34 },
    { 0x0,  0x20, 0x13, 0x8,  0x20 },
    { 0x0,  0x20, 0x13, 0x8,  0x20 },
    { 0x0,  0xA8, 0x28, 0x0,  0x30 },
    { 0x1B, 0x25, 0x8,  0x1,  0x0  },
    { 0x1B, 0x25, 0x8,  0x1,  0x0  },
    { 0x2,  0x20, 0x61, 0x40, 0x11 },
    { 0x2,  0x60, 0x1,  0x40, 0x18 },
    { 0xA,  0xC8, 0x0,  0x4,  0x3A },
    { 0xF,  0x25, 0x60, 0x10, 0x11 },
    { 0x8,  0x68, 0x0,  0x0,  0x39 },
    { 0x0,  0x0,  0x0,  0x0,  0x0  },
    { 0x0,  0x0,  0x0,  0x0,  0x0  },
    { 0x2,  0x20, 0x60, 0x0,  0x39 },
    { 0x10, 0x20, 0x0,  0x10, 0x0  },
    { 0x10, 0x20, 0x20, 0x30, 0x0  },
    { 0x12, 0x64, 0x4A, 0x40, 0x0  },
    { 0x4,  0x24, 0x0,  0x1,  0x14 },
    { 0x12, 0x26, 0x8,  0x25, 0x0  },
    { 0xE2, 0x21, 0x0,  0x40, 0x0  },
    { 0xE2, 0x21, 0x0,  0x40, 0x0  },
    { 0x19, 0x24, 0x20, 0x80, 0x10 },
    { 0x84, 0x2A, 0x0,  0x10, 0x14 },
    { 0x12, 0x30, 0x9,  0x1,  0x0  },
    { 0x4,  0x20, 0x81, 0x10, 0x4  },
    { 0xE,  0x61, 0x0,  0x0,  0x14 },
    { 0xF6, 0x21, 0x0,  0x4A, 0x10 },
    { 0xF6, 0x21, 0x0,  0x4A, 0x30 },
    { 0x12, 0x20, 0x8,  0x11, 0x2  },
    { 0x12, 0x20, 0x8,  0x11, 0x2  },
    { 0x8A, 0x20, 0xA,  0x1,  0x0  },
    { 0x8A, 0x20, 0xA,  0x1,  0x0  },
    { 0x1A, 0x20, 0xA,  0x1,  0x8  },
    { 0xB,  0x20, 0x20, 0x8A, 0x10 },
    { 0xB,  0x20, 0x20, 0x8A, 0x10 },
    { 0x1A, 0x0,  0x20, 0x8A, 0x10 },
    { 0xB,  0xA6, 0x21, 0x8A, 0x10 },
    { 0xE,  0xA8, 0x0,  0x14, 0x10 },
    { 0x2,  0x60, 0x0,  0x0,  0x3A },
    { 0x2,  0x60, 0x0,  0x0,  0x3A },
    { 0x9,  0x22, 0x24, 0x84, 0x10 },
    { 0x92, 0x20, 0xA,  0xB,  0x4  },
    { 0x92, 0x20, 0xA,  0x9B, 0x4  },
    { 0x8,  0x20, 0x60, 0x40, 0x11 },
    { 0x2,  0x60, 0x60, 0xC0, 0x38 },
    { 0x0,  0x0,  0x0,  0x0,  0x0  },
    { 0x2,  0x20, 0x81, 0x0,  0x30 },
    { 0x12, 0x20, 0x83, 0x4,  0x18 },
    { 0xA,  0x21, 0x61, 0x0,  0x21 },
    { 0x62, 0x21, 0x21, 0x20, 0x30 },
    { 0x62, 0x20, 0x1,  0x0,  0x22 },
    { 0x7A, 0x23, 0x41, 0x0,  0x0  },
    { 0x7A, 0x21, 0x43, 0x40, 0x0  },
    { 0x2,  0x22, 0x20, 0x20, 0x10 },
    { 0x2,  0x22, 0x0,  0x0,  0x12 },
    { 0xB,  0x2A, 0x20, 0x0,  0x10 },
    { 0x82, 0x62, 0x8,  0x1,  0x20 },
    { 0x82, 0x62, 0x8,  0x11, 0x20 },
    { 0xE6, 0x67, 0xC,  0x1,  0x20 },
    { 0xB,  0xAE, 0x68, 0x5,  0x11 },
    { 0x2,  0xAA, 0x68, 0x5,  0x12 },
    { 0x2,  0x20, 0x79, 0x49, 0x39 },
    { 0x26, 0x20, 0x12, 0x8,  0x10 },
    { 0x26, 0x20, 0x12, 0x8,  0x10 },
    { 0x26, 0x20, 0x16, 0x8,  0x10 },
    { 0x2,  0x20, 0x1,  0xC0, 0x12 },
    { 0x66, 0x20, 0x81, 0xC0, 0x12 },
    { 0xE6, 0x20, 0x81, 0xC0, 0x16 },
    { 0x9B, 0x24, 0xA,  0x1,  0x0  },
    { 0x9B, 0x25, 0xA,  0x1,  0x0  },
    { 0x9B, 0x25, 0xE,  0x1,  0x0  },
    { 0x2,  0x60, 0x0,  0x0,  0x28 },
    { 0x2,  0x60, 0x0,  0x0,  0x28 },
    { 0x1E, 0x20, 0x1,  0x4A, 0x11 },
    { 0x1E, 0x20, 0x1,  0x4A, 0x11 },
    { 0x0,  0x20, 0x0,  0x0,  0x0  },
    { 0x0,  0x0,  0x0,  0x10, 0x0  },
    { 0x0,  0xA8, 0x20, 0x4,  0x10 },
    { 0x0,  0x0,  0x0,  0x10, 0x0  },
    { 0x0,  0xA8, 0x20, 0x4,  0x10 },
    { 0x8,  0x20, 0x50, 0x8,  0x20 },
    { 0x6B, 0x21, 0x50, 0x8,  0x20 },
    { 0x6B, 0x21, 0x50, 0x8,  0x20 },
    { 0x10, 0x60, 0x10, 0x8,  0x0  },
    { 0x16, 0x60, 0x10, 0x8,  0x10 },
    { 0x1E, 0xE8, 0x10, 0x8C, 0x1C },
    { 0x2,  0xA8, 0x2,  0x4,  0x12 },
    { 0x2,  0xA8, 0x2,  0x4,  0x12 },
    { 0xA,  0xA8, 0x0,  0x4,  0x34 },
    { 0xA,  0xA8, 0x0,  0xE,  0x34 },
    { 0x6A, 0x21, 0x61, 0x0,  0x11 },
    { 0x6A, 0x21, 0x61, 0x0,  0x11 },
    { 0x6A, 0x21, 0x61, 0x0,  0x11 },
    { 0xA,  0x20, 0x20, 0x0,  0x10 },
    { 0xA,  0xA8, 0x20, 0x4,  0x10 },
    { 0x0,  0x20, 0x11, 0x8,  0x0  },
    { 0xA6, 0x20, 0x91, 0x8,  0x0  },
    { 0x6E, 0x21, 0x0,  0x2,  0x8  },
    { 0x6E, 0x1,  0x0,  0x2,  0x28 },
    { 0x6E, 0x21, 0x0,  0x2,  0x8  },
    { 0x6,  0x60, 0x0,  0x0,  0x0  },
    { 0x6,  0xE8, 0x0,  0x0,  0x30 },
    { 0x6,  0x60, 0x0,  0x0,  0x9  },
    { 0x7A, 0x21, 0x40, 0x0,  0x20 },
    { 0x7A, 0x21, 0x40, 0x0,  0x20 },
    { 0x7A, 0x21, 0x44, 0x0,  0x20 },
    { 0xE2, 0x21, 0x81, 0x0,  0x4  },
    { 0xE2, 0x23, 0x81, 0x0,  0x4  },
    { 0x1A, 0x20, 0x1,  0x0,  0x34 },
    { 0x72, 0x21, 0x8,  0x31, 0x0  },
    { 0x1A, 0x20, 0x41, 0x40, 0x18 },
    { 0x1A, 0x20, 0x41, 0x40, 0x18 },
    { 0x6E, 0x69, 0x60, 0x0,  0xD  },
    { 0x2A, 0x23, 0x8,  0x30, 0xC  },
    { 0x96, 0x62, 0xA,  0x31, 0x20 },
    { 0x96, 0x62, 0xA,  0x31, 0x20 },
    { 0xFE, 0x67, 0xE,  0x31, 0x20 },
    { 0x62, 0x21, 0xE1, 0x0,  0x11 },
    { 0x62, 0x21, 0xE1, 0x0,  0x11 },
    { 0x2,  0x20, 0x20, 0x20, 0x10 },
    { 0x2,  0x20, 0x20, 0x20, 0x10 },
    { 0x32, 0x20, 0x21, 0x60, 0x30 },
    { 0x32, 0x20, 0x21, 0x60, 0x30 },
    { 0x22, 0xA9, 0x61, 0x0,  0x10 },
    { 0x22, 0xA9, 0x41, 0x0,  0x10 },
    { 0x6,  0x20, 0x10, 0x8,  0x10 },
    { 0x72, 0x31, 0x0,  0xA,  0x0  },
    { 0x72, 0x31, 0x0,  0xA,  0x0  },
    { 0xF,  0x60, 0x48, 0x80, 0x30 },
    { 0xF,  0x60, 0x48, 0x80, 0x30 },
    { 0x19, 0x20, 0x0,  0x80, 0x0  },
    { 0x19, 0x22, 0x0,  0x80, 0x0  },
    { 0x12, 0x20, 0x0,  0x1,  0x2  },
    { 0x12, 0x22, 0x0,  0x1,  0x2  },
    { 0x12, 0x20, 0x0,  0x11, 0x2  },
    { 0x8,  0x20, 0x60, 0x80, 0x11 },
    { 0x6A, 0x21, 0x60, 0x80, 0x11 },
    { 0x7A, 0x21, 0x41, 0x40, 0x38 },
    { 0x6,  0x20, 0x0,  0x1,  0x0  },
    { 0x6,  0xA8, 0x4,  0x5,  0x12 },
    { 0x66, 0xA8, 0x4,  0x5,  0x12 },
    { 0x26, 0x60, 0x10, 0x8,  0x8  },
    { 0xA6, 0x60, 0x10, 0x8,  0x8  },
    { 0x2,  0xA8, 0x4,  0x4,  0x32 },
    { 0x2,  0xA8, 0x4,  0x4,  0x32 },
    { 0x7E, 0x21, 0x2,  0x40, 0x14 },
    { 0x6,  0x24, 0x0,  0x0,  0x1C },
    { 0x10, 0x22, 0x69, 0x1,  0x10 },
    { 0x10, 0x22, 0x69, 0x11, 0x10 },
    { 0xB,  0x24, 0x0,  0x81, 0x0  },
    { 0xB,  0x24, 0x40, 0x81, 0x0  },
    { 0x8E, 0x60, 0xA,  0x10, 0x4  },
    { 0x8F, 0x60, 0xA,  0x10, 0x14 },
    { 0x2,  0x20, 0x68, 0x1,  0x1  },
    { 0x2,  0x20, 0x68, 0x1,  0x1  },
    { 0x2,  0x30, 0x18, 0x9,  0x0  },
    { 0x2,  0x30, 0x18, 0x9,  0x0  },
    { 0x6,  0x20, 0x8,  0x11, 0x4  },
    { 0x86, 0x24, 0x8,  0x11, 0x4  },
    { 0x9,  0x20, 0x0,  0x0,  0x10 },
    { 0xB,  0x26, 0x0,  0x4,  0x10 },
    { 0x8,  0x28, 0x0,  0x40, 0x10 },
    { 0x7E, 0x25, 0x8,  0x40, 0x1D },
    { 0x8,  0x48, 0x0,  0x0,  0xD  },
    { 0xA,  0x48, 0x0,  0x0,  0xD  },
    { 0x8,  0x68, 0x0,  0x0,  0x9  },
    { 0x6A, 0x69, 0x0,  0x0,  0x9  },
    { 0x6,  0xA8, 0x14, 0x4,  0x0  },
    { 0x18, 0x20, 0x61, 0x40, 0x25 },
    { 0x8E, 0x60, 0x40, 0x80, 0x1C },
    { 0x0,  0x0,  0x0,  0x0,  0x0  },
    { 0x18, 0x60, 0x0,  0x0,  0x0  },
    { 0x18, 0x62, 0x20, 0x0,  0x0  },
    { 0x1B, 0x24, 0x20, 0x0,  0x0  },
    { 0x1B, 0x24, 0x20, 0x0,  0x0  },
    { 0x1F, 0x26, 0x20, 0x0,  0x0  },
    { 0x9,  0x20, 0x0,  0x10, 0x0  },
    { 0xB,  0x24, 0x0,  0x80, 0x18 },
    { 0xB,  0x24, 0x20, 0x80, 0x10 },
    { 0xB,  0x24, 0x8,  0x81, 0x0  },
    { 0x9,  0x20, 0x0,  0x80, 0x10 },
    { 0x6,  0x20, 0x44, 0x4,  0x0  },
    { 0x16, 0x20, 0x44, 0x14, 0x0  },
    { 0x16, 0xAC, 0x44, 0x4,  0x12 },
    { 0x0,  0x2,  0x40, 0x10, 0x0  },
    { 0x3E, 0x23, 0x60, 0x30, 0x11 },
    { 0x3E, 0x23, 0x60, 0x30, 0x11 },
    { 0xF2, 0x23, 0x8,  0x1,  0x0  },
    { 0xBA, 0x23, 0x28, 0x0,  0x0  },
    { 0xB2, 0x23, 0x8,  0x30, 0x0  },
    { 0xF,  0x20, 0x45, 0x44, 0x19 },
    { 0xF,  0x20, 0x45, 0x44, 0x11 },
    { 0xB,  0x26, 0x28, 0x0,  0x30 },
    { 0x76, 0x22, 0x8,  0x1,  0x30 },
    { 0xF,  0x26, 0xC,  0x5,  0x30 },
    { 0x6A, 0x23, 0x69, 0x50, 0x31 },
    { 0x6A, 0x21, 0x60, 0x0,  0x15 },
    { 0x82, 0x20, 0x10, 0x9,  0x0  },
    { 0x82, 0x20, 0x10, 0x9,  0x0  },
    { 0x82, 0x22, 0x14, 0x9,  0x0  },
    { 0x72, 0x20, 0x83, 0x2,  0x32 },
    { 0x72, 0x20, 0x83, 0x2,  0x12 },
    { 0x72, 0x20, 0x83, 0x2,  0x12 },
    { 0xB,  0x20, 0x20, 0x0,  0x0  },
    { 0xB,  0x20, 0x20, 0x0,  0x0  },
    { 0xF,  0x20, 0x20, 0x10, 0x4  },
    { 0x2,  0xA8, 0x2,  0x4,  0x12 },
    { 0x2,  0xA8, 0x2,  0x4,  0x12 },
    { 0x2,  0xA8, 0x2,  0x4,  0x12 },
    { 0x9E, 0x24, 0x0,  0x40, 0x10 },
    { 0x9F, 0x24, 0x0,  0x40, 0x10 },
    { 0x2,  0x20, 0x2,  0x0,  0x20 },
    { 0x6,  0x20, 0x2,  0x0,  0x24 },
    { 0x6,  0x20, 0x20, 0x20, 0x10 },
    { 0x6,  0x20, 0x20, 0x20, 0x10 },
    { 0x86, 0x20, 0x20, 0x20, 0x10 },
    { 0x2,  0x20, 0x10, 0x8,  0x30 },
    { 0x6,  0x20, 0x10, 0x8,  0x10 },
    { 0xE2, 0x62, 0x4A, 0x1,  0x20 },
    { 0xE2, 0x62, 0x4E, 0x1,  0x20 },
    { 0x2,  0x22, 0x8,  0x31, 0x0  },
    { 0x2,  0x22, 0xC,  0x31, 0x0  },
    { 0x0,  0x20, 0x0,  0x0,  0x0  },
    { 0x0,  0x20, 0x32, 0x8,  0x28 },
    { 0x2,  0xA8, 0x20, 0x4,  0x10 },
    { 0x2,  0xA8, 0x2,  0x0,  0x10 },
    { 0x6,  0xA8, 0x22, 0x0,  0x10 },
    { 0x32, 0x20, 0x1,  0x6A, 0x30 },
    { 0xB,  0x21, 0x0,  0x0,  0x10 },
    { 0xB,  0x25, 0x0,  0x0,  0x10 },
    { 0x10, 0x20, 0x11, 0x8,  0x0  },
    { 0x10, 0x20, 0x11, 0x8,  0x0  },
    { 0xB,  0x20, 0x8,  0x1,  0x0  },
    { 0xB,  0x20, 0x8,  0x1,  0x0  },
    { 0x66, 0x61, 0x0,  0xCA, 0x34 },
    { 0x1A, 0xE8, 0x0,  0x0,  0x1D },
    { 0x1A, 0xE8, 0x0,  0x0,  0x1D },
    { 0x2,  0x20, 0x3,  0xC0, 0x30 },
    { 0x66, 0x21, 0x3,  0xC0, 0x30 },
    { 0x8,  0x68, 0x0,  0x0,  0x39 },
    { 0x82, 0xC8, 0x0,  0x4,  0x3A },
    { 0x6,  0x20, 0x0,  0x40, 0x1C },
    { 0x16, 0x20, 0x0,  0x40, 0x1C },
    { 0x18, 0x20, 0x61, 0x40, 0x35 },
    { 0x6,  0x20, 0x0,  0x0,  0x18 },
    { 0x6,  0x20, 0x0,  0x0,  0x18 },
    { 0x10, 0x20, 0x28, 0x0,  0x1  },
    { 0x10, 0x22, 0x68, 0x0,  0x1  },
    { 0x10, 0x20, 0x1,  0x1,  0x28 },
    { 0x2,  0x20, 0x21, 0x0,  0x21 },
    { 0x1A, 0x20, 0x43, 0x40, 0x20 },
    { 0x2,  0xA8, 0x0,  0x4,  0x32 },
    { 0x8,  0x68, 0x0,  0x0,  0x29 },
    { 0x6,  0x22, 0x4,  0x5,  0x10 },
    { 0x6,  0x22, 0x4,  0x5,  0x10 },
    { 0x6,  0x26, 0x4,  0x5,  0x10 },
    { 0xFA, 0x21, 0x40, 0x4A, 0x20 },
    { 0x26, 0x21, 0xC1, 0x30, 0x10 },
    { 0x26, 0x21, 0xC1, 0x30, 0x10 },
    { 0x82, 0x20, 0x0,  0x1,  0x0  },
    { 0x82, 0x22, 0x0,  0x1,  0x0  },
    { 0x6,  0x24, 0x0,  0x0,  0x4  },
    { 0x6,  0x24, 0x0,  0x0,  0x4  },
    { 0x2E, 0x61, 0x81, 0x82, 0xC  },
    { 0x2E, 0x61, 0x81, 0x82, 0xC  },
    { 0x6,  0x30, 0x10, 0x8,  0x4  },
    { 0x9,  0xAC, 0x0,  0x84, 0x10 },
    { 0x9,  0xAC, 0x0,  0x84, 0x10 },
    { 0xB,  0xA0, 0x1,  0x80, 0x10 },
    { 0xA,  0x21, 0x10, 0x8,  0x0  },
    { 0xA,  0x21, 0x14, 0x8,  0x0  },
    { 0xE,  0x61, 0x0,  0x0,  0x14 },
    { 0x10, 0x22, 0x20, 0x30, 0x10 },
    { 0x7A, 0x25, 0x40, 0x0,  0x4  },
    { 0xFE, 0x67, 0xE,  0x1,  0x20 },
    { 0x2,  0x20, 0x18, 0x8,  0x4  },
    { 0x62, 0x21, 0x21, 0x20, 0x10 },
    { 0x62, 0x20, 0x1,  0x0,  0x2  },
    { 0x12, 0xA8, 0x6A, 0x44, 0x13 },
    { 0x2,  0xA8, 0x28, 0x0,  0x30 },
    { 0x6,  0x20, 0x11, 0x48, 0x14 },
    { 0xA,  0x24, 0x21, 0x40, 0x10 },
    { 0x6,  0x24, 0x0,  0x1,  0x14 },
    { 0x8E, 0x22, 0xA,  0x1,  0x4  },
    { 0x8,  0x20, 0x60, 0x40, 0x31 },
    { 0x66, 0x21, 0xE1, 0x0,  0x15 },
    { 0x72, 0x23, 0x8,  0x31, 0x0  },
    { 0x6A, 0x69, 0x0,  0x0,  0x9  },
    { 0x1A, 0x69, 0x20, 0x0,  0x9  },
    { 0x2,  0x68, 0x20, 0x0,  0x39 },
    { 0x62, 0x21, 0x61, 0x0,  0x15 },
    { 0x62, 0x21, 0x61, 0x0,  0x15 },
    { 0x62, 0x21, 0x61, 0x40, 0x35 },
    { 0x6,  0x22, 0xC,  0x35, 0x10 },
    { 0x7,  0x24, 0xC,  0x5,  0x10 },
    { 0x2,  0x22, 0x8,  0x11, 0x22 },
    { 0xEA, 0x23, 0x48, 0x1,  0x0  },
    { 0xE,  0xEE, 0xC,  0x5,  0x10 },
    { 0xE,  0x20, 0x61, 0x0,  0x11 },
    { 0xB,  0x20, 0x29, 0xC0, 0x34 },
    { 0xB,  0x20, 0x29, 0xC0, 0x34 },
    { 0xA,  0x68, 0x0,  0x40, 0x1D },
    { 0x2,  0x20, 0x52, 0x49, 0x10 },
    { 0xF,  0x2E, 0x6C, 0x55, 0x13 },
    { 0x82, 0x20, 0x60, 0x0,  0x1  },
    { 0x2,  0x20, 0x60, 0x10, 0x5  },
    { 0x2,  0x20, 0x60, 0x0,  0x15 },
    { 0x12, 0x20, 0x22, 0x1,  0x28 },
    { 0x0,  0x22, 0x22, 0x32, 0x28 },
    { 0xE,  0xEE, 0xC,  0x5,  0x10 },
    { 0x2,  0xA8, 0x50, 0x48, 0x10 },
    { 0x2,  0x68, 0x20, 0x0,  0x39 },
    { 0x2,  0x68, 0x20, 0x0,  0x39 },
    { 0x2,  0x68, 0x20, 0x0,  0x39 },
    { 0x2,  0x68, 0x20, 0x0,  0x39 },
    { 0x2,  0x68, 0x20, 0x0,  0x39 }
};

struct UnkStruct_ov5_021F7ED8_t {
    FieldSystem * unk_00;
    SysTask * unk_04;
    Window unk_08;
    Window * unk_18;
    Strbuf* unk_1C[39];
    MessageLoader * unk_B8;
    StringTemplate * unk_BC;
    u8 unk_C0;
    u8 unk_C1;
    u8 unk_C2;
    u8 unk_C3_0 : 1;
    u8 unk_C3_1 : 1;
    u8 unk_C3_2 : 6;
    u8 unk_C4;
    u8 unk_C5;
    u8 unk_C6;
    u8 unk_C7;
    u16 * unk_C8;
    u16 * unk_CC;
    UnkStruct_ov84_02240FA8 unk_D0;
    UnkStruct_0200112C * unk_F0;
    u16 unk_F4;
    u16 unk_F6;
    ResourceMetadata unk_F8[39];
    u16 unk_230[39];
    u16 unk_27E;
};

BOOL ScrCmd_2E5(ScriptContext * param0);
BOOL ScrCmd_2E9(ScriptContext * param0);
BOOL ScrCmd_2EA(ScriptContext * param0);
BOOL ScrCmd_2EB(ScriptContext * param0);
BOOL ScrCmd_2E6(ScriptContext * param0);
static BOOL ov5_021F7DE8(ScriptContext * param0);
static u16 ov5_021F7A3C(u16 param0);
static u16 ov5_021F7A4C(u16 param0);
static u8 ReadMovesetMaskByte(Pokemon * param0, u8 param1);
static u16 ov5_021F7B60(Pokemon * param0, u16 param1);
static void ov5_021F7E10(UnkStruct_ov5_021F7ED8 * param0, MessageLoader * param1);
static void ov5_021F7E18(FieldSystem * param0, UnkStruct_ov5_021F7ED8 * param1, u8 param2, u8 param3, u8 param4, u8 param5, u16 * param6, StringTemplate * param7, Window * param8, MessageLoader * param9);
UnkStruct_ov5_021F7ED8 * ov5_021F7ED8(FieldSystem * param0, u8 param1, u8 param2, u8 param3, u8 param4, u16 * param5, StringTemplate * param6, Window * param7, MessageLoader * param8);
void ov5_021F7F2C(UnkStruct_ov5_021F7ED8 * param0, u32 param1, u32 param2, u32 param3);
static void ov5_021F7F34(UnkStruct_ov5_021F7ED8 * param0);
static void ov5_021F7FF8(UnkStruct_ov5_021F7ED8 * param0, u32 param1, u32 param2, u32 param3);
static void ov5_021F8090(UnkStruct_ov5_021F7ED8 * param0);
static void ov5_021F819C(UnkStruct_0200112C * param0, u32 param1, u8 param2);
static void ov5_021F81A8(SysTask * param0, void * param1);
static void ov5_021F8250(UnkStruct_ov5_021F7ED8 * param0);

BOOL ScrCmd_337 (ScriptContext * param0)
{
    u16 v0 = sub_0203F150(param0->fieldSys, ScriptContext_ReadHalfWord(param0));
    u16 * v1 = sub_0203F118(param0->fieldSys, ScriptContext_ReadHalfWord(param0));
    PokedexData * v2 = SaveData_Pokedex(param0->fieldSys->saveData);

    *v1 = sub_02026FE8(v2, v0);
    return 0;
}

BOOL ScrCmd_2E5 (ScriptContext * param0)
{
    Pokemon * v0;
    u16 v1 = ScriptContext_GetVar(param0);
    u16 v2 = ScriptContext_GetVar(param0);
    u16 * v3 = ScriptContext_GetVarPointer(param0);

    v0 = Party_GetPokemonBySlotIndex(Party_GetFromSavedata(param0->fieldSys->saveData), v1);
    *v3 = ov5_021F7B60(v0, v2);

    return 0;
}

BOOL ScrCmd_2E9 (ScriptContext * param0)
{
    u16 v0 = ScriptContext_GetVar(param0);
    u16 v1 = ScriptContext_GetVar(param0);
    u16 v2 = ScriptContext_GetVar(param0);

    sub_02054988(Party_GetFromSavedata(param0->fieldSys->saveData), v0, v1, v2);
    return 0;
}

BOOL ScrCmd_2EA (ScriptContext * param0)
{
    int v0;
    u8 v1, v2, v3, v4;
    UnkStruct_0207D3C0 * v5;
    u16 v6 = ScriptContext_GetVar(param0);
    u16 * v7 = ScriptContext_GetVarPointer(param0);

    v5 = sub_0207D990(param0->fieldSys->saveData);

    for (v0 = 0; v0 < (NELEMS(sTeachableMoves)); v0++) {
        if (v6 == sTeachableMoves[v0].moveID) {
            v1 = sTeachableMoves[v0].unk_02;
            v2 = sTeachableMoves[v0].unk_03;
            v3 = sTeachableMoves[v0].unk_04;
            v4 = sTeachableMoves[v0].unk_05;
            break;
        }
    }

    if (v0 == (NELEMS(sTeachableMoves))) {
        GF_ASSERT(0);
        *v7 = 0;
        return 0;
    }

    *v7 = 1;

    if (v1) {
        if (sub_0207D688(v5, 72, v1, 32) == 0) {
            *v7 = 0;
        }
    }

    if (v2) {
        if (sub_0207D688(v5, 73, v2, 32) == 0) {
            *v7 = 0;
        }
    }

    if (v3) {
        if (sub_0207D688(v5, 74, v3, 32) == 0) {
            *v7 = 0;
        }
    }

    if (v4) {
        if (sub_0207D688(v5, 75, v4, 32) == 0) {
            *v7 = 0;
        }
    }

    return 0;
}

BOOL ScrCmd_2EB (ScriptContext * param0)
{
    int v0;
    u8 v1, v2, v3, v4;
    UnkStruct_0207D3C0 * v5;
    u16 v6 = ScriptContext_GetVar(param0);

    v5 = sub_0207D990(param0->fieldSys->saveData);

    for (v0 = 0; v0 < (NELEMS(sTeachableMoves)); v0++) {
        if (v6 == sTeachableMoves[v0].moveID) {
            v1 = sTeachableMoves[v0].unk_02;
            v2 = sTeachableMoves[v0].unk_03;
            v3 = sTeachableMoves[v0].unk_04;
            v4 = sTeachableMoves[v0].unk_05;
            break;
        }
    }

    if (v0 == (NELEMS(sTeachableMoves))) {
        GF_ASSERT(0);
    }

    Bag_SubtractItem(v5, 72, v1, 32);
    Bag_SubtractItem(v5, 73, v2, 32);
    Bag_SubtractItem(v5, 74, v3, 32);
    Bag_SubtractItem(v5, 75, v4, 32);

    return 0;
}

static u16 ov5_021F7A3C (u16 param0)
{
    return sTeachableMoves[param0].moveID;
}

static u16 ov5_021F7A4C (u16 param0)
{
    int v0;

    for (v0 = 0; v0 < (NELEMS(sTeachableMoves)); v0++) {
        if (sTeachableMoves[v0].moveID == param0) {
            return v0;
        }
    }

    GF_ASSERT(FALSE);
    return 0;
}

static u8 ReadMovesetMaskByte (Pokemon * pokemon, u8 offset)
{
    u32 species = Pokemon_GetValue(pokemon, MON_DATA_SPECIES, NULL);
    u32 form = Pokemon_GetValue(pokemon, MON_DATA_FORM, NULL);
    u16 moveset = species;

    switch (species) {
    case SPECIES_DEOXYS:
        if (form == 1) {
            moveset = MOVESET_FORM_DEOXYS_ATTACK;
        } else if (form == 2) {
            moveset = MOVESET_FORM_DEOXYS_DEFENSE;
        } else if (form == 3) {
            moveset = MOVESET_FORM_DEOXYS_SPEED;
        }
        break;
    case SPECIES_WORMADAM:
        if (form == 1) {
            moveset = MOVESET_FORM_WORMADAM_SANDY;
        } else if (form == 2) {
            moveset = MOVESET_FORM_WORMADAM_TRASH;
        }
        break;
    case SPECIES_GIRATINA:
        if (form == 1) {
            moveset = MOVESET_FORM_GIRATINA_ORIGIN;
        }
        break;
    case SPECIES_SHAYMIN:
        if (form == 1) {
            moveset = MOVESET_FORM_SHAYMIN_SKY;
        }
        break;
    case SPECIES_ROTOM:
        if (form == 1) {
            moveset = MOVESET_FORM_ROTOM_HEAT;
        } else if (form == 2) {
            moveset = MOVESET_FORM_ROTOM_WASH;
        } else if (form == 3) {
            moveset = MOVESET_FORM_ROTOM_FROST;
        } else if (form == 4) {
            moveset = MOVESET_FORM_ROTOM_FAN;
        } else if (form == 5) {
            moveset = MOVESET_FORM_ROTOM_MOW;
        }
        break;
    }

    return sTeachableMovesets[moveset - 1].maskData[offset];
}

static u16 ov5_021F7B60 (Pokemon * param0, u16 param1)
{
    int v0, v1, v2;
    u8 v3, v4;
    u32 v5;
    u16 v6[4];

    v5 = Pokemon_GetValue(param0, MON_DATA_SPECIES, NULL);

    for (v2 = 0; v2 < 4; v2++) {
        v6[v2] = Pokemon_GetValue(param0, MON_DATA_MOVE1 + v2, NULL);
    }

    for (v0 = 0; v0 < MOVESET_MASK_SIZE; v0++) {
        v3 = ReadMovesetMaskByte(param0, v0);

        for (v1 = 0; v1 < 8; v1++) {
            v4 = ((v3 >> v1) & 0x1);

            if ((v4 == 1) && (param1 == sTeachableMoves[v0 * 8 + v1].shardColor)) {
                for (v2 = 0; v2 < 4; v2++) {
                    if (v6[v2] == sTeachableMoves[v0 * 8 + v1].moveID) {
                        break;
                    }
                }

                if (v2 == 4) {
                    return 1;
                }
            }
        }
    }

    return 0;
}

BOOL ScrCmd_2E6 (ScriptContext * param0)
{
    u8 v0, v1;
    int v2, v3, v4, v5;
    Pokemon * v6;
    MessageLoader * v7;
    MessageLoader * v8;
    FieldSystem * v9 = param0->fieldSys;
    UnkStruct_ov5_021F7ED8 * v10;
    u16 v11[4];
    u16 v12[(NELEMS(sTeachableMoves))];
    StringTemplate ** v13 = sub_0203F098(v9, 15);
    u16 v14 = ScriptContext_GetVar(param0);
    u16 v15 = ScriptContext_GetVar(param0);
    u16 v16 = ScriptContext_ReadHalfWord(param0);

    param0->data[0] = v16;

    if (v14 != 0xff) {
        v6 = Party_GetPokemonBySlotIndex(Party_GetFromSavedata(param0->fieldSys->saveData), v14);
    }

    v7 = MessageLoader_Init(0, 26, 647, 32);
    v10 = ov5_021F7ED8(v9, 20, 1, 0, 1, sub_0203F118(v9, v16), *v13, sub_0203F098(param0->fieldSys, 1), v7);

    for (v2 = 0; v2 < (NELEMS(sTeachableMoves)); v2++) {
        v12[v2] = 0;
    }

    v3 = 0;

    if (v14 != 0xff) {
        for (v5 = 0; v5 < 4; v5++) {
            v11[v5] = Pokemon_GetValue(v6, (54 + v5), NULL);
        }

        for (v2 = 0; v2 < MOVESET_MASK_SIZE; v2++) {
            v0 = ReadMovesetMaskByte(v6, v2);

            for (v4 = 0; v4 < 8; v4++) {
                v1 = ((v0 >> v4) & 0x1);

                if ((v1 == 1) && (v15 == sTeachableMoves[v2 * 8 + v4].shardColor)) {
                    for (v5 = 0; v5 < 4; v5++) {
                        if (v11[v5] == sTeachableMoves[v2 * 8 + v4].moveID) {
                            break;
                        }
                    }

                    if (v5 == 4) {
                        v12[v3] = sTeachableMoves[v2 * 8 + v4].moveID;
                        v3++;
                    }
                }
            }
        }
    } else {
        for (v2 = 0; v2 < (NELEMS(sTeachableMoves)); v2++) {
            if (v15 == sTeachableMoves[v2].shardColor) {
                v12[v3] = ov5_021F7A3C(v2);
                v3++;
            }
        }
    }

    for (v2 = 0; v2 < v3; v2++) {
        ov5_021F7F2C(v10, v12[v2], 0xff, v12[v2]);
    }

    v8 = MessageLoader_Init(1, 26, 361, 32);

    ov5_021F7E10(v10, v8);
    ov5_021F7F2C(v10, 5, 0xff, 0xfffe);
    MessageLoader_Free(v8);

    ov5_021F7E10(v10, v7);
    ov5_021F7F34(v10);
    ScriptContext_Pause(param0, ov5_021F7DE8);
    MessageLoader_Free(v7);

    return 1;
}

static BOOL ov5_021F7DE8 (ScriptContext * param0)
{
    FieldSystem * v0 = param0->fieldSys;
    u16 * v1 = sub_0203F118(v0, param0->data[0]);

    if (*v1 == 0xeeee) {
        return 0;
    }

    return 1;
}

static void ov5_021F7E10 (UnkStruct_ov5_021F7ED8 * param0, MessageLoader * param1)
{
    param0->unk_B8 = param1;
    return;
}

static void ov5_021F7E18 (FieldSystem * param0, UnkStruct_ov5_021F7ED8 * param1, u8 param2, u8 param3, u8 param4, u8 param5, u16 * param6, StringTemplate * param7, Window * param8, MessageLoader * param9)
{
    int v0;

    param1->unk_B8 = param9;
    param1->unk_C3_1 = 0;
    param1->unk_BC = param7;
    param1->unk_00 = param0;
    param1->unk_CC = param6;
    param1->unk_C3_0 = param5;
    param1->unk_C2 = param4;
    param1->unk_C4 = param2;
    param1->unk_C5 = param3;
    param1->unk_C7 = 0;
    param1->unk_18 = param8;
    param1->unk_C0 = 3;
    param1->unk_27E = param4;

    for (v0 = 0; v0 < ((NELEMS(sTeachableMoves)) + 1); v0++) {
        param1->unk_F8[v0].unk_00 = NULL;
        param1->unk_F8[v0].unk_04 = 0;
        param1->unk_230[v0] = 0xff;
    }

    for (v0 = 0; v0 < ((NELEMS(sTeachableMoves)) + 1); v0++) {
        param1->unk_1C[v0] = Strbuf_Init((40 * 2), 4);
    }

    *param1->unk_CC = 0xeeee;

    return;
}

UnkStruct_ov5_021F7ED8 * ov5_021F7ED8 (FieldSystem * param0, u8 param1, u8 param2, u8 param3, u8 param4, u16 * param5, StringTemplate * param6, Window * param7, MessageLoader * param8)
{
    UnkStruct_ov5_021F7ED8 * v0;
    int v1;

    v0 = Heap_AllocFromHeap(4, sizeof(UnkStruct_ov5_021F7ED8));

    if (v0 == NULL) {
        return NULL;
    }

    memset(v0, 0, sizeof(UnkStruct_ov5_021F7ED8));
    ov5_021F7E18(param0, v0, param1, param2, param3, param4, param5, param6, param7, param8);

    return v0;
}

void ov5_021F7F2C (UnkStruct_ov5_021F7ED8 * param0, u32 param1, u32 param2, u32 param3)
{
    ov5_021F7FF8(param0, param1, param2, param3);
    return;
}

static void ov5_021F7F34 (UnkStruct_ov5_021F7ED8 * param0)
{
    if (param0->unk_C7 > 8) {
        BGL_AddWindow(param0->unk_00->unk_08, &param0->unk_08, 3, param0->unk_C4, param0->unk_C5, 11, 8 * 2, 13, 1);
    } else {
        BGL_AddWindow(param0->unk_00->unk_08, &param0->unk_08, 3, param0->unk_C4, param0->unk_C5, 11, param0->unk_C7 * 2, 13, 1);
    }

    sub_0200DAA4(param0->unk_00->unk_08, 3, 1024 - (18 + 12) - 9, 11, 0, 4);
    Window_Show(&param0->unk_08, 1, 1024 - (18 + 12) - 9, 11);
    ov5_021F8090(param0);

    param0->unk_F0 = sub_0200112C((const UnkStruct_ov84_02240FA8 *)&param0->unk_D0, 0, param0->unk_C2, 4);
    param0->unk_04 = SysTask_Start(ov5_021F81A8, param0, 0);

    return;
}

static void ov5_021F7FF8 (UnkStruct_ov5_021F7ED8 * param0, u32 param1, u32 param2, u32 param3)
{
    int v0;
    void * v1;

    {
        Strbuf* v2 = Strbuf_Init((40 * 2), 4);

        MessageLoader_GetStrbuf(param0->unk_B8, param1, v2);
        StringTemplate_Format(param0->unk_BC, param0->unk_1C[param0->unk_C7], v2);
        param0->unk_F8[param0->unk_C7].unk_00 = (const void *)param0->unk_1C[param0->unk_C7];
        Strbuf_Free(v2);
    }

    if (param3 == 0xfa) {
        param0->unk_F8[param0->unk_C7].unk_04 = 0xfffffffd;
    } else {
        param0->unk_F8[param0->unk_C7].unk_04 = param3;
    }

    param0->unk_230[param0->unk_C7] = param2;
    param0->unk_C7++;

    return;
}

static void ov5_021F8090 (UnkStruct_ov5_021F7ED8 * param0)
{
    param0->unk_D0.unk_00 = param0->unk_F8;
    param0->unk_D0.unk_04 = ov5_021F819C;
    param0->unk_D0.unk_08 = NULL;
    param0->unk_D0.unk_0C = &param0->unk_08;
    param0->unk_D0.unk_10 = param0->unk_C7;
    param0->unk_D0.unk_12 = 8;
    param0->unk_D0.unk_14 = 1;
    param0->unk_D0.unk_15 = 12;
    param0->unk_D0.unk_16 = 2;
    param0->unk_D0.unk_17_0 = 1;
    param0->unk_D0.unk_17_4 = 1;
    param0->unk_D0.unk_18_0 = 15;
    param0->unk_D0.unk_18_4 = 2;
    param0->unk_D0.unk_1A_0 = 0;
    param0->unk_D0.unk_1A_3 = 16;
    param0->unk_D0.unk_1A_7 = 1;
    param0->unk_D0.unk_1A_9 = 0;
    param0->unk_D0.unk_1A_15 = 0;
    param0->unk_D0.unk_1C = (void *)param0;

    return;
}

static void ov5_021F819C (UnkStruct_0200112C * param0, u32 param1, u8 param2)
{
    u32 v0, v1;
    u16 v2 = 0;
    u16 v3 = 0;
    UnkStruct_ov5_021F7ED8 * v4 = (UnkStruct_ov5_021F7ED8 *)sub_02001504(param0, 19);

    return;
}

static void ov5_021F81A8 (SysTask * param0, void * param1)
{
    u16 v0;
    u32 v1;
    UnkStruct_ov5_021F7ED8 * v2;

    v2 = (UnkStruct_ov5_021F7ED8 *)param1;

    if (v2->unk_C0 != 0) {
        v2->unk_C0--;
        return;
    }

    if (ScreenWipe_Done() == 0) {
        return;
    }

    v1 = sub_02001288(v2->unk_F0);
    v0 = v2->unk_27E;

    sub_020014D0(v2->unk_F0, &v2->unk_27E);

    if (v0 != v2->unk_27E) {
        Sound_PlayEffect(1500);
    }

    switch (v1) {
    case 0xffffffff:
        break;
    case 0xfffffffe:
        if (v2->unk_C3_0 == 1) {
            Sound_PlayEffect(1500);
            *v2->unk_CC = 0xfffe;

            ov5_021F8250(param1);
        }
        break;
    default:
        Sound_PlayEffect(1500);
        *v2->unk_CC = v1;
        ov5_021F8250(param1);
        break;
    }

    return;
}

static void ov5_021F8250 (UnkStruct_ov5_021F7ED8 * param0)
{
    int v0;

    Sound_PlayEffect(1500);
    sub_02001384(param0->unk_F0, NULL, NULL);
    Window_Clear(param0->unk_D0.unk_0C, 0);
    BGL_DeleteWindow(&param0->unk_08);

    for (v0 = 0; v0 < ((NELEMS(sTeachableMoves)) + 1); v0++) {
        Strbuf_Free(param0->unk_1C[v0]);
    }

    if (param0->unk_C3_1 == 1) {
        MessageLoader_Free(param0->unk_B8);
    }

    SysTask_Done(param0->unk_04);
    Heap_FreeToHeap(param0);

    return;
}

BOOL ScrCmd_2EC (ScriptContext * param0)
{
    FieldSystem * v0 = param0->fieldSys;
    StringTemplate ** v1 = sub_0203F098(v0, 15);
    UnkStruct_ov5_021DC1A4 ** v2 = sub_0203F098(v0, 0);
    u8 v3 = ScriptContext_ReadByte(param0);
    u8 v4 = ScriptContext_ReadByte(param0);
    u16 v5 = ScriptContext_GetVar(param0);
    u16 * v6 = ScriptContext_GetVarPointer(param0);

    v5 = ov5_021F7A4C(v5);
    *v2 = ov5_021DD250(v0, v3, v4, v6, *v1, sTeachableMoves[v5].unk_02, sTeachableMoves[v5].unk_03, sTeachableMoves[v5].unk_04, sTeachableMoves[v5].unk_05);

    return 0;
}

BOOL ScrCmd_2ED (ScriptContext * param0)
{
    FieldSystem * v0 = param0->fieldSys;
    UnkStruct_ov5_021DC1A4 ** v1 = sub_0203F098(v0, 0);

    ov5_021DD3A8(*v1);
    return 0;
}
