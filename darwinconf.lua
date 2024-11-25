
darwin.add_lua_file("build_config/main.lua")

local function remove_libs_abs()
  dtw.remove_any("LuaDoTheWorld")
end

local function Load_libs(remove_libs, get_libs)
  if remove_libs then
    remove_libs_abs()
  end

  if get_libs then
    os.execute("git clone -b v0.71 https://github.com/OUIsolutions/LuaDoTheWorld.git")
  end
end

local function Add_lib_global(path, name_func, name_global)
  
  darwin.add_c_code('#include "' .. path .. '"\n')

  darwin.load_lualib_from_c(name_func, name_global)
end

Load_libs(true, true)

Add_lib_global("LuaDoTheWorld/src/one.c", "load_luaDoTheWorld", "dtw")

os.execute("rm -f build.c")

darwin.generate_c_executable_output("build.c")

os.execute("gcc --static build.c -o build.out && rm -f build.c")

remove_libs_abs()

