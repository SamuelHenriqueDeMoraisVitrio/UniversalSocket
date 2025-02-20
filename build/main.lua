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
    darwin.dtw.write_file("UniversalSocketOne.h", one)
end
