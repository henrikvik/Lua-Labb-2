#include "LuaState.h"
#include <iostream>

LuaState::LuaState()
{
	state = luaL_newstate();
}

LuaState::~LuaState()
{
	lua_close(state);
}

void LuaState::restart()
{
	lua_close(state);
	state = luaL_newstate();
}

void LuaState::openLibs()
{
	luaL_openlibs(state);
}

void LuaState::doString(const char * str)
{
	int error = luaL_dostring(state, str);
	nassert(error, "luaL_dostring failed");
}

void LuaState::doFile(const char * path)
{
	int error = luaL_dofile(state, path);
	nassert(error, "luaL_dofile failed");
}



void LuaState::get(const char * name)
{
	lua_getglobal(state, name);
}

void LuaState::set(const char * name)
{
	lua_setglobal(state, name);
}

void LuaState::getGlobal(const char * name, const char *& str)
{
	lua_getglobal(state, name);
	pop(str);
}

void LuaState::setGlobal(const char * name, const char * str)
{
	lua_pushstring(state, str);
	lua_setglobal(state, name);
}

void LuaState::call(int args, int returns)
{
	int error = lua_pcall(state, args, returns, NULL);
	nassert(error, "call error");
}

void LuaState::pop(float & number)
{
	if (lua_isnumber(state, -1))
	{
		number = lua_tonumber(state, -1);
		lua_pop(state, 1);
	}
	else
	{
		std::cerr << "top of the stack is not a number" << std::endl;
	}
}

void LuaState::pop(const char *& str)
{
	if (lua_isstring(state, -1))
	{
		str = lua_tostring(state, -1);
		lua_pop(state, 1);
	}
	else
	{
		std::cerr << "top of the stack is not a number" << std::endl;
	}
}

void LuaState::push(float number)
{
	lua_pushnumber(state, number);
}

void LuaState::push(const char * str)
{
	lua_pushstring(state, str);
}

void LuaState::push(int(*fun)(lua_State * state))
{
	lua_pushcfunction(state, fun);
}

void LuaState::getField(const char * tableName, float fieldId, const char *& value)
{
	get(tableName);

	if (lua_istable(state, -1))
	{
		push(fieldId);
		lua_gettable(state, -2);

		if (lua_isstring(state, -1))
		{
			pop
		}
	}
}

inline void LuaState::assert(bool condition, const char * message)
{
	nassert(!condition, message);
}

inline void LuaState::nassert(bool condition, const char * message)
{
	if (condition)
	{
		std::cerr << message << ": " << lua_tostring(state, -1) << std::endl;
		lua_pop(state, 1);
		throw std::exception("assertion failed");
	}
}


