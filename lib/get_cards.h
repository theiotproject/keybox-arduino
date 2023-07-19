#include <stdio.h>

// TODO integrate with Golioth cloud
static uint64_t* get_cards()
{
  // 20121723233 white
  // 2521244850 blue

  uint64_t* cards_uids = new uint64_t[MAX_KEYSLOTS_CARDS];

  cards_uids[0] = 20121723233;
  cards_uids[1] = 2521244850;

  return cards_uids;
}
