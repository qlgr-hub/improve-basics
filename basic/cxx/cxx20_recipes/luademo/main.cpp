#include <iostream>
#include <string>
#include <vector>
#include <lua5.4/lua.hpp>

using namespace std;

class Lua
{
private:
    lua_State* m_pLuaState{ nullptr };
    bool m_IsThread{ false };

public:
    Lua()
        : m_pLuaState{ luaL_newstate() }
    {
        if (m_pLuaState) {
            luaL_openlibs(m_pLuaState);
        }
    }

    Lua(lua_State* pLuaState)
        : m_pLuaState{ pLuaState }
    {
        if (m_pLuaState) {
            luaL_openlibs(m_pLuaState);
        }
    }

    ~Lua()
    {
        if (!m_IsThread && m_pLuaState) {
            lua_close(m_pLuaState);
        }
    }

    Lua(const Lua& other) = delete;
    Lua& operator=(const Lua& other) = delete;

    Lua(Lua&& rvalue)
        : m_pLuaState{ rvalue.m_pLuaState }
        , m_IsThread{ rvalue.m_IsThread }
    {
        rvalue.m_pLuaState = nullptr;
    }

    Lua& operator=(Lua&& rvalue)
    {
        if (this != &rvalue) {
            m_pLuaState = rvalue.m_pLuaState;
            m_IsThread = rvalue.m_IsThread;
            rvalue.m_pLuaState = nullptr;
        }

        return *this;
    }

    bool IsValid() const
    {
        return m_pLuaState != nullptr;
    }

    int LoadFile(const string& filename)
    {
        int status{ luaL_loadfile(m_pLuaState, filename.c_str()) };
        
        if (status == 0) {
            lua_setglobal(m_pLuaState, filename.c_str());
        }

        return status;
    }

    void GetGlobal(const string& name)
    {
        lua_getglobal(m_pLuaState, name.c_str());
    }

    Lua CreateThread()
    {
        Lua threadContext{ lua_newthread(m_pLuaState) };
        threadContext.m_IsThread = true;
        return move(threadContext);
    }

    int ResumeThread()
    {
        return lua_resume(m_pLuaState, m_pLuaState, 0, nullptr);
    }
};

class LuaFunction
{
private:
    Lua& m_Lua;
    string m_FileName;

public:
    LuaFunction(Lua& lua, const string& filename)
        : m_Lua{ lua }
        , m_FileName{ filename }
    {
        int status{ m_Lua.LoadFile(m_FileName) };
    }

    void Push()
    {
        m_Lua.GetGlobal(m_FileName);
    }
};

class LuaThread
{
private:
    Lua m_Lua;
    LuaFunction m_LuaFunction;
    int m_Status{ -1 };

public:
    LuaThread(Lua&& lua, const string& functionFilename)
        : m_Lua{ move(lua) }
        , m_LuaFunction{ m_Lua, functionFilename }
    {

    }

    ~LuaThread() = default;

    LuaThread(const LuaThread& other) = delete;
    LuaThread& operator=(const LuaThread& other) = delete;

    LuaThread(LuaThread&& rvalue) = delete;
    LuaThread& operator=(LuaThread&& rvalue) = delete;

    void Resume()
    {
        if (!IsFinished()) {
            if (m_Status == -1) {
                m_LuaFunction.Push();
            }
            m_Status = m_Lua.ResumeThread();
        }
    }

    bool IsFinished() const
    {
        return m_Status == LUA_OK;
    }
};

int main(int argc, char* argv[])
{
    Lua lua;
    if (lua.IsValid()) {
        const string functionName{ "LuaCode4.lua" };
        LuaThread myThread{ lua.CreateThread(), functionName };

        while (!myThread.IsFinished()) {
            myThread.Resume();
            cout << "myThread yielded or finished!" << endl;
        }
        cout << "myThread finished!" << endl;
    }

    return 0;
}
























// using namespace std;
//
// namespace {
//     int Sum(lua_State* L)
//     {
//         unsigned int numArguments{ static_cast<unsigned int>(lua_gettop(L)) };
//         lua_Number sum{ 0 };
//         for (unsigned int i = 1; i <= numArguments; ++i) {
//             if (!lua_isnumber(L, i)) {
//                 lua_pushstring(L, "incorrect argument");
//                 lua_error(L);
//             }
//             sum += lua_tonumber(L, i);
//         }
//         lua_pushnumber(L, sum / numArguments);
//         lua_pushnumber(L, sum);
//         return 2;
//     }
// }
//
// class Lua
// {
// private:
//     lua_State* m_pLuaState{ nullptr };
//
// public:
//     Lua()
//         : m_pLuaState{ luaL_newstate() }
//     {
//         if (m_pLuaState) {
//             luaL_openlibs(m_pLuaState);
//         }
//     }
//
//     ~Lua()
//     {
//         lua_close(m_pLuaState);
//     }
//
//     Lua(const Lua& other) = delete;
//     Lua& operator=(const Lua& other) = delete;
//
//     Lua(Lua&& rvalue) = delete;
//     Lua& operator=(Lua&& rvalue) = delete;
//
//     bool IsValid() const
//     {
//         return m_pLuaState != nullptr;
//     }
//
//     int LoadFile(const string& filename)
//     {
//         int status{ luaL_loadfile(m_pLuaState, filename.c_str()) };
//        
//         if (status == 0) {
//             lua_setglobal(m_pLuaState, filename.c_str());
//         }
//
//         return status;
//     }
//
//     void GetGlobal(const string& name)
//     {
//         lua_getglobal(m_pLuaState, name.c_str());
//     }
//
//     int PCall()
//     {
//         return lua_pcall(m_pLuaState, 0, LUA_MULTRET, 0);
//     }
//
//     void NewTable(const string& name)
//     {
//         lua_newtable(m_pLuaState);
//         lua_setglobal(m_pLuaState, name.c_str());
//     }
//
//     void PushNumber(double number)
//     {
//         lua_pushnumber(m_pLuaState, number);
//     }
//
//     void SetTableValue(double index, double value)
//     {
//         PushNumber(index);
//         PushNumber(value);
//         lua_rawset(m_pLuaState, -3);
//     }
//
//     double GetNumber()
//     {
//         return lua_tonumber(m_pLuaState, -1);
//     }
//
//     void Pop(int number)
//     {
//         lua_pop(m_pLuaState, number);
//     }
//
//     void CreateCFunction(const string& name, lua_CFunction function)
//     {
//         lua_pushcfunction(m_pLuaState, function);
//         lua_setglobal(m_pLuaState, name.c_str());
//     }
// };
//
// class LuaTable
// {
// private:
//     Lua& m_Lua;
//     string m_Name;
//
// public:
//     LuaTable(Lua& lua, const string& name)
//         : m_Lua{ lua }
//         , m_Name{ name }
//     {
//         m_Lua.NewTable(m_Name);
//     }
//
//     void Set(const vector<int>& values)
//     {
//         Push();
//
//         for (unsigned int i = 0; i < values.size(); ++i) {
//             m_Lua.SetTableValue(i + 1, values[i]);
//         }
//
//         m_Lua.Pop(1);
//     }
//
//     void Push()
//     {
//         m_Lua.GetGlobal(m_Name);
//     }
// };
//
// class LuaFunction
// {
// private:
//     Lua& m_Lua;
//     string m_FileName;
//
//     int PCall()
//     {
//         return m_Lua.PCall();
//     }
//
// public:
//     LuaFunction(Lua& lua, const string& filename)
//         : m_Lua{ lua }
//         , m_FileName{ filename }
//     {
//         m_Lua.LoadFile(m_FileName);
//     }
//
//     ~LuaFunction() = default;
//
//     LuaFunction(const LuaFunction& other) = delete;
//     LuaFunction& operator=(const LuaFunction& other) = delete;
//
//     LuaFunction(LuaFunction&& rvalue) = delete;
//     LuaFunction& operator=(LuaFunction&& rvalue) = delete;
//
// protected:
//     int Call()
//     {
//         m_Lua.GetGlobal(m_FileName);
//         return PCall();
//     }
//
//     double GetReturnValue()
//     {
//         double result{ m_Lua.GetNumber() };
//         m_Lua.Pop(1);
//         return result;
//     }
// };
//
// class PrintTable 
//     : public LuaFunction
// {
// public:
//     PrintTable(Lua& lua, const string& name)
//         : LuaFunction(lua, name)
//     {
//
//     }
//
//     double Call(LuaTable& table)
//     {
//         double sum{};
//
//         int status{ LuaFunction::Call() };
//         if (status) {
//             throw(status);
//         }
//         else {
//             sum = LuaFunction::GetReturnValue();
//         }
//        
//         return sum;
//     }
// };
//
// int main()
// {
//     // Lua lua;
//     // if (lua.IsValid()) {
//     //     const string filename{ "LuaCode1.lua" };
//     //     LuaFunction function(lua, filename);
//     //     function.Call();
//     // }
//
//     Lua lua;
//     if (lua.IsValid()) {
//         const string functionName{ "Sum" };
//         lua.CreateCFunction(functionName, Sum);
//
//         const string tableName{ "cTable" };
//         LuaTable table(lua, tableName);
//
//         vector<int> values{ 1, 2, 3, 4, 5 };
//         table.Set(values);
//
//         const string filename{ "LuaCode3.lua" };
//         PrintTable printTableFunction(lua, filename);
//
//         try {
//             double result{ printTableFunction.Call(table) };
//             cout << "Result: " << result << endl;
//         }
//         catch(int error) {
//             cout << "Call error: " << error << endl;
//         }
//
//         cout << "Waiting" << endl;
//
//         int input;
//         cin >> input;
//
//         // int loop = 2;
//         // while (loop > 0) {
//         //     const string tableName{ "cTable" };
//         //     LuaTable table(lua, tableName);
//         //
//         //     vector<int> values{ 1, 2, 3, 4, 5 };
//         //     table.Set(values);
//         //
//         //     const string filename{ "LuaCode2.lua" };
//         //     PrintTable printTableFunction(lua, filename);
//         //
//         //     try {
//         //         double result{ printTableFunction.Call(table) };
//         //         cout << "Result: " << result << endl;
//         //     }
//         //     catch(int error) {
//         //         cout << "Call error: " << error << endl;
//         //     }
//         //
//         //     cout << "Waiting" << endl;
//         //
//         //     int input;
//         //     cin >> input;
//         //
//         //     -- loop;
//         // }
//     }
//
//     return 0;
// }