

local path_universal_main = "../UniversalSocket.h"
local src = "../src/imports/imports.def.h"


dtw.remove_any(path_universal_main)

local one_file = camalgamator.generate_amalgamation(src);

dtw.write_file(path_universal_main, one_file);





