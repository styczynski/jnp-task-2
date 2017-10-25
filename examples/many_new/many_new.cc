#include <cstdio>
#include <cassert>
#include "cdict"
#include "cdictglobal"

int main(void) {
    
    const unsigned long id1 = ::jnp1::dict_new();
    const unsigned long id2 = ::jnp1::dict_new();
    const unsigned long id3 = ::jnp1::dict_new();
    const unsigned long id4 = ::jnp1::dict_new();
    const unsigned long id5 = ::jnp1::dict_new();
    const unsigned long id6 = ::jnp1::dict_new();
    
    ::jnp1::dict_delete(id3);
    ::jnp1::dict_delete(id4);
    
    const unsigned long new_id = ::jnp1::dict_new();
    
    ::jnp1::dict_delete(id1);
    ::jnp1::dict_delete(id2);
    ::jnp1::dict_delete(id5);
    ::jnp1::dict_delete(id3);
    ::jnp1::dict_delete(id6);
    ::jnp1::dict_delete(new_id);
  
    return 0;
}