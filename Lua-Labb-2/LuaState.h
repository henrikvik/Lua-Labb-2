#pragma once
#include <Lua/lua.hpp>
#include <vector>

class LuaState
{
public:
	LuaState();
	~LuaState();

	void restart();

	void openLibs();
	void doString(const char * str);
	void doFile(const char * path);

	void get(const char * name);
	void set(const char * name);

	void getGlobal(const char * name, const char *& str);
	void setGlobal(const char * name, const char * str);

	void call(int args = 0, int returns = 0);

	void pop(float & number);
	void pop(const char *& str);

	void push(float number);
	void push(const char * str);
	void push(int(*fun)(lua_State * state));

	void getField(const char * table, float fieldId, const char *& value);

private:
	lua_State * state;

	inline void assert(bool condition, const char * message);
	inline void nassert(bool condition, const char * message);

};
