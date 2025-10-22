#include <luaautoc/lautoc.h>

float power(float val, int pow) {
  float x = 1.0;
  for(int i = 0; i < pow; i++) {
    x = x * val;
  }
  return x;
}

typedef struct {
  int fst, snd;
} pair;

static int luaA_push_pair(lua_State* L, luaA_Type t, const void* c_in) {
  pair* p = (pair*)c_in;
  lua_pushinteger(L, p->fst);
  lua_pushinteger(L, p->snd);
  return 2;
}

static void luaA_to_pair(lua_State* L, luaA_Type t, void* c_out, int index) {
  pair* p = (pair*)c_out;
  p->snd = lua_tointeger(L, index);
  p->fst = lua_tointeger(L, index-1);
}

typedef struct {
  int id;
  int legs;
  float height;
} table;


typedef struct {
  char* name;
  int num_wings;
} birdie;

birdie test_birdie;

birdie* get_instance_ptr(lua_State* L) {
  return &test_birdie;
}

int birdie_index(lua_State* L) {
  const char* membername = lua_tostring(L, -1);
  birdie* self = get_instance_ptr(L);
  return luaA_struct_push_member_name(L, birdie, membername, self);
}

int birdie_newindex(lua_State* L) {
  const char* membername = lua_tostring(L, -2);
  birdie* self = get_instance_ptr(L);
  luaA_struct_to_member_name(L, birdie, membername, self, -1);
  return 0;
}

typedef enum {
  DIAMONDS,
  HEARTS,
  CLUBS,
  SPADES,
  INVALID = -1
} cards;

int fib(int n) {
  if (n == 0) { return 1; }
  if (n == 1) { return 1; }
  return fib(n-1) + fib(n-2);
}


void hello_world(void) {
  puts("Hello World!");
}

void hello_repeat(int times) {
  for (int i = 0; i < times; i++) {
    hello_world();
  }
}

void hello_person(const char* person) {
  printf("Hello %s!\n", person);
}

int hello_subcount(const char* greeting) {
  int count = 0;
  const char *tmp = greeting;
  while((tmp = strstr(tmp, "hello"))) {
    count++; tmp++;
  }
  return count;
}

/* Hello Module End */

int C(lua_State* L) {
  return luaA_call_name(L, lua_tostring(L, 1));
}

typedef struct {
  float x, y, z;
} vec3;

int main(int argc, char **argv) {
  
  test_birdie.name = "MrFlingly";
  test_birdie.num_wings = 2;
  
  
  lua_State* L = luaL_newstate();
  luaA_open(L);
  
  luaA_function(L, power, float, float, int);
  
  lua_pushnumber(L, 4.2);
  lua_pushinteger(L, 3);
  luaA_call(L, power);
  
  printf("Result: %f\n", lua_tonumber(L, -1));
  lua_pop(L, 1);
  
  
  
  luaA_conversion(L, pair, luaA_push_pair, luaA_to_pair);
	
  pair p = {20, 10};
  luaA_push(L, pair, &p);
  lua_pop(L, 2);
  
  luaA_struct(L, table);
  luaA_struct_member(L, table, id, int);
  luaA_struct_member(L, table, legs, int);
  luaA_struct_member(L, table, height, float);
  
  table t = {0, 4, 0.72};

  luaA_push(L, table, &t);

  lua_getfield(L, -1, "legs");
  printf("legs: %i\n", (int)lua_tointeger(L, -1));
  lua_pop(L, 1);

  lua_getfield(L, -1, "height");
  printf("height: %f\n", lua_tonumber(L, -1));
  lua_pop(L, 1);

  lua_pop(L, 1);
  
  
  
  
  luaA_struct(L, birdie);
  luaA_struct_member(L, birdie, name, char*);
  luaA_struct_member(L, birdie, num_wings, int);
  
  lua_register(L, "birdie_index", birdie_index);
  lua_register(L, "birdie_newindex", birdie_newindex);
  
  luaL_dostring(L, ""
    "Birdie = {}\n"
    "setmetatable(Birdie, Birdie)\n"
    "function Birdie.__call()\n"
    "  local self = {}\n"
    "  setmetatable(self, Birdie)\n"
    "  return self\n"
    "end\n"
    "Birdie.__index = birdie_index\n"
    "Birdie.__newindex = birdie_newindex\n"
    "\n"
    "bird = Birdie()\n"
    "print(bird.name)\n"
    "print(bird.num_wings)\n"
    "bird.num_wings = 3\n"
    "print(bird.num_wings)\n"
    "\n");
    
  
  
  luaA_enum(L, cards);
  luaA_enum_value(L, cards, DIAMONDS);
  luaA_enum_value(L, cards, HEARTS);
  luaA_enum_value(L, cards, CLUBS);
  luaA_enum_value(L, cards, SPADES);
  luaA_enum_value(L, cards, INVALID);

  cards cval = SPADES;
  const char* lval = "SPADES";
  
  luaA_push(L, cards, &cval);
  printf("%i pushed as %s\n", cval, lua_tostring(L, -1));
  lua_pop(L, 1);
  
  lua_pushstring(L, lval);
  luaA_to(L, cards, &cval, -1);
  printf("%s read back as %i\n", lval, cval); 
  lua_pop(L, 1);
  
  
  
   /* Register `fib` function */
  luaA_function(L, fib, int, int);
  
  /* Push integer onto stack and call `fib` */
  lua_pushinteger(L, 25);
  luaA_call(L, fib);
  
  /* Print result & pop */
  printf("Result: %i\n", (int)lua_tointeger(L, -1));
  lua_pop(L, 1);
  
  
  
   luaA_function(L, hello_world, void);
  luaA_function(L, hello_repeat, void, int);
  luaA_function(L, hello_person, void, const char*);
  luaA_function(L, hello_subcount, int, const char*);
  
  lua_register(L, "C", C);
  
  luaL_dostring(L,
    "C('hello_world')\n"
    "C('hello_person', 'Daniel')\n"
    "C('hello_repeat', C('hello_subcount', 'hello hello'))\n"
  );
  
  
  luaA_struct(L, vec3);
  luaA_struct_member(L, vec3, x, float);
  luaA_struct_member(L, vec3, y, float);
  luaA_struct_member(L, vec3, z, float);
  
  vec3 pos = {1.0f, 2.11f, 3.16f};

  luaA_struct_push_member(L, vec3, x, &pos);
  printf("x: %f\n", lua_tonumber(L, -1));
  lua_pop(L, 1);

  lua_pushnumber(L, 0.0);
  luaA_struct_to_member(L, vec3, x, &pos, -1);
  lua_pop(L, 1);

  luaA_struct_push_member(L, vec3, x, &pos);
  printf("x: %f\n", lua_tonumber(L, -1));
  lua_pop(L, 1);
  
  
  luaA_close(L);
  lua_close(L);
  
  return 0;
}