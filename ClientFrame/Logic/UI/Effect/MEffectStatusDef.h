//----------------------------------------------------------------------
// MEffectStatusDef.h
//----------------------------------------------------------------------

#ifndef __MEFFECTSTATUSDEF_H__
#define	__MEFFECTSTATUSDEF_H__

enum EFFECTSTATUS {
		
	////////////////////////////////////////////////////////////
	// 새로 추가되는 기술은 제일 밑에 넣어주세요!!!!!!!!!!!
	////////////////////////////////////////////////////////////
	//
	// 성직 관련 이펙트
	EFFECTSTATUS_LIGHT,
	EFFECTSTATUS_DETECT_HIDDEN,
	EFFECTSTATUS_PROTECTION_FROM_POISON,
	EFFECTSTATUS_PROTECTION_FROM_CURSE,
	EFFECTSTATUS_PROTECTION_FROM_ACID,
	EFFECTSTATUS_BLESS,
	EFFECTSTATUS_STRIKING,
	EFFECTSTATUS_CONTINUAL_LIGHT,        // Continual Light를 걸었을때.
	EFFECTSTATUS_DETECT_INVISIBILITY,    // DetectInvisibility 을 걸었을 때.
	EFFECTSTATUS_REGENERATION,
	EFFECTSTATUS_AURA_SHIELD,
	EFFECTSTATUS_SAINT_AURA,
	EFFECTSTATUS_FLARE,

	// 무사 관련 이펙트
	EFFECTSTATUS_CROSS_COUNTER,          // final blow & cross counter
	EFFECTSTATUS_CHARGING_POWER,
	EFFECTSTATUS_LIGHTNING_HAND,
	EFFECTSTATUS_POTENTIAL_EXPLOSION,
	EFFECTSTATUS_DANCING_SWORD,
	EFFECTSTATUS_GHOST_BLADE,

	// 뱀프 관련 이펙트
	EFFECTSTATUS_HIDE ,					// Hide 를 걸었을때.
	EFFECTSTATUS_ACID_TOUCH,			// AcidTouch 를 걸었을때.
	EFFECTSTATUS_POISON ,				// Poisonous Hands의 공격을 당했을때.
	EFFECTSTATUS_POISONOUS_HANDS ,		// Poisonous Hands 를 걸고 있을때.
	EFFECTSTATUS_BLOOD_DRAIN,			// 흡혈 당했을때.
	EFFECTSTATUS_CURSE_PARALYSIS,
	EFFECTSTATUS_CURSE_DOOM,
	EFFECTSTATUS_GREEN_POISON,
	EFFECTSTATUS_YELLOW_POISON,
	EFFECTSTATUS_YELLOW_POISON_TO_CREATURE,	// 캐릭터에 걸려있는 Yellow Poison 효과
	EFFECTSTATUS_DARKNESS,
	EFFECTSTATUS_INVISIBILITY,           // Invisibility 를 걸었을때.
	EFFECTSTATUS_ACID_SWAMP,
	EFFECTSTATUS_ACID_BALL,              // AcidBall이 바닥에 .
	EFFECTSTATUS_GREEN_STALKER,
	EFFECTSTATUS_DARKBLUE_POISON,
	EFFECTSTATUS_DARKBLUE_POISON_TO_CREATURE,
	EFFECTSTATUS_TRANSFORM_TO_WOLF,
	EFFECTSTATUS_TRANSFORM_TO_BAT,

	// 군인 관련 이펙트
	EFFECTSTATUS_RELOAD_TIMER,			// passive skill "FAST RELOAD"를 위해서..
	EFFECTSTATUS_DETECT_MINE,
	EFFECTSTATUS_INSTALL,                // mine install( install되면 안보인다)
	EFFECTSTATUS_FADE_OUT,
	EFFECTSTATUS_SNIPPING_MODE,

	// etc
	EFFECTSTATUS_DECAY_CORPSE,			// 일정 시간이 지나면 시체가 사라짐
	EFFECTSTATUS_DEAD_CREATURE, 		// 일정 시간이 지나면 죽음 처리를 해줌.
	EFFECTSTATUS_SHUT_DOWN, 			// 일정 시간이 지나면 서버를 종료한다.
	EFFECTSTATUS_DECAY_ITEM, 			// 

	////////////////////////////////////////////////////////////
	// 새로 추가되는 기술은 제일 밑에 넣어주세요!!!!!!!!!!!
	////////////////////////////////////////////////////////////

	// Increase HP
	EFFECTSTATUS_HP_RECOVERY,
	EFFECTSTATUS_MP_RECOVERY,

	EFFECTSTATUS_SACRIFICE,

	// 서버 전용
	EFFECTSTATUS_AFTER_MATH,
	EFFECTSTATUS_ALIGNMENT_RECOVERY,
	EFFECTSTATUS_ENEMY_ERASE,

	EFFECTSTATUS_VAMPIRE_PORTAL,
	EFFECTSTATUS_SLAYER_PORTAL,

	EFFECTSTATUS_COMA,

	EFFECTSTATUS_SEDUCTION,							// 56
	EFFECTSTATUS_EXPANSION,							// 57
	EFFECTSTATUS_MIRACLE_SHIELD,					// 58
	EFFECTSTATUS_BERSERKER,							// 59
	EFFECTSTATUS_TYPHOON,							// 60
	EFFECTSTATUS_MIND_CONTROL,						// 61
	EFFECTSTATUS_ACTIVATION,						// 62
	EFFECTSTATUS_PEACE,								// 63
	EFFECTSTATUS_SANCTUARY,							// 64
	EFFECTSTATUS_REFLECTION,						// 65
	EFFECTSTATUS_HALLUCINATION,						// 66
	EFFECTSTATUS_CASKET,							// 67
	EFFECTSTATUS_DEATH,								// 68

	EFFECTSTATUS_PRECEDENCE,						// 69
	EFFECTSTATUS_RESTORE,							// 70

	// 2002.3.23 추가
	EFFECTSTATUS_CURE_CRITICAL_WOUNDS,				// 71
	EFFECTSTATUS_EXTREME,							// 72
	EFFECTSTATUS_HYPNOSIS,							// 73
	EFFECTSTATUS_ARMAGEDDON,						// 74
	EFFECTSTATUS_SUMMON_BAT,						// 75
	EFFECTSTATUS_CHARM,								// 76
	EFFECTSTATUS_MEPHISTO,							// 77

	EFFECTSTATUS_ACID_STORM,						// 78
	EFFECTSTATUS_POISON_STORM,						// 79
	EFFECTSTATUS_BLOODY_STORM,						// 80

	EFFECTSTATUS_ACID_STORM_TO_CREATURE,			// 81
	EFFECTSTATUS_POISON_STORM_TO_CREATURE,			// 82
	EFFECTSTATUS_BLOODY_STORM_TO_CREATURE,			// 83

	EFFECTSTATUS_ENERGY_DROP,						// 84
	EFFECTSTATUS_ENERGY_DROP_TO_CREATURE,			// 85
	EFFECTSTATUS_VIGOR_DROP,						// 86
	EFFECTSTATUS_VIGOR_DROP_TO_CREATURE,			// 87

	// 2002.4.17 추가 by larosel
	EFFECTSTATUS_CAUSE_CRITICAL_WOUNDS,				// 88

	// 2002.6.12 전쟁 관련 이펙트
	EFFECTSTATUS_TRANSPORT_ITEM,					// 89
	EFFECTSTATUS_ADD_ITEM,							// 90

	EFFECTSTATUS_SLAYER_RELIC,						// 91
	EFFECTSTATUS_VAMPIRE_RELIC,						// 92
	EFFECTSTATUS_HAS_SLAYER_RELIC,					// 93
	EFFECTSTATUS_HAS_VAMPIRE_RELIC,					// 94
	EFFECTSTATUS_INCRASE_ATTR,						// 95

	EFFECTSTATUS_HYMN,								// 96
	EFFECTSTATUS_GATEWAY_MONSTER,					// 97
	EFFECTSTATUS_OBSERVING_EYE,						// 98

	// ???
	EFFECTSTATUS_DELETE_ITEM,						// 99
	EFFECTSTATUS_ADD_MONSTER,						// 100

	EFFECTSTATUS_LOGIN_GUILD_MESSAGE,				// 101

	EFFECTSTATUS_SLAYER_RELIC_TABLE,				// 102
	EFFECTSTATUS_VAMPIRE_RELIC_TABLE,				// 103
	EFFECTSTATUS_RELIC_LOCK,   						// 104
	EFFECTSTATUS_RELIC_POSITION,					// 105

	EFFECTSTATUS_GUILD_CHAT,						// 106

	// by sigi. 2002.9.2
	EFFECTSTATUS_MASTER_LAIR_PASS,					// 107
	EFFECTSTATUS_NO_DAMAGE,							// 108
	EFFECTSTATUS_GHOST,								// 109

	// by sigi. 2002.9.10
	EFFECTSTATUS_CONTINUAL_GROUND_ATTACK,			// 110
	EFFECTSTATUS_GROUND_ATTACK,						// 111
	EFFECTSTATUS_METEOR_STRIKE,						// 112

	// by sigi. 2002.9.13
	EFFECTSTATUS_IMMUNE_TO_BLOOD_DRAIN,				// 113
	EFFECTSTATUS_IMMUNE_TO_PARALYZE,				// 114
	EFFECTSTATUS_IMMUNE_TO_POISON,					// 115
	EFFECTSTATUS_IMMUNE_TO_ACID,					// 116
	EFFECTSTATUS_IMMUNE_TO_CURSE,					// 117

	// by sigi. 2002.9.14
	EFFECTSTATUS_DECREASE_HP,						// 118
	EFFECTSTATUS_INCREASE_HP,						// 119

	// by sigi. 2002.9.27
	EFFECTSTATUS_BLOODY_WALL,						// 120
	EFFECTSTATUS_BLOODY_WALL_BLOCKED,				// 121
	EFFECTSTATUS_BLOODY_WALL_SNAKE,					// 122

	// 2002.10.23
	EFFECTSTATUS_SOUL_CHAIN,						// 123
	EFFECTSTATUS_TRANSPORT_CREATURE,				// 124
	EFFECTSTATUS_GRAND_MASTER_SLAYER,				// 125	
	EFFECTSTATUS_GRAND_MASTER_VAMPIRE,				// 126

	EFFECTSTATUS_LEVELUP_SLAYER,					// 127
	EFFECTSTATUS_LEVELUP_VAMPIRE,					// 128

	// 2002.12.29
	EFFECTSTATUS_FIRE_CRACKER_1,					// 129
	EFFECTSTATUS_FIRE_CRACKER_2,					// 130
	EFFECTSTATUS_FIRE_CRACKER_3,					// 131

	EFFECTSTATUS_KILL_AFTERMATH,					// 132

	// 2002.12.12
	EFFECTSTATUS_CLIENTONLY_XMAS_TREE,				// 133

	// 2002.12.26
	EFFECTSTATUS_SHARP_SHIELD_1,					// 134
	EFFECTSTATUS_SHARP_SHIELD_2,					// 135
	EFFECTSTATUS_SHARP_SHIELD_3,					// 136
	EFFECTSTATUS_SHARP_SHIELD_4,					// 137

	EFFECTSTATUS_AIR_SHIELD_1,						// 138
	EFFECTSTATUS_AIR_SHIELD_2,						// 139
	EFFECTSTATUS_AIR_SHIELD_3,						// 140
	EFFECTSTATUS_AIR_SHIELD_4,						// 141

	EFFECTSTATUS_GUN_SHOT_GUIDANCE_AIM,				// 142
	EFFECTSTATUS_GUN_SHOT_GUIDANCE_FIRE,			// 143
	EFFECTSTATUS_GUN_SHOT_GUIDANCE_POINT,			// 144
	EFFECTSTATUS_SLEEP,								// 145

	EFFECTSTATUS_SPIRIT_GUARD_1,					// 146
	EFFECTSTATUS_SPIRIT_GUARD_2,					// 147
	EFFECTSTATUS_SPIRIT_GUARD_3,					// 148
	EFFECTSTATUS_SPIRIT_GUARD_4,					// 149

	EFFECTSTATUS_TILE_STORM,						// 150

	// 2003.1.29			by sonee
	EFFECTSTATUS_HAS_BLOOD_BIBLE_ARMEGA,			// 151
	EFFECTSTATUS_HAS_BLOOD_BIBLE_MIHOLE,			// 152
	EFFECTSTATUS_HAS_BLOOD_BIBLE_KIRO,				// 153
	EFFECTSTATUS_HAS_BLOOD_BIBLE_INI,				// 154
	EFFECTSTATUS_HAS_BLOOD_BIBLE_GREGORI,			// 155
	EFFECTSTATUS_HAS_BLOOD_BIBLE_CONCILIA,			// 156
	EFFECTSTATUS_HAS_BLOOD_BIBLE_LEGIOS,			// 157
	EFFECTSTATUS_HAS_BLOOD_BIBLE_HILLEL,			// 158
	EFFECTSTATUS_HAS_BLOOD_BIBLE_JAVE,				// 159
	EFFECTSTATUS_HAS_BLOOD_BIBLE_NEMA,				// 160
	EFFECTSTATUS_HAS_BLOOD_BIBLE_AROSA,				// 161
	EFFECTSTATUS_HAS_BLOOD_BIBLE_CHASPA,			// 162

	EFFECTSTATUS_SHRINE_GUARD_ARMEGA,				// 163
	EFFECTSTATUS_SHRINE_GUARD_MIHOLE,				// 164
	EFFECTSTATUS_SHRINE_GUARD_KIRO,					// 165
	EFFECTSTATUS_SHRINE_GUARD_INI,					// 166
	EFFECTSTATUS_SHRINE_GUARD_GREGORI,				// 167
	EFFECTSTATUS_SHRINE_GUARD_CONCILIA,				// 168
	EFFECTSTATUS_SHRINE_GUARD_LEGIOS,				// 169
	EFFECTSTATUS_SHRINE_GUARD_HILLEL,				// 170
	EFFECTSTATUS_SHRINE_GUARD_JAVE,					// 171
	EFFECTSTATUS_SHRINE_GUARD_NEMA,					// 172
	EFFECTSTATUS_SHRINE_GUARD_AROSA,				// 173
	EFFECTSTATUS_SHRINE_GUARD_CHASPA,				// 174

	EFFECTSTATUS_SHRINE_HOLY_ARMEGA,				// 175
	EFFECTSTATUS_SHRINE_HOLY_MIHOLE,				// 176
	EFFECTSTATUS_SHRINE_HOLY_KIRO,					// 177
	EFFECTSTATUS_SHRINE_HOLY_INI,					// 178
	EFFECTSTATUS_SHRINE_HOLY_GREGORI,				// 179
	EFFECTSTATUS_SHRINE_HOLY_CONCILIA,				// 180
	EFFECTSTATUS_SHRINE_HOLY_LEGIOS,				// 181
	EFFECTSTATUS_SHRINE_HOLY_HILLEL,				// 182
	EFFECTSTATUS_SHRINE_HOLY_JAVE,					// 183
	EFFECTSTATUS_SHRINE_HOLY_NEMA,					// 184
	EFFECTSTATUS_SHRINE_HOLY_AROSA,					// 185
	EFFECTSTATUS_SHRINE_HOLY_CHASPA,				// 186

	EFFECTSTATUS_SHRINE_GUARD_WARP,					// 187		수호성단에서 워프될때
	EFFECTSTATUS_SHRINE_HOLY_WARP,					// 188		성지성단에서 워프될때
	EFFECTSTATUS_CHANGE_CASTLE_CHANGED,				// 189

	EFFECTSTATUS_SHRINE_SHIELD,						// 190
	EFFECTSTATUS_TOWER_SHIELD,						// 191

	EFFECTSTATUS_TRANSPORT_ITEM_TO_CORPSE,          // 192
	EFFECTSTATUS_ADD_ITEM_TO_CORPSE,                // 193
	EFFECTSTATUS_WARP_BLOOD_BIBLE_FROM_ME,			// 194 내가 가지고있던 피의성서가 워프될때 머리에 찍어주는-_- 이펙트
	EFFECTSTATUS_WARP_BLOOD_BIBLE_FROM_TILE,		// 195 땅에 떨어져있던 피의성서가 워프될때 그 타일에 찍어주는 이펙트

	EFFECTSTATUS_WARP_HOLY_LAND_VAMPIRE,			// 196 뱀파이어가 포탈로 이동할때
	EFFECTSTATUS_WARP_HOLY_LAND_SLAYER,				// 197 슬레이어가 포탈로 이동할때

	EFFECTSTATUS_AMBER_OF_GUARD,					// 198
	EFFECTSTATUS_AMBER_OF_AVENGER,					// 199
	EFFECTSTATUS_AMBER_OF_IMMORTAL,					// 200
	EFFECTSTATUS_AMBER_OF_CURSE,					// 201

	EFFECTSTATUS_INIT_ALL_STATUS,					// 202

	EFFECTSTATUS_CASTLE_SHRINE_GUARD,               // 203
	EFFECTSTATUS_CASTLE_SHRINE_HOLY,                // 204

	EFFECTSTATUS_WARP_BLOOD_BIBLE_SLAYER,			// 205
	EFFECTSTATUS_WARP_BLOOD_BIBLE_VAMPIRE,			// 206
	EFFECTSTATUS_RACE_WAR_JOIN_TICKET,				// 207
	EFFECTSTATUS_LOVE_CHAIN,						// 208
	EFFECTSTATUS_PK_ZONE_REGEN,						// 209
	EFFECTSTATUS_PK_ZONE_RESURRECTION,				// 210

	// 2003.3.31		by sonee
	EFFECTSTATUS_MAGIC_ELUSION,						// 211		Tile		옥타부스		흑표범
	EFFECTSTATUS_POISON_MESH,						// 212		Object		테르티우스		용
	EFFECTSTATUS_ILLUSION_OF_AVENGE,				// 213		Object		셉티무스		소
	EFFECTSTATUS_WILL_OF_LIFE,						// 214		Object		쿠아르투스		불사조

	EFFECTSTATUS_DENIAL_MAGIC,                      // 215
	EFFECTSTATUS_DENIAL_MAGIC_DAMAGED,              // 216
	EFFECTSTATUS_REQUITAL,                          // 217
	EFFECTSTATUS_CONCEALMENT,                       // 218
	EFFECTSTATUS_DRAGON_FIRE_CRACKER,               // 219
	EFFECTSTATUS_GRAND_MASTER_OUSTERS,              // 220

	EFFECTSTATUS_FIRE_CRACKER_4,					// 221
	EFFECTSTATUS_FIRE_CRACKER_VOLLEY_1,				// 222
	EFFECTSTATUS_FIRE_CRACKER_VOLLEY_2,				// 223
	EFFECTSTATUS_FIRE_CRACKER_VOLLEY_3,				// 224
	EFFECTSTATUS_FIRE_CRACKER_VOLLEY_4,				// 225

	EFFECTSTATUS_FIRE_CRACKER_WIDE_VOLLEY_1,		// 226
	EFFECTSTATUS_FIRE_CRACKER_WIDE_VOLLEY_2,		// 227
	EFFECTSTATUS_FIRE_CRACKER_WIDE_VOLLEY_3,		// 228
	EFFECTSTATUS_FIRE_CRACKER_WIDE_VOLLEY_4,		// 229	

	EFFECTSTATUS_FIRE_CRACKER_STORM,				// 230
	EFFECTSTATUS_TRANSLATION,						// 231
	EFFECTSTATUS_LIGHTNESS,							// 232

	EFFECTSTATUS_EVADE,								// 233
	EFFECTSTATUS_BLUNTING,							// 234
	EFFECTSTATUS_CROSS_GUARD,						// 235
	EFFECTSTATUS_HANDS_OF_FIRE,						// 236
	EFFECTSTATUS_PROMINENCE,						// 237
	EFFECTSTATUS_RING_OF_FLARE,						// 238
	EFFECTSTATUS_WATER_BARRIER,						// 239
	EFFECTSTATUS_TENDRIL,							// 240
	EFFECTSTATUS_GNOME_WHISPER,						// 241
	EFFECTSTATUS_ICE_FIELD,                         // 242
	EFFECTSTATUS_ICE_FIELD_TO_CREATURE,             // 243
	EFFECTSTATUS_CANNOT_ABSORB_SOUL,                // 244
	EFFECTSTATUS_SUMMON_SYLPH,                      // 245
	EFFECTSTATUS_LEVELUP_OUSTERS,					// 246
	EFFECTSTATUS_BACK_STAB,                         // 247

	EFFECTSTATUS_PROMINENCE_2,                      // 248
	EFFECTSTATUS_PROMINENCE_3,                      // 249	
	EFFECTSTATUS_RING_OF_FLARE_2,                   // 250
	EFFECTSTATUS_RING_OF_FLARE_3,                   // 251

	EFFECTSTATUS_BACK_STAB_2,						// 252
	EFFECTSTATUS_BACK_STAB_3,						// 253

	EFFECTSTATUS_FIRE_OF_SOUL_STONE,				// 254
	EFFECTSTATUS_ICE_OF_SOUL_STONE,					// 255
	EFFECTSTATUS_SAND_OF_SOUL_STONE,				// 256
	EFFECTSTATUS_BLOCK_HEAD,						// 257

	EFFECTSTATUS_LOUD,								// 258
	EFFECTSTATUS_DIVINE_SPIRITS,					// 259

	EFFECTSTATUS_REFINIUM_TICKET,                   // 260

	EFFECTSTATUS_CONTINUAL_BLOODY_WALL,             // 261
	EFFECTSTATUS_DIVINE_GUIDANCE,                   // 262	
	EFFECTSTATUS_JABBING_VEIN,                      // 263
	EFFECTSTATUS_BLAZE_BOLT,                        // 264

	EFFECTSTATUS_HAS_FLAG,                          // 265
	EFFECTSTATUS_FLAG_INSERT,                       // 266
	EFFECTSTATUS_MUTE,                              // 267

	EFFECTSTATUS_DROP_FORCE,						// 268
	EFFECTSTATUS_SLAYER_ONLY,                       // 269
	EFFECTSTATUS_VAMPIRE_ONLY,                      // 270
	EFFECTSTATUS_OUSTERS_ONLY,                      // 271

	EFFECTSTATUS_REDIANCE,							// 272
	EFFECTSTATUS_HEART_CATALYST,					// 273

	EFFECTSTATUS_WARP_HOLY_LAND_OUSTERS,			// 274
	EFFECTSTATUS_FAMILY_BONUS,						// 275

	EFFECTSTATUS_PROTECTION_FROM_BLOOD,				// 276
	EFFECTSTATUS_ETERNITY,							// 277
	EFFECTSTATUS_HAS_PET,                           // 278

	EFFECTSTATUS_ETERNITY_PAUSE,                    // 279

	EFFECTSTATUS_TRAP_INSTALLED,                    // 280
	EFFECTSTATUS_TRAP_TRIGGERED,                    // 281

	EFFECTSTATUS_TRAPPED,                           // 282
	EFFECTSTATUS_MERCY_GROUND,                      // 283
	EFFECTSTATUS_HOLY_ARMOR,                        // 284

	EFFECTSTATUS_TRANSFORM_TO_WERWOLF,              // 285
	EFFECTSTATUS_HOWL,                              // 286
	EFFECTSTATUS_STONE_SKIN,                        // 287
	EFFECTSTATUS_GRAY_DARKNESS,						// 288
	EFFECTSTATUS_STONE_SKIN_DAMAGED,				// 289

	EFFECTSTATUS_ACID_ERUPTION,                     // 290

	EFFECTSTATUS_JUST_LOGIN,                        // 291			클라이언트 사용 안함.

	EFFECTSTATUS_HAS_SWEEPER,                       // 292
	EFFECTSTATUS_HAS_SWEEPER_2,                     // 293
	EFFECTSTATUS_HAS_SWEEPER_3,                     // 294
	EFFECTSTATUS_HAS_SWEEPER_4,                     // 295
	EFFECTSTATUS_HAS_SWEEPER_5,                     // 296
	EFFECTSTATUS_HAS_SWEEPER_6,                     // 297
	EFFECTSTATUS_HAS_SWEEPER_7,                     // 298
	EFFECTSTATUS_HAS_SWEEPER_8,                     // 299
	EFFECTSTATUS_HAS_SWEEPER_9,                     // 300
	EFFECTSTATUS_HAS_SWEEPER_10,                    // 301
	EFFECTSTATUS_HAS_SWEEPER_11,                    // 302
	EFFECTSTATUS_HAS_SWEEPER_12,                    // 303

	EFFECTSTATUS_KEEP_SWEEPER,                      // 304
	EFFECTSTATUS_KEEP_SWEEPER_2,                    // 305
	EFFECTSTATUS_KEEP_SWEEPER_3,                    // 306
	EFFECTSTATUS_KEEP_SWEEPER_4,                    // 307
	EFFECTSTATUS_KEEP_SWEEPER_5,                    // 308
	EFFECTSTATUS_KEEP_SWEEPER_6,                    // 309
	EFFECTSTATUS_KEEP_SWEEPER_7,                    // 310
	EFFECTSTATUS_KEEP_SWEEPER_8,                    // 311
	EFFECTSTATUS_KEEP_SWEEPER_9,                    // 312
	EFFECTSTATUS_KEEP_SWEEPER_10,                   // 313
	EFFECTSTATUS_KEEP_SWEEPER_11,                   // 314
	EFFECTSTATUS_KEEP_SWEEPER_12,                   // 315

	EFFECTSTATUS_SLAYER_REGEN_ZONE,                 // 316
	EFFECTSTATUS_VAMPIRE_REGEN_ZONE,                // 317
	EFFECTSTATUS_OUSTERS_REGEN_ZONE,                // 318
	EFFECTSTATUS_DEFAULT_REGEN_ZONE,                // 319
	EFFECTSTATUS_SLAYER_TRYING_1,                   // 320
	EFFECTSTATUS_SLAYER_TRYING_2,                   // 321
	EFFECTSTATUS_SLAYER_TRYING_3,                   // 322
	EFFECTSTATUS_VAMPIRE_TRYING_1,                  // 323
	EFFECTSTATUS_VAMPIRE_TRYING_2,                  // 324
	EFFECTSTATUS_VAMPIRE_TRYING_3,                  // 325
	EFFECTSTATUS_OUSTERS_TRYING_1,                  // 326
	EFFECTSTATUS_OUSTERS_TRYING_2,                  // 327
	EFFECTSTATUS_OUSTERS_TRYING_3,                  // 328

	EFFECTSTATUS_TRYING_POSITION,                   // 329
	EFFECTSTATUS_TRYING,                            // 330

	EFFECTSTATUS_CAPTURE_REGEN_ZONE,                // 331
	EFFECTSTATUS_ON_BRIDGE,                         // 332

	EFFECTSTATUS_SUMMON_SYLPH_GREEN,                // 333
	EFFECTSTATUS_SUMMON_SYLPH_ORANGE,               // 334
	EFFECTSTATUS_SUMMON_SYLPH_RED,                  // 335
	EFFECTSTATUS_SUMMON_SYLPH_YELLOW,               // 336

	EFFECTSTATUS_SUMMON_SYLPH_WHITE,                // 337
	EFFECTSTATUS_SUMMON_SYLPH_BROWN,                // 338
	EFFECTSTATUS_SUMMON_SYLPH_LILAC,                // 339
	EFFECTSTATUS_SUMMON_SYLPH_BLACK,                // 340

	EFFECTSTATUS_IMMUNE_TO_HALLUCINATION,           // 341
	EFFECTSTATUS_PET_DISSECT,                       // 342
	EFFECTSTATUS_EXPLOSION_WATER,					// 343
	EFFECTSTATUS_FROZEN_ARMOR,						// 344
	EFFECTSTATUS_FROZEN_ARMOR_TO_ENEMY,             // 345
	EFFECTSTATUS_REACTIVE_ARMOR,                    // 346
	EFFECTSTATUS_MAGNUM_SPEAR,                      // 347
	EFFECTSTATUS_HELLFIRE,                          // 348
	EFFECTSTATUS_HELLFIRE_TO_ENEMY,					// 349
	EFFECTSTATUS_GROUND_BLESS,                      // 350
	EFFECTSTATUS_SHARP_CHAKRAM,                     // 351
	EFFECTSTATUS_DESTRUCTION_SPEAR,                 // 352
	EFFECTSTATUS_BLESS_FIRE,                        // 353
	EFFECTSTATUS_WATER_SHIELD,                      // 354
	EFFECTSTATUS_SAND_CROSS,                        // 355
	EFFECTSTATUS_GROUND_ELEMENTAL_AURA,             // 356
	EFFECTSTATUS_FIRE_ELEMENTAL,                    // 357
	EFFECTSTATUS_WATER_ELEMENTAL,                   // 358
	EFFECTSTATUS_DISTANCE_BLITZ,                    // 359
	EFFECTSTATUS_GROUND_ELEMENTAL_CENTER,           // 360
	EFFECTSTATUS_FIRE_ELEMENTAL_ATTACK,             // 361
	EFFECTSTATUS_FIRE_ELEMENTAL_DAMAGED,            // 362
	EFFECTSTATUS_WATER_ELEMENTAL_HEAL,              // 363
	EFFECTSTATUS_WATER_ELEMENTAL_HEALED,            // 364
	EFFECTSTATUS_DARKNESS_FORBIDDEN,                // 365
	EFFECTSTATUS_VIEW_HP,                           // 366
	
	// 2004, 03, 25 sobeit add start
	EFFECTSTATUS_BLACK_LARGE_SMOKE,                 // 367
	EFFECTSTATUS_BLACK_HALL,                        // 368
	EFFECTSTATUS_BLACK_SMALL_SMOKE_1,               // 369
	EFFECTSTATUS_BLACK_SMALL_SMOKE_2,               // 370
	EFFECTSTATUS_BLACK_SMALL_SMOKE_3,               // 371
	EFFECTSTATUS_ELECTRIC_POST,				        // 372

	EFFECTSTATUS_GHOST_1,                           // 373
	EFFECTSTATUS_GHOST_2,                           // 374
	// 2004, 03, 25 sobeit add end

	// 2004, 4, 2, sobeit add start
	EFFECTSTATUS_LUCKY,                             // 375
    EFFECTSTATUS_MISFORTUNE,                        // 376
	// 2004, 4, 2, sobeit add end

	// 2004, 5, 6 sobeit add start
	EFFECTSTATUS_HAS_CASTLE_SYMBOL_5,               // 377 - amber of life
    EFFECTSTATUS_HAS_CASTLE_SYMBOL_6,               // 378 - amber of light
	// 2004, 5, 6 sobeit add end

	// 2004, 5, 19 sobeit add start
    EFFECTSTATUS_ICICLE_DROP,                       // 379
    EFFECTSTATUS_ICICLE_DROP_SIGN,                  // 380

    EFFECTSTATUS_ICICLE_AUGER,                      // 381
	EFFECTSTATUS_ICICLE_AUGER_SIGN,                 // 382

    EFFECTSTATUS_ICE_STICK_SW,                      // 383
    EFFECTSTATUS_ICE_STICK_SW_SIGN,                 // 384

    EFFECTSTATUS_ICE_STICK_SE,                      // 385
    EFFECTSTATUS_ICE_STICK_SE_SIGN,                 // 386

    EFFECTSTATUS_ICE_STICK_NE,                      // 387
    EFFECTSTATUS_ICE_STICK_NE_SIGN,                 // 388

    EFFECTSTATUS_ICE_STICK_NW,                      // 389
    EFFECTSTATUS_ICE_STICK_NW_SIGN,                 // 390

	EFFECTSTATUS_ICICLE_LARGE_AUGER,                // 391
	EFFECTSTATUS_ICICLE_LARGE_AUGER_SIGN,           // 392

	EFFECTSTATUS_WHITE_BLESS,						// 393
	// 2004, 5, 19 sobeit add end

	// 2004, 6, 5 sobeit add start
	EFFECTSTATUS_BLINDNESS,							// 394
	EFFECTSTATUS_CAN_ENTER_GDR_LAIR,				// 395
	// 2004, 6, 5 sobeit add end

//	// 2004, 6, 11 sobeit add start
    EFFECTSTATUS_SUMMON_GDR,                    // 396
    EFFECTSTATUS_GDR_SATELLITE,                 // 397
    EFFECTSTATUS_GDR_FLOATING,                  // 398

    EFFECTSTATUS_GRAND_MASTER_SLAYER_130,       // 399
    EFFECTSTATUS_GRAND_MASTER_SLAYER_150,       // 400
    EFFECTSTATUS_GRAND_MASTER_VAMPIRE_130,      // 401
    EFFECTSTATUS_GRAND_MASTER_VAMPIRE_150,      // 402
    EFFECTSTATUS_GRAND_MASTER_OUSTERS_130,      // 403
    EFFECTSTATUS_GRAND_MASTER_OUSTERS_150,      // 404
//	// 2004, 6, 11 sobeit add end

// 2004, 6, 15 sobeit add Start - gdr skill - glacier
//	EFFECTSTATUS_GDR_GLACIER_SLAYER,
//	EFFECTSTATUS_GDR_GLACIER_VAMPIRE,
//	EFFECTSTATUS_GDR_GLACIER_OUSTERS,
// 2004, 6, 15 sobeit add end - gdr skill - glacier
// 2004, 6, 21 sobeit add start
    EFFECTSTATUS_CAN_MODIFY_NICKNAME_0,         // 405
    EFFECTSTATUS_CAN_MODIFY_PET_NICKNAME,       // 406

    EFFECTSTATUS_GLACIER,                       // 407
    EFFECTSTATUS_ICE_HAIL,                      // 408
// 2004, 6, 21 sobeit add end
// 2004, 7, 21 sobeit add start
	EFFECTSTATUS_GOLD_MEDAL,					// 409
// 2004, 7, 21 sobeit add end

	EFFECTSTATUS_PK_COUNTED,					// 410
	EFFECTSTATUS_PUNISH_COUNTED,					// 411
	EFFECTSTATUS_SIEGE_DEFENDERL,					// 412
	EFFECTSTATUS_SIEGE_REINFORCE,					// 413
	EFFECTSTATUS_SIEGE_ATTACKER_1,					// 414
	EFFECTSTATUS_SIEGE_ATTACKER_2,					// 415
	EFFECTSTATUS_SIEGE_ATTACKER_3,					// 416
	EFFECTSTATUS_SIEGE_ATTACKER_4,					// 417
	EFFECTSTATUS_SIEGE_ATTACKER_5,					// 418
	
	EFFECTSTATUS_SHARE_HP,                      // 419  // HP 공유하기~
	EFFECTSTATUS_LAND_MINE_EXPLOSION,           // 420  // 랜드마인 터지는 이펙트
    EFFECTSTATUS_CLAYMORE_EXPLOTION,            // 421  // 크레모어 터지는 이펙트
    EFFECTSTATUS_PLEASURE_EXPLOSION,            // 422  // 플레져 스테이션 터지는 이펙트
    EFFECTSTATUS_TURRET_LASER,                  // 423  // 터렛 레이저 1타일
    EFFECTSTATUS_TURRET_LASER_ATTACK,           // 424  // 터렛 레이저 공격 1타일 (공격측에도 보임)
	EFFECTSTATUS_AUTO_TURRET,                   // 425  // 오토 터렛 서있는거
	EFFECTSTATUS_HIDE_TO_ATTACKER,              // 426  // 공성 공격측에는 안 보인다.

	EFFECTSTATUS_REPUTO_FACTUM,                 // 427  // 맞았을때 이펙트
	EFFECTSTATUS_REPUTO_FACTUM_LAST,            // 428  // 지속이펙트

	EFFECTSTATUS_SWORD_OF_THOR,                 // 429  // 타일에 붙어서 터지는 칼

    EFFECTSTATUS_BURNING_SOL_CHARGE_1,          // 430
    EFFECTSTATUS_BURNING_SOL_CHARGE_2,          // 431
    EFFECTSTATUS_BURNING_SOL_CHARGE_3,          // 432
    EFFECTSTATUS_BURNING_SOL_CHARGE_4,          // 433

    EFFECTSTATUS_INSTALL_TURRET,                // 434

	EFFECTSTATUS_WHITSUNTIDE,                   // 435
	
	EFFECTSTATUS_DRAGON_EYES,                   // 436

	EFFECTSTATUS_ROCKET_LUNCHER,                // 437

	EFFECTSTATUS_PLASMA_ROCKET_LAUNCHER,        // 438 - 흠..내 화면에 어떤 넘이 들어왔는데..그넘한테 미사일이 붙었다네..
    EFFECTSTATUS_INTIMATE_GRAIL,                // 439

	EFFECTSTATUS_ICE_HORIZON,					// 440
	EFFECTSTATUS_SET_AFIRE_ATTACK,				// 441
	
	EFFECTSTATUS_FURY_OF_GNOME,                 // 442 // 단지 타일 상태
	EFFECTSTATUS_FURY_OF_GNOME_MARK,            // 443 // 이펙트..

	EFFECTSTATUS_SUMMON_MIGA_FIRE,				// 444

	EFFECTSTATUS_DRAGON_TORNADO,                // 445
    EFFECTSTATUS_DRAGON_TORNADO_CHILD,          // 446
    EFFECTSTATUS_HARPOON_BOMB,                  // 447
    EFFECTSTATUS_PASSING_HEAL,                  // 448
    EFFECTSTATUS_ABERRATION,                    // 449
    EFFECTSTATUS_HALO,                          // 450
    EFFECTSTATUS_FIERCE_FLAME,            
 
	EFFECTSTATUS_SHADOW,                        // 452
    EFFECTSTATUS_SHADOW_OF_STORM,               // 453

	EFFECTSTATUS_BIKE_CRASH,					// 454

	EFFECTSTATUS_DONATION_200501,               // 455
    EFFECTSTATUS_BONUS_EXP,                     // 456

	EFFECTSTATUS_ADVANCEMENT_MASTSER_EFFECT_SLAYER,	// 457
	EFFECTSTATUS_ADVANCEMENT_MASTSER_EFFECT_VAMPIRE,// 458
	EFFECTSTATUS_ADVANCEMENT_MASTSER_EFFECT_OUSTERS,// 459

	EFFECTSTATUS_DELETE_TILE,                   // 460

	EFFECTSTATUS_CAN_ENTER_SLAYER_PORTAL,       // 461
    EFFECTSTATUS_CAN_ENTER_VAMPIRE_PORTAL,      // 462
    EFFECTSTATUS_CAN_ENTER_OUSTERS_PORTAL,      // 463

	EFFECTSTATUS_TILE_PORTAL,                   // 464
	// add by Coffee 2007-5-20
	EFFECTSTATUS_BLOOD_BLLODY_SCARIFY,			// 沂裂임丹(俱沂뱁)
	EFFECTSTATUS_BLOOD_CURSE,					// 沂裂�{麓(俱沂뱁)
	// add by Coffee 2007-3-6 앵텔뷰珞  훙膠�襁┪㏏� // 465
	EFFECTSTATUS_BOMB_CRASH_WALK_TO_ENEMY,
	EFFECTSTATUS_SATELLITE_BOMB_AIM,		//括槿뷰샌 槻벎땍屢 (훙잚)
	EFFECTSTATUS_SATELLITE_BOMB_POINT,		//括槿뷰샌 槻벎땍屢 (훙잚)
	EFFECTSTATUS_SATELLITE_BOMB_FIRE,
	EFFECTSTATUS_HEAVEN_GROUND,				//랬可莖�洲돝�
	// add by Coffee 2007-5-2
	EFFECTSTATUS_DUMMY_DRAKE,				//돠잉옹웨잔(침쥣삽랬)
	EFFECTSTATUS_HYDRO_CONVERGENCE,			//릿북彊좟(침쥣彊랬)
	EFFECTSTATUS_SUMMON_CLAY,				//  Summon Clay  瀾皐梁뻥    (침쥣劤세콘 皐랬)
	EFFECTSTATUS_HETER_CHAKRAM,	//475			//  Heter Chakram 謳꼈적샘凜  (침쥣劤세콘  濫却)

	//add by viva
	EFFECTSTATUS_SLAYER_GUN_BOMB_XRL_MISSILE,	//XRL 珞죙돔뎐
	EFFECTSTATUS_UNKOWN_VIVA2,
	EFFECTSTATUS_UNKOWN_VIVA3,
	EFFECTSTATUS_UNKOWN_VIVA4,

	EFFECTSTATUS_SLAYER_ENCHANT_BRAMBLE_HALO,//Original Action:390 //쐽섕밟뻔 //龍르
	EFFECTSTATUS_UNKOWN_VIVA5, //EffectSpriteType:1134
	EFFECTSTATUS_OUSTERS_WATER_RAPID_FREEZE,	//Original Action:396
	EFFECTSTATUS_OUSTERS_COMBAT_PENETRATE_WHEEL,	//Orginal Action : 393
	EFFECTSTATUS_UNKOWN_VIVA6,
	EFFECTSTATUS_VAMPIRE_TRANSFORM_TO_D_BAT,//Original Action : 409
	EFFECTSTATUS_VAMPIRE_TRANSFORM_TO_D_ANGEL,//Original Action : 410
	EFFECTSTATUS_SUMMON_SYLPH1,//梁뻥쑹쥣//ousters//Original Action : 247
	EFFECTSTATUS_SUMMON_SYLPH2,
	EFFECTSTATUS_UNKOWN_VIVA7,
	
	//end
	EFFECTSTATUS_MAX,
	EFFECTSTATUS_NULL
};

#endif

