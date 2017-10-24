/*
 * JNP-ZAD-2
 *
 *  University of Warsaw 2017
 *
 * Contributors:
 *   @wikzan
 *   @styczynski
 */
#include <cstddef>
 
 
/*
 * Creates new empty dictionary and returns its id.
 *
 * @returns id of newly created dictionary
 */
unsigned long dict_new();

/*
 * Removes dictionary with given id.
 * If no dictionary with such id exists then
 * the function call has no effects.
 *
 * You cannot remove the global dictonary.
 * This function called on its id has no effects.
 *
 * @param[in] id: id of dictionary
 */
void dict_delete(unsigned long id);

/*
 * Returns count of elements contained in
 * the dictionary with specified id.
 * If no dictionary with such id exists then
 * the function returns zero.
 *
 * @param[in] id  : id of dictionary
 * @returns size_t size of dictionary
 */
std::size_t dict_size(unsigned long id);

/*
 * Puts a new record in the dictionary
 * with a given id.
 *
 * If the given key or value is NULL then
 * the function call has no effects.
 *
 * If no dictionary with such id exists then
 * the function call has no effects.
 *
 * @param[in] id    : id of dictionary
 * @param[in] key   : key of new entry
 * @param[in] value : value of new entry
 */
void dict_insert(unsigned long id, const char* key, const char* value);

/*
 * Removes record from the dictionary
 * specified by id.
 *
 * If the given key does not exist in the dictionary
 * the function call has no effects.
 *
 * If no dictionary with such id exists then
 * the function call has no effects.
 *
 * @param[in] id    : id of dictionary
 * @param[in] key   : key of entry that will be removed
 */
void dict_remove(unsigned long id, const char* key);

/*
 * Returns the value saved under the specified key
 * in the dictionary specified by id.
 *
 * If the given key does not exist in the dictionary
 * the function searches the global dictionary.
 *
 * If no dictionary with such id exists then
 * the function searches the global dictionary.
 *
 * If there's no such key in global dictionary
 * then NULL is returned.
 *
 * @param[in] id    : id of dictionary
 * @param[in] key   : key of entry that will be removed
 * @returns pointer to the value saved under the given key
 */
const char* dict_find(unsigned long id, const char* key);

/*
 * Clears the dictionary
 * with a given id.
 *
 * All of its records will be removed.
 *
 * If no dictionary with such id exists then
 * the function call has no effects.
 *
 * @param[in] id    : id of dictionary to be removed
 */
void dict_clear(unsigned long id);

/*
 * Copies records among two dictionaries.
 *
 * If one of the two dictionaries identified by
 * given ids does not exist then the function call
 * has no effects.
 *
 * @param[in] src_id : id of the source dictionary
 * @param[in] dst_id : id of the destination dictionary
 */
void dict_copy(unsigned long src_id, unsigned long dst_id);

/*
 * Returns the id of global dictionary.
 *
 * Global dictionary is unremovable.
 * dict_remove on it has no effects.
 * 
 */
unsigned long dict_global();

/*
 * Maximum size of global dictionary.
 * 
 * If this size is exceeded then adding elements has no effect
 * on the global dictionary.
 */
const static int MAX_GLOBAL_DICT_SIZE = 42;
 
