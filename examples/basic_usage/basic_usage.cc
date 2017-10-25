#include <cstdio>
#include "cdict"
#include "cdictglobal"

int main(void) {
    printf("Hello world thats the basic test! :)\n");
  
    const unsigned long id = ::jnp1::dict_new();
    ::jnp1::dict_insert(id, "Key", "Value");
    printf("%s\n", ::jnp1::dict_find(id, "Key"));
  
  
    return 0;
}