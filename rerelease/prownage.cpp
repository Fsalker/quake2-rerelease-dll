#include "./g_local.h"

void proMarkerFly(edict_t* self)
{
	vec3_t dest;
	dest = self->owner->s.origin;
	dest[2] = self->owner->absmax[2] + self->proMarkerIndex * HEIGHT_BETWEEN_PRO_MARKERS + HEIGHT_OFFSET_PRO_MARKERS;
	self->s.origin = dest;
	gi.linkentity(self);
}

THINK(proMarkerThink) (edict_t* self) -> void
{
	if (self->owner) {
		self->ideal_yaw = self->owner->s.angles[YAW];
		self->nextthink = level.time + 60_hz;
	}
	M_ChangeYaw(self);
	proMarkerFly(self);

	if (self->owner->health < 0) {
		float minAlpha = 0.3f;
		float decreaseDuration = 3; // seconds
		float decreaseSpeed = (1.0f - minAlpha) / (decreaseDuration * 60);
		//gi.Com_PrintFmt_("Owner is dead... decreaseSpeed={}, alpha={}\n", decreaseSpeed, self->s.alpha);

		if (self->s.alpha > minAlpha) {
			self->s.alpha -= decreaseSpeed;
		}
	}
}

edict_t* proMarkerSpawn(edict_t* owner, proModifier mod, int index = 0)
{
	gi.Com_Print("Spawning Marker...\n");
	edict_t* proMarker;

	proMarker = G_Spawn();
	proMarker->proMarkerIndex = index;
	proMarker->s.origin = owner->s.origin;
	proMarker->s.origin[2] = owner->absmax[2] + proMarker->proMarkerIndex * HEIGHT_BETWEEN_PRO_MARKERS + HEIGHT_OFFSET_PRO_MARKERS;
	proMarker->s.angles[YAW] = owner->s.angles[YAW];
	proMarker->solid = SOLID_NOT;
	proMarker->clipmask = MASK_PROJECTILE;
	proMarker->s.renderfx = RF_FULLBRIGHT | RF_IR_VISIBLE;
	proMarker->movetype = MOVETYPE_FLYMISSILE;
	proMarker->s.alpha = 1.0;

	proMarker->owner = owner;
	proMarker->classname = "proMarker";
	proMarker->yaw_speed = 40;
	proMarker->monsterinfo.attack_finished = 0_ms;
	proMarker->spawnflags = SPAWNFLAG_NONE;

	proMarker->s.modelindex = gi.modelindex("models/items/hunter/tris.md2");
	proMarker->s.sound = gi.soundindex("world/xian1.wav");

	proMarker->think = proMarkerThink;
	proMarker->nextthink = level.time + 60_hz;

	gi.linkentity(proMarker);

	return proMarker;
}

auto andyPow(float base, int exp) {
    auto result = base;
    for(int index=2; index<=exp; ++index) {
        result *= base;
    }
	return result;
}

void assignMonsterProPoints(edict_t* self)
{
    float rand = frandom(MAX_PRO_POINTS);
    int proPoints = rand * andyPow(rand / MAX_PRO_POINTS, PRO_POINTS_SCALE);
    self->proPoints = proPoints;
    //gi.Com_PrintFmt("This monster's proPoints = {}\n", proPoints);

	if (self->proPoints) {
		spendProPoints(self);
	}
}

void spendProPoints(edict_t* self)
{
	int availableModifiers[NUM_MODIFIERS];
	int selectedModifiers[NUM_MODIFIERS];

	for (int index = 0; index < NUM_MODIFIERS; ++index) {
		availableModifiers[index] = index;
	}

	//gi.Com_PrintFmt("Available modifiers = ");for (unsigned int index = 0; index < self->proPoints; ++index) gi.Com_PrintFmt("{} ", availableModifiers[index]); gi.Com_PrintFmt("\n");
	for (int index = 0; index < self->proPoints; ++index) {
		int randomIndex = irandom(index, NUM_MODIFIERS);

		selectedModifiers[index] = availableModifiers[randomIndex];
		std::swap(availableModifiers[index], availableModifiers[randomIndex]);
		//gi.Com_PrintFmt_("randomIndex = {}, selectedModifiers[{}]={}\n", randomIndex, index, selectedModifiers[index]);
	}
	gi.Com_PrintFmt("Selected modifiers = "); for (int index = 0; index < self->proPoints; ++index) gi.Com_PrintFmt_("{} ", selectedModifiers[index]); gi.Com_PrintFmt("\n");

	for (int index = 0; index < self->proPoints; ++index) {
		int modifierIndex = selectedModifiers[index];
		proModifier mod = proModifiers[modifierIndex];

		self->proFlags |= mod.flag;
		proMarkerSpawn(self, mod, index);
	}
}
