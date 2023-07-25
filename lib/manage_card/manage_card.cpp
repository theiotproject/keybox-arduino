#include <cstdint>
#include <cstdlib>

#include "../../include/config.h"
#include "manage_card.h"

uint64_t* get_cards()
{
  // 20121723233 white id
  // 2521244850 blue id

  uint64_t* cards_uids = (uint64_t*) malloc(sizeof(uint64_t) * MAX_CARDS);

  // add access to cards
  cards_uids[0] = 2521244850;

  return cards_uids;
}

uint8_t* get_slots()
{
  uint8_t* slots = (uint8_t*) malloc(sizeof(uint8_t) * MAX_SLOTS);

  // add access to slots
  slots[0] = 1;
  slots[1] = 2;
  slots[2] = 3;

  return slots;
}
