#pragma once
const int MAX_PRO_POINTS = 7;
const int PRO_POINTS_SCALE = 2;
const int HEIGHT_BETWEEN_PRO_MARKERS = 13;
const int HEIGHT_OFFSET_PRO_MARKERS = 12;

struct proModifier
{
	uint32_t index;
	uint32_t flag;
	bool enabled;
};

enum PRO_MODIFIERS {
	PRO_MOD_KAMIKAZE,					// doesn't shoot much (75% chance to ignore shooting) / nuke on death
	PRO_MOD_DAMAGE,						// 2x damage
	PRO_MOD_DEFENSE,					// 0.5x damage received
	PRO_MOD_MOVE_SPEED,					// 3x move speed
	PRO_MOD_FIRE_SPEED,					// (?) faster firerate
	PRO_MOD_PROJECTILE_SPEED,			// 2x projectile speed
	PRO_MOD_HEALTH,						// 2x-2.5x health
	PRO_MOD_POISON,						// he hits you = you're poisoned
	PRO_MOD_BURNING_TOUCH,				// you touch = you're set on fire (3x damage)
	PRO_MOD_BURNING_DAMAGE,				// he hits you = you're set on fire
	PRO_MOD_WATER_BOLT,					// (?) occasionally spits a WATER BOLT at his target
	PRO_MOD_FIRE_BOLT,					// (?) occasionally spits a FIRE BOLT at his target
	PRO_MOD_NO_SELF_KNOCKBACK,			// RECEIVES 0 knockback
	PRO_MOD_NEGATIVE_SELF_KNOCKBACK,	// RECEIVES negative knockback 4x
	PRO_MOD_KNOCKBACK,					// 4x more knockback
	PRO_MOD_BONUS_LOOT,					// 10x more shards / stimpacks
	PRO_MOD_EXPLOSIVE_DEATH,			// 35 grenades on death TOWARDS his target
	PRO_MOD_DANCE,						// 5s - purple shell / play world.xian1 / frozen
	PRO_MOD_RAIN,						// (?) occasionally spits rain on you (BLUE, GRAVITY blaster bolts)
	PRO_MOD_ANKH,						// revives on death
	PRO_MOD_LUCKER,						// has 25% chance to deal 3x damage
	PRO_MOD_HEALER,						// (?) heals all allies around him 2/0.25s (8/second) + HEALING BUBBLES
};

const proModifier proModifiers[] = {
	{ PRO_MOD_KAMIKAZE,						1 << (PRO_MOD_KAMIKAZE + 1),					true },
	{ PRO_MOD_DAMAGE,						1 << (PRO_MOD_DAMAGE + 1),						true },
	{ PRO_MOD_DEFENSE,						1 << (PRO_MOD_DEFENSE + 1),						true },
	{ PRO_MOD_MOVE_SPEED,					1 << (PRO_MOD_MOVE_SPEED + 1),					true },
	{ PRO_MOD_FIRE_SPEED,					1 << (PRO_MOD_FIRE_SPEED + 1),					true },
	{ PRO_MOD_PROJECTILE_SPEED,				1 << (PRO_MOD_PROJECTILE_SPEED + 1),			true },
	{ PRO_MOD_HEALTH,						1 << (PRO_MOD_HEALTH + 1),						true },
	{ PRO_MOD_POISON,						1 << (PRO_MOD_POISON + 1),						true },
	{ PRO_MOD_BURNING_TOUCH,				1 << (PRO_MOD_BURNING_TOUCH + 1),				true },
	{ PRO_MOD_BURNING_DAMAGE,				1 << (PRO_MOD_BURNING_DAMAGE + 1),				true },
	{ PRO_MOD_WATER_BOLT,					1 << (PRO_MOD_WATER_BOLT + 1),					true },
	{ PRO_MOD_FIRE_BOLT,					1 << (PRO_MOD_FIRE_BOLT + 1),					true },
	{ PRO_MOD_NO_SELF_KNOCKBACK,			1 << (PRO_MOD_NO_SELF_KNOCKBACK + 1),			true },
	{ PRO_MOD_NEGATIVE_SELF_KNOCKBACK,		1 << (PRO_MOD_NEGATIVE_SELF_KNOCKBACK + 1),		true },
	{ PRO_MOD_KNOCKBACK,					1 << (PRO_MOD_KNOCKBACK + 1),					true },
	{ PRO_MOD_BONUS_LOOT,					1 << (PRO_MOD_BONUS_LOOT + 1),					true },
	{ PRO_MOD_EXPLOSIVE_DEATH,				1 << (PRO_MOD_EXPLOSIVE_DEATH + 1),				true },
	{ PRO_MOD_DANCE,						1 << (PRO_MOD_DANCE + 1),						true },
	{ PRO_MOD_RAIN,							1 << (PRO_MOD_RAIN + 1),						true },
	{ PRO_MOD_ANKH,							1 << (PRO_MOD_ANKH + 1),						true },
	{ PRO_MOD_LUCKER,						1 << (PRO_MOD_LUCKER + 1),						true },
	{ PRO_MOD_HEALER,						1 << (PRO_MOD_HEALER + 1),						true },
};
const int NUM_MODIFIERS = sizeof(proModifiers) / sizeof(proModifiers[0]);

void assignMonsterProPoints(edict_t* self);
void spendProPoints(edict_t* self);