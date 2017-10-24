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
  // TODO: styczyn
  // FIX: Transh value
  return 0;
}

// Remove entire dict
void dict_delete(unsigned long id) {
  // TODO: wikzan
  // TODO: Implement
}

// Count records in dict
std::size_t dict_size(unsigned long id) {
  // TODO: wikzan
  // FIX: Transh value
  return 0;
}

// Create new record in dict
void dict_insert(unsigned long id, const char* key, const char* value) {
  // TODO: styczyn
  // TODO: Implement
}

// Remove record from dict
void dict_remove(unsigned long id, const char* key) {
  // TODO: wikzan
  // TODO: Implement
}

// Get value from dict
const char* dict_find(unsigned long id, const char* key) {
  // TODO: styczyn
  // FIX: Transh value
  return nullptr;
}

// Erase all records in dict
void dict_clear(unsigned long id) {
  // TODO: wikzan
  // TODO: Implement
}

// Copy dicts src -> dst
void dict_copy(unsigned long src_id, unsigned long dst_id) {
  // TODO: styczyn
  // TODO: Implement
}

