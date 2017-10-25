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
#include <vector>
#include <iostream>

extern "C" {

#include "dict.h"
#ifndef NDEBUG

    constexpr bool DEBUG = true;

#else

    constexpr bool DEBUG = false;
  
#endif

    namespace {
     
        typedef std::unordered_map<std::string, std::string> Dict;
        typedef Dict::const_iterator DictConstIterator;
        typedef std::vector<Dict> DictContainer;
        
        static DictContainer dictionaries = {};

        bool is_valid_id(const unsigned long& id) {
            return dictionaries.size();
        }
        
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
        
        dictionaries.push_back( Dict() );
        const unsigned long new_id = dictionaries.size() - 1;
        
        if(DEBUG) {
            std::cerr << "dict_new: dict " << new_id << " has been created\n";
        }
        
        return new_id;
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
      
        if(DEBUG) {
            std::cerr << "dict_insert(" << id << ", "<< format_cstring(key)
                      << ", " << format_cstring(value) << ")\n";
        }
      
        if(!is_valid_id(id)) return;
        if(key == nullptr || value == nullptr) return;
      
        const std::string key_str(key);
        const std::string value_str(value);
      
        dictionaries[id].insert({ key_str, value_str });
      
        if(DEBUG) {
            std::cerr << "dict_insert: dict " << id << ", the pair (" << format_cstring(key)
                      << ", " << format_cstring(value) << ") has been inserted\n";
        }
    }

    // Remove record from dict
    void dict_remove(unsigned long id, const char* key) {
        // TODO: wikzan
        // TODO: Implement
    }

    // Get value from dict
    const char* dict_find(unsigned long id, const char* key) {
      
        if(DEBUG) {
            std::cerr << "dict_find(" << id << ", "<< format_cstring(key) << ")\n";
        }
      
        if(!is_valid_id(id)) return nullptr;
        const DictConstIterator i = dictionaries[id].find(std::string(key));
        if(i == dictionaries[id].end()) {
            // TODO: Provide global dictionary lookup
            if(DEBUG) {
                std::cerr << "dict_find: the key " << format_cstring(key) << " not found\n";
            }
            return nullptr;
        } else {
            const char* value = (i->second).c_str();
            if(DEBUG) {
                std::cerr << "dict_find: dict " << id << ", the key \"" << (i->first)
                          << "\" has the value \"" << (i->second) << "\"\n";
            }
            return value;
        }
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

} // extern C