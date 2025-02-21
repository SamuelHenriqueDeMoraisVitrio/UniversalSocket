---@class Darwin
darwin = darwin
---./silver.out --src src --tags imp mac types dep const globals dec def
function main()
    darwin.silverchain.generate({
        src = "src",
        tags = { "dep", "mac", "types", "const", "globals", "dec", "def" },
        project_short_cut = "UniversalSocket"
    })

    local MAX_CONTENT = darwin.camalgamator.ONE_MB * 10
    local MAX_RECURSION = 100

    local one = darwin.camalgamator.generate_amalgamation("src/imports/imports.def.h", MAX_CONTENT, MAX_RECURSION)
    local lincense = "/* " .. darwin.dtw.load_file("LICENSE") .. " */ \n"
    one = lincense .. one
    darwin.dtw.write_file("UniversalSocketOne.h", one)

    local only_declare = darwin.camalgamator.generate_amalgamation("src/imports/imports.dec.h", MAX_CONTENT,
        MAX_RECURSION)
    only_declare = lincense .. only_declare

    darwin.dtw.write_file("UniversalSocket.h", only_declare)

    local only_definition = darwin.camalgamator.generate_amalgamation_with_callback("src/imports/imports.def.h",
        function(import, path)
            if darwin.dtw.ends_with(import, ".c") then
                return "include-once"
            end
            return "dont-include"
        end,
        MAX_CONTENT,
        MAX_RECURSION
    )
    only_definition = '#include "UniversalSocket.h"\n' .. only_definition

    only_definition = lincense .. only_definition


    darwin.dtw.write_file("UniversalSocket.c", only_definition)
end
