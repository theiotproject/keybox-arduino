#include <stdio.h>

// TODO integrate with Golioth cloud
static uint64_t* get_keyslots()
{
  // 20121723233 white
  // 2521244850 blue

  uint64_t* keyslots_ids = new uint64_t[MAX_KEYSLOTS];

  keyslots_ids[0] = 1;

  return keyslots_ids;
}
