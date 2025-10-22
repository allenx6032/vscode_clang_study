#include <chrono>
#include <iomanip>
#include <memory>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include "HTTPRequest.hpp"

#include "autoupdate/file_version_queue.h"
#include "autoupdate/http_helper.h"
#include "autoupdate/dir_updater.h"
#include "autoupdate/autoupdate_config.h"
#include <algorithm>


// #define PONDER_USES_LUA_IMPL
// #define PONDER_USES_RUNTIME_IMPL
// #include <ponder/class.hpp>
// #include <ponder/classbuilder.hpp>
// #include <ponder/value.hpp>             // TODO: should this be in lua.hpp?
// #include <ponder/detail/rawtype.hpp>    // TODO: should this be in lua.hpp?
// #include <ponder/uses/lua.hpp>
// #include <list>
// #include <cstdio>
// #include <cmath>


// extern "C" {
//     #include <lua/lualib.h>
// }
// #define PLDB(X) X
// #define PASSERT(X) if(!(X)) __builtin_trap()
//
// namespace lib
// {
//     static constexpr float FLOAT_EPSILON = 1e-5f;
//     
//     struct Vec
//     {
//         float   x,y;
//         static int instanceCount;
//         
//         Vec()                       : x(0), y(0) { ++instanceCount; }
//         Vec(float x_, float y_)     : x(x_), y(y_) { ++instanceCount; }
//         Vec(const Vec& o)           : x(o.x), y(o.y) { ++instanceCount; }
//         Vec(Vec&& o)                : x(o.x), y(o.y) { ++instanceCount; }
//         ~Vec() { --instanceCount; }
//         Vec& operator=(const Vec& o) { x = o.x; y = o.y; return *this; }
//
//         bool operator == (const Vec& o) const {
//             const float dx = x - o.x, dy = y - o.y;
//             return std::abs(dx) < FLOAT_EPSILON && std::abs(dy) < FLOAT_EPSILON;
//         }
//         
//         std::tuple<float,float> get() const { return std::make_tuple(x,y); }
//
//         void set(float x_, float y_) { x = x_, y = y_; }
//         
//         Vec operator + (const Vec& o) const { return Vec(x + o.x, y + o.y); }
//         const Vec& operator += (const Vec& o) { x += o.x, y += o.y; return *this; }
//         
//         float length() const        { return std::sqrt(x*x + y*y); }
//         
//         float dot(const Vec &o) const {
//             return x*o.x + y*o.y;
//         }
//         
//         static Vec up() { return Vec(0, 1.f); }     // static function
//         
//         Vec& ref() { return *this; }                // return ref
//     };
//
//     int Vec::instanceCount = 0;
//     
//     struct Holder
//     {
//         Holder() = default;
//         Holder(const Holder&) = delete;              
//         Holder(Holder&&) = default;
//
//         Vec vec;
//         
//         Holder* ptrRef() { return this; }
//         Holder& refRef() { return *this; }
//     };
//     
//     struct Types
//     {
//         struct Obj {
//             Obj(const Obj&) = delete;
//         } o;
//         
//         static int len(const ponder::detail::string_view str) { return (int) str.length(); }
//         
//         Obj* retPtr() { return &o; }
//         void passPtr(Obj *po) {}
//         
//         static const char* getString() { return "blah"; }
//     };
//     
//     struct Static
//     {
//         static int halve(int x) { return x/2; }
//     };
//     int twice(int x) { return 2*x; }
//     
//     enum class Colour { Red, Green, Blue };
//     
//     struct Parsing
//     {
//         int a;
//         std::string b;
//         
//         void init(ponder_ext::LuaTable lt)
//         {
//             assert(lua_istable(lt.L, -1)); // should be guaranteed by conversion
//             
//             lua_getfield(lt.L, -1, "a");
//             a = (int) luaL_checknumber(lt.L, -1);
//             lua_pop(lt.L, 1);
//             
//             lua_getfield(lt.L, -1, "b");
//             b = luaL_checkstring(lt.L, -1);
//             lua_pop(lt.L, 1);
//         }
//     };
//     
//     void declare()
//     {
//         using namespace ponder;
//     
//         ponder::Class::declare<Vec>()
//             .constructor()
//             .constructor<float, float>()
//             .constructor<const Vec&>()
//             .property("x", &Vec::x)
//             .property("y", &Vec::y)
//             .function("get", &Vec::get, policy::ReturnMultiple()) // tuple
//             .function("set", &Vec::set)
//             .function("add", &Vec::operator+=)
//             .function("add2", &Vec::operator+) //.tag("+")
//             .function("length", &Vec::length)
//             .function("dot", &Vec::dot)
//         
//             .function("up", &Vec::up)   // static
//         
//             .function("funcRef", &Vec::ref, policy::ReturnInternalRef())  // ref function
//             .property("propRef", &Vec::ref)     // ref property
//             ;
//
//         ponder::Class::declare<std::tuple<float,float>>();
//
//         ponder::Class::declare<Holder>()
//             .constructor()
//             //  .property("pref", &Holder::ptrRef) // TODO - fix for self ref pointers
//             .function("rref", &Holder::refRef, policy::ReturnInternalRef())
//             .property("vec", &Holder::vec)
//             ;
//
//         ponder::Class::declare<Types>()
//             .function("len", &Types::len)
//             .function("retp", &Types::retPtr, policy::ReturnInternalRef())
//             .function("passp", &Types::passPtr)
//             .function("getStr", &Types::getString)
//             ;
//
//         ponder::Class::declare<Static>()
//             .function("halve", &Static::halve)
//             .function("twice", &twice)
//             ;
//
//         ponder::Enum::declare<Colour>()
//             .value("red", Colour::Red)
//             .value("green", Colour::Green)
//             .value("blue", Colour::Blue)
//             ;
//         
//         ponder::Class::declare<Parsing>()
//             .constructor()
//             .function("init", &Parsing::init)
//             .property("a", &Parsing::a)
//             .property("b", &Parsing::b)
//             ;
//     }
//     
// } // namespace lib
//
// PONDER_TYPE(lib::Vec)
// PONDER_TYPE(std::tuple<float,float>)
// PONDER_TYPE(lib::Holder)
// PONDER_TYPE(lib::Types)
// PONDER_TYPE(lib::Types::Obj)
// PONDER_TYPE(lib::Static)
// PONDER_TYPE(lib::Colour)
// PONDER_TYPE(lib::Parsing)
//
// static bool luaTest(lua_State *L, const char *source, int lineNb, bool success = true)
// {
//     std::printf("l:%d------------------------------------------------------\n", lineNb);
//     std::printf("Test%s: %s\n", success ? "" : "(should fail)", source);
//     const bool ok = ponder::lua::runString(L, source);
//     if (ok != success)
//     {
//         std::printf("FAILED");
//         exit(EXIT_FAILURE);
//         return false;
//     }
//     std::printf("\n");
//     return true;
// }
//
// #define LUA_PASS(SRC) luaTest(L,SRC,__LINE__,true)
// #define LUA_FAIL(SRC) luaTest(L,SRC,__LINE__,false)
//
// static bool Test(bool test, const char msg[])
// {
//     std::printf("Test: %s : %s\n", msg, test ? "PASSED" : "FAILED");
//     return test;
// }
//
// #define TEST(T) if (!Test((T), #T)) return EXIT_FAILURE


// #include "euluna/euluna.hpp"

// double mathex_lerp(double a, double b, double t) {
//     return a + (b-a)*t;
// }
//
// EULUNA_BEGIN_SINGLETON("mathex")
// EULUNA_FUNC_NAMED("lerp", mathex_lerp)
// EULUNA_END()

using std::cout;
using std::endl;

int get_remote_md5_cb(const char* url, const char* filepath, int retcode, size_t content_len) {
    if (retcode != 200) {
        cout << "get remote json failed." << endl;
        return -1;
    }
    FileVersionQueue fq_remote;
    const char* jsonFile = filepath;
    std::string remoteVersion;
    if (!fq_remote.FromJsonFile(jsonFile, remoteVersion)) {
        cout << "FromJsonFile error:" << endl;
        return -1;
    }
    fq_remote.Print();

    FileVersionQueue fq_local;
    fq_local.FromCurrDir();
    fq_local.Print();
    fq_local.SaveJson(g_autoUpateCfg->localMd5JsonLocalDir, remoteVersion);

    FileVersionUpdateInfo update_info;
    fq_local.Diff(fq_remote, update_info);
    auto print = [](const FileVersionInfo& info) { cout << info << endl; };
    cout << endl << "Add" << endl;
    std::for_each(update_info.add.begin(), update_info.add.end(), print);
    cout << endl << "Update" << endl;
    std::for_each(update_info.update.begin(), update_info.update.end(), print);
    cout << endl << "Del" << endl;
    std::for_each(update_info.del.begin(), update_info.del.end(), print);
    cout << endl << endl;

    DirUpdater updater;
    std::string resUrlPrefix = g_autoUpateCfg->resUrl + remoteVersion + "/";
    updater.DoUpdate(update_info, resUrlPrefix);

    return 0;
}

void help() {
    cout << "currently supported mode:" << endl;
    cout << "directly run with no args" << endl;
    cout << "xxx.exe genlocalmd5 123     => 123 is the new version" << endl;
    cout << endl;
}

int genlocalmd5(const std::string& version) {
    int ret = 0;
    FileVersionQueue fq_local;
    ret = fq_local.FromCurrDir();
    if (ret != 0) return ret;
    fq_local.Print();
    ret = fq_local.SaveJson(".\\md5.json", version);
    if (ret != 0) return ret;

    return 0;
}

#include "luaaa.hpp"

#define LOG printf

void bindToLUA(lua_State *);

void runLuaExample(lua_State * ls)
{
    bindToLUA(ls);
    do {
        LOG("------------------------------------------\n");
        std::stringstream buffer;
        std::ifstream file("example.lua");
        if (file)
        {
            buffer << file.rdbuf();
            file.close();
        }
        int err = luaL_loadbuffer(ls, buffer.str().c_str(), buffer.str().length(), "console");
        if (err == 0)
        {
            err = lua_pcall(ls, 0, 0, 0);
        }
        if (err)
        {
            LOG("lua err: %s", lua_tostring(ls, -1));
            lua_pop(ls, 1);
        }
    } while (std::cin.get() != 27);
}

class Cat
{
public:
    Cat()
        : m_age(1), m_weight(1.0f)
    {
        LOG("Cat: a cat spawn at %p.\n", this);
    }

    Cat(const std::string& name)
        : m_name(name), m_age(1), m_weight(1.0f)
    {
        LOG("Cat: %s spawn at %p\n", m_name.c_str(), this);
    }

    ~Cat()
    {
        LOG("Cat: cat[%p] %s is free.\n", this, m_name.c_str());
    }

    const std::string& getName() const {
        LOG("Cat:get name\n");
        return m_name; 
    }

    const std::string& setName(const std::string& name)
    {
        LOG("Cat:set name to %s\n", name.c_str());
        m_name = name; 
        return m_name;
    }

    int setAge(const int age)
    { 
        LOG("Cat:set age to %d\n", age);
        m_age = age; 
        return m_age;
    }

    int getAge() const
    {
        LOG("Cat:get age\n");
        return m_age; 
    }

    float setWeight(float w)
    {
        LOG("Cat:set weight to %f\n", w);
        m_weight = w;
        return m_weight;
    }

    float getWeight() const
    {
        LOG("Cat:get weight\n");
        return m_weight;
    }

    void eat(const std::list<std::string>& foods)
    {
        for (auto & it : foods)
        {
            LOG("%s eat %s.\n", m_name.c_str(), it.c_str());
            m_weight += 0.1f;
        }
        LOG("%s is getting fatter.\n", m_name.c_str());
    }

    void test(int a, const std::string& b, float c, const std::string& d, const std::string& e)
    {
        LOG("cat test: got params from lua: [0: %d, 1:%s, 2:%f, 3:%s, 4:%s]\n", a, b.c_str(), c, d.c_str(), e.c_str());
    }

    std::string toString() const
    { 
        std::stringstream result;
        result << m_name << " is a cat, he is " << m_age <<" years old, has a weight of " << m_weight << " kg.";
        return result.str();
    }

    static void speak(const std::string& w)
    {
        LOG("%s, miaow~~\n", w.c_str());
    }

    void testfunctor(std::function<int(int param)> callback)
    {
	    int result = callback(42);
	    LOG("Callback with argument 42 leads to %d.\n", result);
    }

public:
    std::string prop1;
    std::set<std::string> prop3;
private:
    std::string m_name;
    int m_age;
    float m_weight;
};

std::string getProp1(const Cat& cat) {
    printf("*** READ prop1 ***\n");
    return cat.prop1;
}

void setProp1(Cat& cat, const std::string& val) {
    printf("*** WRITE prop1 ***\n");
    cat.prop1 = val;
}

class SingletonWorld 
{
public:
    static SingletonWorld * getInstance() {
        static SingletonWorld instance("singleton");
        return &instance;
    }

    static SingletonWorld * newInstance(const std::string tagName) {
        return new SingletonWorld(tagName);
    }

    static void delInstance(SingletonWorld * instance) {
        delete instance;
    }
public:
    const std::string getTag() const {
        return mTag;
    }

    SingletonWorld() {
        mTag = "default";
        LOG("SingletonWorld[%s] constructed.\n", mTag.c_str());
    }

    SingletonWorld(const std::string& tagName) : mTag(tagName) {
        LOG("SingletonWorld[%s] constructed.\n", mTag.c_str());
    }

    ~SingletonWorld() {
        LOG("SingletonWorld[%s] destructed.\n", mTag.c_str());
    }
private:
    std::string mTag;
};

class Position {
public:
    float x;
    float y;
    float z;

    Position():x(0), y(0), z(0) {}
    Position(float fx, float fy, float fz):x(fx), y(fy), z(fz) {}
};

//===============================================================================
// example c functions
//===============================================================================
void testSet(const std::set<int>& s1, const std::set<int>& s2)
{
    LOG("testSet: set<int> size: s1:%lu s2:%lu\n", s1.size(), s2.size());
    LOG("--------------------------\n");
    LOG("s1:");
    for (auto it = s1.begin(); it != s1.end(); ++it)
    {
        LOG("%d ", *it);
    }
    LOG("\ns2:");
    for (auto it = s2.begin(); it != s2.end(); ++it)
    {
        LOG("%d ", *it);
    }
    LOG("\n--------------------------\n");
}

void testSetSet(const std::multiset<std::set<std::string>>& s)
{
    LOG("testSetSet: multiset<set<str>> size: %lu\n", s.size());
    LOG("--------------------------\n");
    for (auto it = s.begin(); it != s.end(); ++it)
    {
        LOG("=>set<str> size: %lu\n", it->size());
        for (auto nit = it->begin(); nit != it->end(); ++nit)
        {
            LOG("'%s', ", nit->c_str());
        }
        LOG("\n");
    }
    LOG("\n--------------------------\n");
}

void testMapMap(const std::map<std::string, std::map<std::string, std::string>>& s)
{
    LOG("testMapMap: map<str, map<str, str>> size: %lu\n", s.size());
    LOG("--------------------------\n");
    for (auto it = s.begin(); it != s.end(); ++it)
    {
        LOG("'%s' => map<str, str> size: %lu\n", it->first.c_str(), it->second.size());
        for (auto nit = it->second.begin(); nit != it->second.end(); ++nit)
        {
            LOG("%s = %s, ", nit->first.c_str(),  nit->second.c_str());
        }
        LOG("\n");
    }
    LOG("\n--------------------------\n");
}

const std::tuple<int, std::string, std::string, float> testTuple(std::tuple<std::string, int, float> info) {
    LOG("c++ load lua list to tuple:\n");
    LOG("\t0: '%s'\n", std::get<0>(info).c_str());
    LOG("\t1: %d\n", std::get<1>(info));
    LOG("\t2: %g\n", std::get<2>(info));
    LOG("c++ returns tuple to lua:\n");
    return std::tuple<int, std::string, std::string, float>(123, "string A", "string B", 0.123f);
}

const std::tuple<> testTuple2(std::tuple<> info) {
    LOG("c++ load lua list to empty tuple.\n");
    LOG("c++ returns empty tuple to lua:\n");
    return std::tuple<>();
}

void testMultipleParams(int a, int b, const std::string& c, float d, double e)
{
    LOG("c++ testCallback: got params from lua: [0: %d, 1: %d, 2: %s, 3: %f, 4: %g]\n", a, b, c.c_str(), d, e);
}

void testCallback(int (*f)(const std::string&, int, float), int val, const std::string& str)
{
    auto result = f("a string from c++:" + str, val, 1.2345678f);
    LOG("c++ testCallback: got result from lua callback: %d\n", result);
}

void testCallbackFunctor(std::function<int(const std::string&, int, float)> f, int val, const std::string& str)
{
    auto result = f("a string from c++:" + str, val, 8.7654321f);
    LOG("c++ testCallbackFunctor: got result from lua callback: %d\n", result);
}

//===============================================
// declare custom LuaStack operators
//===============================================
// for GCC, it must be delcared in namespace luaaa.
namespace luaaa {
    template<> struct LuaStack<Position>
    {
        inline static Position get(lua_State * L, int idx)
        {
            auto dict = LuaStack<std::map<std::string, float>>::get(L, idx);
            return Position(dict.find("x")->second, dict.find("y")->second, dict.find("z")->second);
        }

        inline static void put(lua_State * L, const Position & v)
        {
            std::map<std::string, float> dict;
            dict["x"] = v.x;
            dict["y"] = v.y;
            dict["z"] = v.z;
            LuaStack<decltype(dict)>::put(L, dict);
        }
    };
}
//*/

Position testPosition(const Position& a, const Position& b)
{
    return Position(a.x + b.x, a.y + b.y, a.z + b.z);
}

//===============================================
// below shows ho to bind c++ with lua
//===============================================
using namespace luaaa;

int module__index(lua_State* state) {
    LOG("~~~~~~~~~~~~~~~~~~module__index:~~~~~~~~~~~~~~~~~~~");
    lua_pushinteger(state, 999);
    return 1;
}

int module__newindex(lua_State* state) {
    LOG("~~~~~~~~~~~~~~~~~~module__newindex:~~~~~~~~~~~~~~~~~~~");
    lua_rawset(state, -3);
    return 0;
}

void moduleSetProp1(const std::string& val) {
    LOG("moduleSetProp1:%s", val.c_str());
    return;
}


const char* moduleGetProp1() {
    LOG("moduleGetProp1");
    return "string as prop1 value";
}

int moduleSetProp2(int val) {
    LOG("moduleSetProp2:%d", val);
    return val;
}

const char* moduleGetProp2() {
    LOG("moduleGetProp2");
    return "string as prop2 value";
}

void bindToLUA(lua_State * L)
{
    // bind class to lua
    LuaClass<Cat> luaCat(L, "AwesomeCat");
    luaCat.ctor<std::string>();
    luaCat.fun("setName", &Cat::setName);
    luaCat.fun("getName", &Cat::getName);
    luaCat.fun("setAge", &Cat::setAge);
    luaCat.fun("getAge", &Cat::getAge);
    luaCat.fun("eat", &Cat::eat);
    luaCat.fun("speak", &Cat::speak);
    luaCat.fun("test", &Cat::test);
    luaCat.fun("testfunctor", &Cat::testfunctor);
    luaCat.fun(std::string("testFunctor1"), [](int n1, int n2) -> int {
        LOG("testFunctor1:%d, %d\n", n1, n2);
        return n1 * n2;
    });
    luaCat.fun("testFunctor2", std::function<void(int, int)>([](int n1, int n2) {
        LOG("testFunctor2:%d, %d\n", n1, n2);
    }));
    luaCat.fun("__tostring", &Cat::toString);
    luaCat.def("tag", "Animal");

    luaCat.set("say", &Cat::speak);
    luaCat.set("name", &Cat::setName);
    luaCat.get("name", &Cat::getName);
    luaCat.set("age", &Cat::setAge);
    luaCat.get("age", &Cat::getAge);

    luaCat.set("prop1", setProp1);
    luaCat.get("prop1", getProp1);
    luaCat.set("prop2", [](const Cat& cat, float val) -> void { printf("set prop2=%f\n", val); /*cat.setWeight(val)*/; });
    luaCat.get("prop2", [](Cat& cat) -> float { printf("get prop2\n");  return cat.getWeight(); });
    luaCat.set(std::string("prop3"), [](Cat& cat, const std::set<std::string>& val) { printf("set prop3\n");  cat.prop3 = val; });
    luaCat.get(std::string("prop3"), [](const Cat& cat) -> std::set<std::string> { printf("get prop3\n");  return cat.prop3; });
    luaCat.set(std::string("prop4"), [](float val) { printf("set prop4=%f\n", val); });
    luaCat.get(std::string("prop4"), []() -> float { printf("get prop4\n");  return 0.123f; });

    // rise compile error
    //luaCat.set(std::string("prop5"), [](float val, int v2) { printf("set prop5=%f\n", val); });
    //luaCat.get(std::string("prop5"), [](int) -> float { printf("get prop5\n");  return 0.123f; });


    // bind singleton class to lua
    LuaClass<SingletonWorld> luaWorld(L, "SingletonWorld");
    /// use class default constructor as instance spawner, default destructor will be called from gc.
    luaWorld.ctor();
    /// use class constructor as instance spawner, default destructor will be called from gc.
    luaWorld.ctor<const std::string&>("createWithName");
    /// use static function as instance spawner, default destructor will be called from gc.
    luaWorld.ctor("newInstance", &SingletonWorld::newInstance);
    /// use static function as instance spawner and static function as delete function which be called from gc.
    luaWorld.ctor("managedInstance", &SingletonWorld::newInstance , &SingletonWorld::delInstance);
    /// for singleton pattern, set deleter(gc) to nullptr to avoid singleton instance be destroyed.
    luaWorld.ctor("getInstance", &SingletonWorld::getInstance, nullptr);
    luaWorld.fun("getTag", &SingletonWorld::getTag);


    // define a module with name "AwesomeMod"
    LuaModule awesomeMod(L, "AwesomeMod");
    awesomeMod.def("cint", 20190101);
    awesomeMod.def("cstr", "this is c string");
    awesomeMod.def("acat", luaCat);

    std::list<std::string> dict {
        "AMICUS", "AMOS", "AMTRAK", "ANGELICA", "ANNIE OAKLEY", 
        "BEETHOVEN", "BERTHA", "BESSEYA", "BILLIE JEAN", "BIMBO", 
        "BISS", "DECATHLON", "DELIRIUM", "DELIUS", "DEMPSEY" 
    };

    awesomeMod.def("dict", dict);

    // c++11 standard conatiners(array, vector, deque, list, forward_list, set/multiset, map/multimap, unordered_set/unordered_multiset, unordered_map/unordered_multimap)
    awesomeMod.fun("testSet", testSet);
    awesomeMod.fun("testSetSet", testSetSet);
    awesomeMod.fun("testMapMap", testMapMap);
    awesomeMod.fun("testMultipleParams", testMultipleParams);
    awesomeMod.fun("testTuple", testTuple);
    awesomeMod.fun("testTuple2", testTuple2);
    awesomeMod.fun("testCallback", testCallback);
    awesomeMod.fun("testCallbackFunctor", testCallbackFunctor);
    awesomeMod.fun("testPosition", testPosition);
    awesomeMod.fun("testFunctor1", [](int a, float b) {
        LOG("awesomeMod call testFunctor1: %d, %f", a, b);
    });
    awesomeMod.fun("testFunctor2", [](int a, float b) -> float {
        LOG("awesomeMod call testFunctor2(%d * %f = %f):", a, b, a*b);
        return a * b;
    });

    awesomeMod.set("prop1", moduleSetProp1);
    awesomeMod.get("prop1", moduleGetProp1);
    awesomeMod.set("prop2", moduleSetProp2);
    awesomeMod.get("prop2", moduleGetProp2);
    awesomeMod.set(std::string("prop3"), [](const std::string& val) { printf("set prop3=%s\n", val.c_str()); });
    awesomeMod.get(std::string("prop3"), []() -> std::string { printf("get prop3\n");  return "string as prop3"; });
    awesomeMod.set(std::string("prop4"), [](float val) { printf("set prop4=%f\n", val); });
    awesomeMod.get(std::string("prop4"), [](){ printf("get prop4\n"); return 0.123f; });

    awesomeMod.fun("__index", module__index);
    awesomeMod.fun("__newindex", module__newindex);

    // put something to global, just emit the module name
    LuaModule(L).def("pi", 3.1415926535897932);

    LuaModule(L).def("WITHOUT_CPP_STDLIB", !!LUAAA_WITHOUT_CPP_STDLIB);

    // operations can be chained.
    LuaClass<int*>(L, "int")
    .ctor<int*>("new")
    .def("type", std::string("[c int *]"))
    .def("max", INT_MAX)
    .def("min", INT_MIN);

} 

int main(int argc, const char* argv[])
{
    using Clock = std::chrono::high_resolution_clock;
    std::ios_base::sync_with_stdio(false);
    std::cout.setf(std::ios::fixed);
    std::cout.precision(6);
    auto begin = Clock::now();
    std::string line;
    // while (std::getline(std::cin, line)) {
    //     auto now = Clock::now();
    //     auto t = std::chrono::duration<double>(now - begin).count();
    //     std::cout << std::right << std::setw(12) << t << " | " << line << "\n";
    // }
    auto now = Clock::now();
    auto t = std::chrono::duration<double>(now - begin).count();
    std::cout << "-------------|\n" << std::right << std::setw(12) << t << " | total" << std::endl;
           
              
    auto ls = luaL_newstate();
    luaL_openlibs(ls);
    if (ls != NULL)
    {
        runLuaExample(ls);
        lua_close(ls);
    }   
     // Initialize euluna engine using a new lua state
    // EulunaEngine euluna(luaL_newstate());
    // Register C++ bindings to lua
    // EulunaBinder::registerGlobalBindings(&euluna);
    // Example of calling a C++ function from lua and returning its result back to C++
    // double res = euluna.runBuffer<double>("return mathex.lerp(0,10,0.5)");
    // Outputs 5
    // std::cout << res << std::endl;
    
    // std::printf("Lua version %s\n", LUA_VERSION);
        //
    // lua_State *L = luaL_newstate();
    // luaopen_base(L);
        //
    // lib::declare();
    // ponder::lua::expose<lib::Vec>(L, "Vec2");
    // ponder::lua::expose<lib::Holder>(L, "Holder");
    // ponder::lua::expose<lib::Types>(L, "Types");
    // ponder::lua::expose<lib::Static>(L, "Static");
    // ponder::lua::expose<lib::Colour>(L, "Colour");
    // ponder::lua::expose<lib::Parsing>(L, "Parsing");
        //
    //------------------------------------------------------------------
    //
    // TEST(lib::Vec::instanceCount == 0);
    //
    // class defined
    // LUA_PASS("print(Vec2); assert(Vec2 ~= nil)");
    //
    // instance
    // LUA_PASS("v = Vec2(); assert(v ~= nil)");
    // LUA_PASS("assert(type(v) == 'userdata')");
    //
    // property read
    // LUA_PASS("assert(v.x == 0)");
    // LUA_PASS("assert(v.y == 0)");
    //
    // property write
    // LUA_PASS("v.x = 7; assert(v.x == 7)");
    // LUA_PASS("v.y = -3; assert(v.y == -3)");
    // LUA_PASS("assert(type(v.x) == 'number'); assert(type(v.y) == 'number')");
    // LUA_PASS("v.x = 1.25");
    // LUA_PASS("v.x = 1.76e6");
    // LUA_FAIL("v.x = 'fail'");
    //
    // method call with args
    // LUA_PASS("v:set(12, 8.5); assert(v.x == 12 and v.y == 8.5)");
    // LUA_PASS("v:set(1, 2); assert(v.x == 1 and v.y == 2)");
    // LUA_FAIL("v:set('fail'); print(v.x, v.y)");
    // LUA_FAIL("v:set(); print(v.x, v.y)");
    //
    // method call return args
    // LUA_PASS("l = Vec2(3,0); assert(l:length() == 3)");
    //
    // method call with object arg
    // LUA_PASS("a,b = Vec2(2,3), Vec2(3,4); c = a:dot(b); print(c); assert(c == 2*3+3*4)");
    //
    // method call (:) with return object (immutable)
    // LUA_PASS("c = a:add2(b); assert(c ~= nil); print(c.x, c.y);");
    // LUA_PASS("assert(c.x == 5); assert(c.y == 7);");
    //
    // method call (:) with return object (mutable)
    // LUA_PASS("c = a:add(b); assert(c ~= nil); print(c.x, c.y);");
    // LUA_PASS("assert(c.x == 5); assert(c.y == 7);");
    //
    // static func
    // LUA_PASS("assert(type(Vec2.up) == 'function')");
    // LUA_PASS("up = Vec2.up(7); assert(type(up) == 'userdata')");
    // LUA_PASS("assert(type(up.x) == 'number')");
    //
    // Vec return ref (func)
    // LUA_PASS("r = Vec2(7,8); assert(r.x == 7)");
    // LUA_PASS("r.x = 9; assert(r.x == 9)");
    // LUA_PASS("r:funcRef().x = 19; assert(r.x == 19)");
    //
    // Vec return ref (prop)
    // LUA_PASS("r = Vec2(17,8); assert(r.x == 17)");
    // LUA_PASS("r.x = 9; assert(r.x == 9)");
    // LUA_PASS("r.propRef.x = 19; assert(r.x == 19)");
        //
    // Vec return tuple or multiple values.
    // LUA_PASS("t = Vec2(11,22); x,y = t:get(); print(x,y); assert(x == 11); assert(y == 22)");
    //
    //------------------------------------------------------------------
    // Non-copyable return ref
    // LUA_PASS("h = Holder()");
    // LUA_PASS("h:rref().vec.x = 9; assert(h:rref().vec.x == 9)");
        //
    //------------------------------------------------------------------
        //
    // Types
    // LUA_PASS("assert(type(Types) == 'userdata')");
    // LUA_PASS("x = Types.len('two'); assert(type(x) == 'number' and x == 3)");
    // LUA_PASS("assert(Types.len('1234567890') ~= 11)");
        //
    // LUA_PASS("assert(Types.getStr() == 'blah')");
    //
    //------------------------------------------------------------------
    //
    // Class static function
    // LUA_PASS("assert(type(Static) == 'userdata')");
    // LUA_PASS("assert(type(Static.halve) == 'function')");
    // LUA_PASS("x = Static.halve(16); assert(x == 8)");
    //
    // Non-class function
    // LUA_PASS("assert(type(Static) == 'userdata')");
    // LUA_PASS("assert(type(Static.twice) == 'function')");
    // LUA_PASS("x = Static.twice(7); assert(x == 14)");
    //
    //------------------------------------------------------------------
        //
    // Enum
    // LUA_PASS("assert(type(Colour) == 'table')");
    // LUA_PASS("assert(Colour.red == 0)");
    // LUA_PASS("assert(Colour.green == 1)");
    // LUA_PASS("assert(Colour.blue == 2)");
    //
    //------------------------------------------------------------------
        //
    // Parsing
    // LUA_PASS("p = Parsing(); assert(type(p)=='userdata')");
    // LUA_PASS("p:init{a=77, b='w00t'}; assert(p.a == 77 and p.b == 'w00t')");
    //
    // lua_close(L);
    //
    //printf("lib::Vec::instanceCount = %d\n", lib::Vec::instanceCount);
    // TEST(lib::Vec::instanceCount == 0);
    
    // if (argc > 1) {
    //     if (argc < 3) {
    //         help();
    //         return -1;
    //     }
    //     std::string mode = argv[1];
    //     std::string version = argv[2];
    //     if (mode == "genlocalmd5") {
    //         return genlocalmd5(version);
    //     }
    //     help();
    //     return -1;
    // }
    genlocalmd5("main");

    const char* md5remote_url = g_autoUpateCfg->md5jsonUrl.c_str();
    const char* md5remote = g_autoUpateCfg->remoteMd5JsonLocalDir.c_str();
    HttpHelper hhelper;
    hhelper.wget(md5remote_url, md5remote, -1, get_remote_md5_cb);
    
    try
    {
        std::string uri;
        std::string method = "GET";
        std::string arguments;
        std::string output;
        auto protocol = http::InternetProtocol::V4;

        for (int i = 1; i < argc; ++i)
        {
            const auto arg = std::string{argv[i]};

            if (arg == "--help")
            {
                std::cout << "example --url <url> [--protocol <protocol>] [--method <method>] [--arguments <arguments>] [--output <output>]\n";
                return EXIT_SUCCESS;
            }
            else if (arg == "--uri")
            {
                if (++i < argc) uri = argv[i];
                else throw std::runtime_error("Missing argument for --url");
            }
            else if (arg == "--protocol")
            {
                if (++i < argc)
                {
                    if (std::string{argv[i]} == "ipv4")
                        protocol = http::InternetProtocol::V4;
                    else if (std::string{argv[i]} == "ipv6")
                        protocol = http::InternetProtocol::V6;
                    else
                        throw std::runtime_error{"Invalid protocol"};
                }
                else throw std::runtime_error{"Missing argument for --protocol"};
            }
            else if (arg == "--method")
            {
                if (++i < argc) method = argv[i];
                else throw std::runtime_error{"Missing argument for --method"};
            }
            else if (arg == "--arguments")
            {
                if (++i < argc) arguments = argv[i];
                else throw std::runtime_error{"Missing argument for --arguments"};
            }
            else if (arg == "--output")
            {
                if (++i < argc) output = argv[i];
                else throw std::runtime_error{"Missing argument for --output"};
            }
            else
                throw std::runtime_error{"Invalid flag: " + arg};
        }

        http::Request request{uri, protocol};

        const auto response = request.send(method, arguments, {
            {"Content-Type", "application/x-www-form-urlencoded"},
            {"User-Agent", "runscope/0.1"},
            {"Accept", "*/*"}
        }, std::chrono::seconds(2));

        std::cout << response.status.reason << '\n';

        if (response.status.code == http::Status::Ok)
        {
            if (!output.empty())
            {
                std::ofstream outfile{output, std::ofstream::binary};
                outfile.write(reinterpret_cast<const char*>(response.body.data()),
                              static_cast<std::streamsize>(response.body.size()));
            }
            else
                std::cout << std::string{response.body.begin(), response.body.end()} << '\n';
        }
    }
    catch (const http::RequestError& e)
    {
        std::cerr << "Request error: " << e.what() << '\n';
        return EXIT_FAILURE;
    }
    catch (const http::ResponseError& e)
    {
        std::cerr << "Response error: " << e.what() << '\n';
        return EXIT_FAILURE;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << '\n';
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}