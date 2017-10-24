/*
 * JNP-ZAD-2
 *
 *  University of Warsaw 2017
 *
 * Contributors:
 *   @wikzan
 *   @styczynski
 */
#include "dict.h"
 
typedef std::unordered_map<std::string, std::string> dict;
 
// Create new dict and return its id
unsigned long dict_new() {
  // FIX: Transh value
  return 0;
}

// Remove entire dict
void dict_delete(unsigned long id) {
  // TODO: Implement
}

// Count records in dict
std::size_t dict_size(unsigned long id) {
  // FIX: Transh value
  return 0;
}

// Create new record in dict
void dict_insert(unsigned long id, const char* key, const char* value) {
  // TODO: Implement
}

// Remove record from dict
void dict_remove(unsigned long id, const char* key) {
  // TODO: Implement
}

// Get value from dict
const char* dict_find(unsigned long id, const char* key) {
  // FIX: Transh value
  return nullptr;
}

// Erase all records in dict
void dict_clear(unsigned long id) {
  // TODO: Implement
}

// Copy dicts src -> dst
void dict_copy(unsigned long src_id, unsigned long dst_id) {
  // TODO: Implement
}

