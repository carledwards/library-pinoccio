// Class that collects info about connected backpacks
#ifndef LIB_PINOCCIO_BACKPACKS_H
#define LIB_PINOCCIO_BACKPACKS_H

#include "PBBP.h"
#include "Pbbe.h"

/**
 * Structure collecting some info on a backpack. Do not create any of
 * these objects outside of Backpacks::info, since getAddress() only
 * works when this struct lives inside that array.
 */
struct BackpackInfo {
  Pbbe::UniqueId id;

  /**
   * Retrieve the Eeprom a backpack, if not already done so.
   *
   * @returns The value of eeprom_contents if succesful, NULL otherwise.
   */
  uint8_t* getEeprom();

  /**
   * Free the memory used by the eeprom contents.
   */
  void freeEeprom();

  /**
   * Returns the bus address of this backpack.
   */
  uint8_t getAddress();

protected:
  // Declare a private constructor to prevent people from allocating new
  // BackpackInfo objects outside of Backpacks::info (which would break
  // getAddress).
  BackpackInfo() {}

  uint8_t *eeprom_contents;
  uint8_t eeprom_contents_length;

  friend class Backpacks;
};

class Backpacks {
public:
  /**
   * Autodetect connected backpacks.
   */
  static void detect();

  static void setup();
  static void loop() {}

  /**
   * See if a backpack with the given model identifier is present.
   */
  static bool isModelPresent(uint16_t modelid);

  static uint8_t num_backpacks;
  static BackpackInfo *info;
  static PBBP pbbp;

protected:
  /**
   * Add a backpack
   */
  static void addBackpack(uint8_t *unique_id);

  /**
   * Print a Pbbp error. Prints the given prefix, followed by the
   * last pbbp error.
   */
  static void printPbbpError(const char *prefix);

  friend class BackpackInfo;
};

#endif // LIB_PINOCCIO_BACKPACKS_H

/* vim: set filetype=cpp sw=2 sts=2 expandtab: */