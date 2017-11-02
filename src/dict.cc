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
#include <cassert>
#include <cstdarg>
#include <ostream>

extern "C" {

#include "dict.h"
#include "dictglobal.h"

#define log(...) log_formated(std::cerr, __func__, __VA_ARGS__)

// Constants
#ifndef NDEBUG
    
    // Enable debugging
    constexpr bool DEBUG = true;

#else

    // Disable debugging
    constexpr bool DEBUG = false;
  
#endif

    constexpr bool USE_ID_COMPACT_ALLOC_MODE = false;

    namespace {
        
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
        
        /*
         * Formats dictionary id.
         * Returns human readable representation of
         * specified dictionary.
         *
         * @param[in] id : dictionary id
         * @returns formatted std::string
         */
        std::string format_dict_name(const unsigned long id) {
            if(id == 0) {
                return "the Global Dictionary";
            }
            return "dict " + std::to_string(id);
        }
        
        /*
         * This method works like basic text template.
         *
         * Formats given data with specified formatting string.
         * Formating string can contain any text sequence.
         *
         * If the text contains %{<var_name>} sequence
         * then it's replaced with special value.
         *
         * The special values are the following:
         *  - %{function_name} - replaced by the provided function_name argument
         *  - %{<type>} - replaced by the arguments provided in the variadic list
         *
         * The supported types are:
         *  - int
         *  - ulong (unsigned long)
         *  - dict  (dictionary id)
         *  - size_t
         *  - double
         *  - cstring (or char*) - null-terminated char* array
         *  - string
         *
         * Example call:
         *
         *    log_formated(cout, "test", "%{function_name} %{int}==0 %{string}?", 0, "ala");
         *
         * Example output:
         *
         *    test 0==0 ala?
         *
         * NOTE:
         *   The DEBUG value set to false disables any output.
         *
         * @param[in] out           : output stream
         * @param[in] function_name : value used as %{function_name}
         * @param[in] fmt           : format string
         * @param[in] ...           : args variadic list
         * @returns output stream reference
         */
        std::ostream& log_formated(std::ostream& out,
            const char* function_name, const char* fmt...) {
            
            // Skip is DEBUG is switched off
            if(!DEBUG) return out;
            
            va_list args;
            va_start(args, fmt);
         
            std::string accumulator = "";
            std::string funct_args = "";
            bool formatting_mode_flag = false;
            
            while(*fmt != '\0') {
                if(*fmt == '\n' ) {
                    out << accumulator;
                    out << "\n";
                    accumulator = "";
                } else if(*fmt == '%') {
                    out << accumulator;
                    accumulator = "";
                    formatting_mode_flag = true;
                    ++fmt;
                    if(*fmt != '{') {
                       accumulator += *fmt;
                       formatting_mode_flag = false;
                    }
                } else if(*fmt == '}') {
                   if(formatting_mode_flag) {
                      //
                      // Formatting variable was encountered
                      //
                      if(accumulator == "function_name") {
                          out << std::string(function_name);
                      } else if(accumulator == "int") {
                          const int value = va_arg(args, int);
                          out << value;
                      } else if(accumulator == "ulong") {
                          const unsigned long value = va_arg(args, unsigned long);
                          out << value;
                      } else if(accumulator == "dict") {
                          const unsigned long value = va_arg(args, unsigned long);
                          out << format_dict_name(value);
                      } if(accumulator == "size_t") {
                          const std::size_t value = va_arg(args, std::size_t);
                          out << value;
                      } else if(accumulator == "double") {
                          const double value = va_arg(args, double);
                          out << value;
                      } else if(accumulator == "char*" ||
                                accumulator == "cstring") {
                          const char* value = va_arg(args, char*);
                          out << format_cstring(value);
                      } else if(accumulator == "string") {
                          const std::string value = va_arg(args, std::string);
                          out << value;
                      } else {
                          out << "%{" << accumulator << "}";
                      }
                      accumulator = "";
                      formatting_mode_flag = false;
                   } else {
                      accumulator += *fmt;
                   }                   
                } else {
                   accumulator += *fmt;
                }
                ++fmt;
            }
            out << accumulator;
            accumulator = "";
         
            va_end(args);
            return out;
        }
     
        // Type definitions
        typedef std::unordered_map<std::string, std::string> Dict;
        typedef Dict::const_iterator DictConstIterator;
        typedef std::map<unsigned long, Dict> DictContainer;
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
      
    } //anonymous namespace
       
     
    // Create new dict and return its id
    // If  is ON then ids are reused
    // (after dictionary removal)
    // If not then id assigned once (and even deleted) is never
    // used again.
    unsigned long dict_new() {
        
        log("%{function_name}()\n");
        
        // Find first free id in the container
        static unsigned long global_id_counter = 1;
        unsigned long free_id = 0;
        
        if(USE_ID_COMPACT_ALLOC_MODE) {
            unsigned long last_id = 0;
            bool free_id_found = false;
            
            for ( const auto &dict : get_dict_container() ) {
                if(dict.first != 0 && dict.first != last_id+1) {
                    free_id = last_id+1;
                    free_id_found = true;
                    break;
                }
                last_id = dict.first;
            }
            
            if(!free_id_found) {
                free_id = last_id+1;
            }
        } else {
            free_id = global_id_counter;
            ++global_id_counter;
        }
        
        // There's no value with free_id key
        assert(get_dict_container().find(free_id) == get_dict_container().end());
        // We do not return global dictionary key
        assert(free_id != 0);
        
        // Create new dictionary
        get_dict_container().insert( { free_id, Dict() } );
        
        // Key free_id is now present
        assert(get_dict_container().find(free_id) != get_dict_container().end());    
        
        log("%{function_name}: dict %{dict}\n", free_id);
        
        return free_id;
    }

    // Remove entire dict
    void dict_delete(unsigned long id) {
        
        log("%{function_name}(%{dict})\n", id);
        
        if(id == 0) {
           log("%{function_name}: an attempt to remove the Global Dictionary\n");
        }
        
        if(!is_valid_id(id) || id == 0) return;
        get_dict_container().erase(id);
        
        // There's no dictionary with that key
        assert(!is_valid_id(id));
        
        log("%{function_name}: %{dict} has been deleted\n", id);
    }

    // Count records in dict
    std::size_t dict_size(unsigned long id) {
        
        log("%{function_name}(%{dict})\n", id);
        
        if(!is_valid_id(id)) return 0;
        
        const std::size_t size = get_dict_container()[id].size();

        log("dict %{dict} contains %{size_t} element(s)\n", id);
        
        return size;
    }

    // Create new record in dict
    void dict_insert(unsigned long id, const char* key, const char* value) {
     
        log("%{function_name}(%{dict}, %{cstring}, %{cstring})\n", id, key, value);
        
      
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
      
        // Global dictionary has maximum size MAX_GLOBAL_DICT_SIZE
        assert(id != 0 || get_dict_container()[id].size() <= MAX_GLOBAL_DICT_SIZE);    
      
        log("%{function_name}: dict %{dict}, "
            "the pair (%{cstring}, %{cstring}) "
            "has been inserted\n", id, key, value);
        
    }

    // Remove record from dict
    void dict_remove(unsigned long id, const char* key) {

        log("%{function_name}(%{dict}, %{cstring})\n", id, key);
    
        if(!is_valid_id(id)) return;
        if(key == nullptr) return;
        
        if(get_dict_container()[id].find(key) == get_dict_container()[id].end()) {
           log("%{function_name}: %{dict} does not "
               "contain the key %{cstring}\n", id, key);
        } else {
            get_dict_container()[id].erase(key);
        }
        
        // Dictionary hasn't got that key anymore
        assert(get_dict_container()[id].find(key) == get_dict_container()[id].end());
        
        log("%{function_name}: %{dict}, "
            "the key %{cstring} has been removed\n", id, key);
        
    }

    // Get value from dict
    const char* dict_find(unsigned long id, const char* key) {
      
        log("%{function_name}(%{dict}, %{cstring})\n", id, key);
      
        if(!is_valid_id(id)) return nullptr;
        if(key == nullptr) return nullptr;
        
        // The key could not be NULL
        assert(key != nullptr);
        
        DictConstIterator i = get_dict_container()[id].find(std::string(key));
        if(i == get_dict_container()[id].end()) {
            // Global dictionary lookup
            i = get_dict_container()[0].find(std::string(key));
            if(i == get_dict_container()[id].end()) {
                log("%{function_name}: the key %{cstring} not found\n", key);
                return nullptr;
            }
        }
        
        // Check if i is valid interator object
        assert(i != get_dict_container()[id].end());
        assert(i != get_dict_container()[0].end());
        
        const char* value = (i->second).c_str();
        
        log("%{function_name}: dict %{dict}, "
            "the key %{cstring} has the value %{cstring}\n", id, key, value);
        
        return value;
    }

    // Erase all records in dict
    void dict_clear(unsigned long id) {
        log("%{function_name}(%{dict})\n", id);
        
        if(!is_valid_id(id)) return;
        get_dict_container()[id].clear();
        
        log("%{function_name}: %{dict} has been cleared\n", id);
             
        // The size of dictionary is zero
        assert(get_dict_container()[id].size() == 0); 
    }

    // Copy dicts src -> dst
    void dict_copy(unsigned long src_id, unsigned long dst_id) {

        log("%{function_name}(%{dict}, %{dict})\n", src_id, dst_id);

        // Self copying detected
        // Do nothing as the contents of src and dst
        // is the same
        if(src_id == dst_id) return;
        
        if(!is_valid_id(src_id)) return;
        if(!is_valid_id(dst_id)) return;
        
        unsigned long copied_entries_count = 0;
        
        // Copy to global dict
        if(dst_id == 0) {
            // Prevent overflows
            // Clear global dict
            get_dict_container()[0].clear();
            
            const auto& src_ref = get_dict_container()[src_id];
            std::size_t global_dict_size = get_dict_container()[0].size();
            for(auto& record : src_ref) {
                if(global_dict_size >= MAX_GLOBAL_DICT_SIZE) {
                    // Prevent global dict overflow
                    break;
                }
                
                // Copy record
                get_dict_container()[0][record.first] = record.second;
                ++global_dict_size;
                ++copied_entries_count;
            }
            
            // Never allow to overflow
            assert(get_dict_container()[0].size() <= MAX_GLOBAL_DICT_SIZE);
        } else {
            get_dict_container()[dst_id] = get_dict_container()[src_id];
            copied_entries_count = get_dict_container()[dst_id].size();
            
            // The size of both dictionaries is the same
            assert(get_dict_container()[dst_id].size() == get_dict_container()[src_id].size());
        }
        
        log("%{function_name}: %{ulong} entries were copied\n", copied_entries_count);
        
    }

} // extern C