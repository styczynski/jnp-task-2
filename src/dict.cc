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
#include <unordered_map>
#include <map>
#include <vector>
#include <iostream>
#include <functional>

extern "C" {

#include "dict.h"
#include "dictglobal.h"

// Constants
#ifndef NDEBUG
	
	// Enable debugging
    constexpr bool DEBUG = true;

#else

	// Disable debugging
    constexpr bool DEBUG = false;
  
#endif

    namespace {
     
		// Type definitions
        typedef std::unordered_map<std::string, std::string> Dict;
        typedef Dict::const_iterator DictConstIterator;
        typedef std::map<unsigned long, Dict, std::greater<unsigned long>> DictContainer;
		typedef DictContainer::const_iterator DictContainerConstIterator;
		
		/*
		 * Returns the global dictionaries container
		 *
		 * @returns DictContainer object
		 */
		DictContainer& get_dict_container() {
			// Dictionaries container
			// Inited with global dictionary
			// (id = 0)
			static DictContainer dictionaries = { {0, {}} };
		
			return dictionaries;
		}

		/*
		 * Checks if dictionary with given id exists.
		 *
		 * @param[in] id : dictionary id
		 * @returns If the dictionary exists?
		 */
        bool is_valid_id(const unsigned long& id) {
            const DictContainerConstIterator i = get_dict_container().find(id);
			return (i != get_dict_container().end());
        }
        
		/*
		 * Formats C98 (char pointer) string.
		 * Returns string: NULL for NULLs
		 * And string: "<contents>" for non-null pointers 
		 *
		 * @param[in] text : input C98 string
		 * @returns formatted std::string
		 */
        std::string format_cstring(const char* text) {
            if(text == nullptr) {
                return "NULL";
            }
            return "\"" + std::string(text) + "\"";
        }
      
    } //anonymous namespace
       
     
    // Create new dict and return its id
    unsigned long dict_new() {
        
        if(DEBUG) {
            std::cerr << "dict_new()\n";
        }
		
		// Find first free id in the container
		
		unsigned long last_id = 0;
		unsigned long free_id = 0;
		bool free_id_found = false;
		
		for ( const auto &dict : get_dict_container() ) {
			if(dict.first != last_id+1) {
				free_id = last_id+1;
				free_id_found = true;
				break;
			}
			last_id = dict.first;
		}
		
		if(!free_id_found) {
			free_id = last_id+1;
		}
        
		// Create new dictionary
        get_dict_container().insert( { free_id, Dict() } );
        
        if(DEBUG) {
            std::cerr << "dict_new: dict " << free_id << " has been created\n";
        }
        
        return free_id;
    }

    // Remove entire dict
    void dict_delete(unsigned long id) {
		// TODO: Wikzan add debug output
		
		if(!is_valid_id(id) || id == 0) return;
		get_dict_container().erase(id);
    }

    // Count records in dict
    std::size_t dict_size(unsigned long id) {
		if(DEBUG) {
			std::cerr << "dict_size(" << id << ")\n";
		}
		
		if(!is_valid_id(id)) return 0;
		
		const std::size_t size = get_dict_container()[id].size();
		
		if(DEBUG) {
			std::cerr << "dict " << id << " contains " << size << " element(s)\n";
		}
		
		return size;
    }

    // Create new record in dict
    void dict_insert(unsigned long id, const char* key, const char* value) {
      
        if(DEBUG) {
            std::cerr << "dict_insert(" << id << ", "<< format_cstring(key)
                      << ", " << format_cstring(value) << ")\n";
        }
      
        if(!is_valid_id(id)) return;
        if(key == nullptr || value == nullptr) return;
      
		// If it's global dictionary and it's filled
		// then do nothing
		if(id == 0) {
			if(dict_size(0) >= MAX_GLOBAL_DICT_SIZE) {
				return;
			}
		}
	  
        const std::string key_str(key);
        const std::string value_str(value);
      
        get_dict_container()[id].insert({ key_str, value_str });
      
        if(DEBUG) {
            std::cerr << "dict_insert: dict " << id << ", the pair (" << format_cstring(key)
                      << ", " << format_cstring(value) << ") has been inserted\n";
        }
    }

    // Remove record from dict
    void dict_remove(unsigned long id, const char* key) {
        // TODO: Wikzan add debug output
		
		if(!is_valid_id(id)) return;
		get_dict_container()[id].erase(key);
    }

    // Get value from dict
    const char* dict_find(unsigned long id, const char* key) {
      
        if(DEBUG) {
            std::cerr << "dict_find(" << id << ", "<< format_cstring(key) << ")\n";
        }
      
        if(!is_valid_id(id)) return nullptr;
		
        DictConstIterator i = get_dict_container()[id].find(std::string(key));
        if(i == get_dict_container()[id].end()) {
			// Global dictionary lookup
			i = get_dict_container()[0].find(std::string(key));
			if(i == get_dict_container()[id].end()) {
				if(DEBUG) {
					std::cerr << "dict_find: the key " << format_cstring(key) << " not found\n";
				}
				return nullptr;
			}
        }
		
		const char* value = (i->second).c_str();
		if(DEBUG) {
			std::cerr << "dict_find: dict " << id << ", the key \"" << (i->first)
					  << "\" has the value \"" << (i->second) << "\"\n";
		}
		return value;
    }

    // Erase all records in dict
    void dict_clear(unsigned long id) {
        // TODO: Wikzan add debug output
		
		if(!is_valid_id(id)) return;
		get_dict_container()[id].clear();
    }

    // Copy dicts src -> dst
    void dict_copy(unsigned long src_id, unsigned long dst_id) {
        // TODO: Wikzan add debug output
		
		if(!is_valid_id(src_id)) return;
		if(!is_valid_id(dst_id)) return;
		
		get_dict_container()[dst_id] = get_dict_container()[src_id];
    }

} // extern C