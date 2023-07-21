#pragma once

#include <stdio.h>

static uint64_t* get_cards()
{
  // 20121723233 white id
  // 2521244850 blue id

  uint64_t* cards_uids = (uint64_t*) malloc(sizeof(uint64_t) * MAX_CARDS);

  cards_uids[0] = 20121723233;
  cards_uids[1] = 2521244850;

  return cards_uids;
}

static uint8_t* get_slots()
{
  uint8_t* slots = (uint8_t*) malloc(sizeof(uint8_t) * MAX_SLOTS);

  slots[0] = 1;
  slots[1] = 2;
  slots[2] = 3;

  return slots;
}
