#include <stdio.h>

// TODO integrate with Golioth cloud
static uint64_t* get_cards()
{
  // 20121723233 white id
  // 2521244850 blue id

  uint64_t* cards_uids = new uint64_t[MAX_KEYSLOTS_CARDS];

  cards_uids[0] = 20121723233;
  cards_uids[1] = 2521244850;

  return cards_uids;
}

static uint64_t* get_keyslots()
{
  uint64_t* keyslots_ids = new uint64_t[MAX_KEYSLOTS];

  keyslots_ids[0] = 1;

  return keyslots_ids;
}
