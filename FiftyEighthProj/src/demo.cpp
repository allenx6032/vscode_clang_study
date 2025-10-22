#include <luwra.hpp>

#include <string>
#include <memory>
#include <iostream>

using namespace luwra;

static
void my_function_1(float num, const char* str) {
	std::cout << "my_function_1(" << num << ", " << str << ")" << std::endl;
}

static
std::string my_function_2() {
	return "World";
}

static
int my_function_3(int a, int b) {
	return a + b;
}

static
double sum3(int a, int b, double c) {
	return (a + b) * c;
}

namespace luwra {
	// You may add custom specializations of luwra::Value in order to retrieve them from the stack.
	template <>
	struct Value<char> {
		/**
		 * Retrieve the value at position `n`.
		 */
		static inline
		char read(lua_State* state, int n) {
			auto str = Value<std::string>::read(state, n);

			if (str.length() < 1) {
				luaL_argerror(state, n, "Given empty string instead of character");
			}

			return str[0];
		}

		/**
		 * push the value onto the stack.
		 */
		static inline
		size_t push(lua_State* state, char val) {
			if (val == 0)
				return 0;

			lua_pushlstring(state, &val, 1);

			return 1;
		}
	};
}

static
void read_chars(char a, char b) {
	std::cout << "Got '" << a << b << "'" << std::endl;
}


struct Point {
	double x, y;

	Point(double x, double y):
		x(x), y(y)
	{
		std::cout << "Construct Point(" << x << ", " << y << ")" << std::endl;
	}

	~Point() {
		std::cout << "Destruct Point(" << x << ", " << y << ")" << std::endl;
	}

	void scale(double f) {
		x *= f;
		y *= f;
	}

	std::string __tostring() const {
		return "<Point(" + std::to_string(x) + ", " + std::to_string(y) + ")>";
	}
};

LUWRA_DEF_REGISTRY_NAME(Point, "Point")

int main() {
	StateWrapper state;
	
	state.loadStandardLibrary();

	push(state, 1337);
	push(state, 7731, 1337);

	std::cout << read<int>(state, -3) << std::endl
	          << read<int>(state, -2) << std::endl
	          << read<int>(state, -1) << std::endl;
	
	// Build stack
	state.push(13);
	state.push(37);
	state.push(42.2);

	// Each value can be retrieved individually.
	std::cout << "a = " << state.read<int>(1) << std::endl;
	std::cout << "b = " << state.read<int>(2) << std::endl;
	std::cout << "c = " << state.read<double>(3) << std::endl;

	// ... which is a little cumbersome. Instead we might apply a fitting function to our stack.
	std::cout << "(a + b) * c = "
	          << state.apply(1, sum3)
	          << std::endl;
	          
	// Build stack
	state.push('H');
	state.push('i');

	// apply function to stack values
	state.apply(1, read_chars);
	lua_pop(state, 2);

	// Build stack again
	state.push('Y', 'o');
	state.apply(1, read_chars);
	
	
	state.registerUserType<Point (double, double)>(
		// Constructor name
		"Point",
		// Methods which shall be availabe in the Lua user data, need to be declared here
		{
			LUWRA_MEMBER(Point, scale),
			LUWRA_MEMBER(Point, x),
			LUWRA_MEMBER(Point, y),
			{"magic", luwra::MemberMap {
				{"number", 1337},
				{"string", "Hello World"}
			}}
		},
		// Meta methods may be registered aswell
		{
			LUWRA_MEMBER(Point, __tostring)
		}
	);

	// Load Lua code
	const char* code = (
		// Instantiate type
		"local p = Point(13, 37)\n"
		"print('p =', p)\n"

		// Invoke 'scale' method
		"p:scale(2)\n"
		"print('p =', p)\n"

		// Access 'x' and 'y' property
		"print('p.x =', p:x())\n"
		"print('p.y =', p:y())\n"

		// Modify 'x' property
		"p:x(10)\n"
		"print('p.x =', p:x())\n"

		"print('magicNumber', p.magic.number)\n"
		"print('magicString', p.magic.string)"
	);
	
	state.runString(code);
	
	// Register 'my_function_1'
	state["my_function_1"] = LUWRA_WRAP(my_function_1);

	// Register 'my_function_2'
	state["my_function_2"] = LUWRA_WRAP(my_function_2);

	// Register 'my_function_3'
	state["my_function_3"] = LUWRA_WRAP(my_function_3);

	state.runString(
		// Invoke 'my_function_1'
		"my_function_1(1337, 'Hello')\n"

		// Invoke 'my_function_2'
		"local result2 = my_function_2()\n"
		"print('my_function_2() = ' .. result2)\n"

		// Invoke 'my_function_3'
		"local result3 = my_function_3(13, 37)\n"
		"print('my_function_3(13, 37) = ' .. result3)\n"
	);


	state["foo"] = 1337;

	int r = state.runString(
		"print(foo)"
	);
	
	
	state["t1"] = MemberMap {};

	for (int i = 0; i < 10000; i++) {
		state["t1"]["value"] = i;
		int j = state["t1"]["value"];

		if (j != i) {
			return 1;
		}
	}

	state.runString("t2 = {a = 13, b = 'Hello'}");

	state.runString("t2 = {a = 13, b = 'Hello'}");
	Table t2 = state["t2"];

	LuaType bt = t2["b"];
	if (bt == LuaType::String) {
		std::string b = t2["b"];
		std::cout << b << std::endl;
	}

	std::map<std::string, Reference> ret = state["t2"];
	for (auto pair: ret) {
		std::cout << pair.first << ": ";
		LuaType typ = pair.second;
		switch (typ) {
			case LuaType::Number:
				std::cout << pair.second.read<int>();
				break;

			case LuaType::String:
				std::cout << pair.second.read<std::string>();
				break;

			default:
				std::cout << "Unknown";
				break;

		}
		std::cout << std::endl;
	}

	return 0;
}
