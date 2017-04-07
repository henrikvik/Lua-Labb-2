#include <Windows.h>
#include "LuaState.h"
#include "Engine.h"

static int CppDiv(lua_State * state);

void main()
{
	Engine engine;
	engine.run();

	system("pause");
}

void oneToFive()
{
	LuaState lua;
	lua.openLibs();

	lua.doString(R"(print("Hello World!"))");
	lua.doFile("scripts/HelloFromLua.lua");
	lua.doFile("scripts/HelloVariable.lua");
	lua.doFile("scripts/LuaDiv.lua");

	const char * str;
	lua.getGlobal("helloFromLua", str);
	printf("%s\n", str);

	lua.setGlobal("helloFromCpp", "C++ says hello!");
	lua.get("helloCpp");
	lua.call();

	float f1, f2;
	lua.get("LuaDiv");
	lua.push(1.0);
	lua.push(2.0);
	lua.push(3.0);
	lua.call(3, 2);
	lua.pop(f2);
	lua.pop(f1);

	printf("LuaDiv Return %f, %f\n", f1, f2);


	lua.push(CppDiv);
	lua.set("CppDiv");

	lua.get("CppDiv");
	lua.push(1.0);
	lua.push(2.0);
	lua.push(3.0);
	lua.call(3, 2);
	lua.pop(f2);
	lua.pop(f1);

	printf("CppDiv Return %f, %f\n", f1, f2);

	system("pause");
}


int CppDiv(lua_State * state)
{
	if (!lua_isnumber(state, -1) &&
		!lua_isnumber(state, -2) &&
		!lua_isnumber(state, -3))
		throw "not all numbers";

	float a = lua_tonumber(state, -3);
	float b = lua_tonumber(state, -2);
	float c = lua_tonumber(state, -1);
	lua_pop(state, 3);

	lua_pushnumber(state, a / b);
	lua_pushnumber(state, b / c);
	return 2;
}