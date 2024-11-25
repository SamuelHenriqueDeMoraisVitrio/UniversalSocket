

NOT_OK = "\27[31mNot ok\27[0m"
OK = "\27[32mok\27[0m"

local function ler_arquivo(caminho)
    local arquivo = io.open(caminho, "r")
    if not arquivo then
        return nil, "Não foi possível abrir o arquivo."
    end
    local conteudo = arquivo:read("*a")
    arquivo:close()
    return conteudo
end

local function comparar_arquivos(arquivo1, arquivo2)
    local conteudo1, erro1 = ler_arquivo(arquivo1)
    local conteudo2, erro2 = ler_arquivo(arquivo2)

    if erro1 or erro2 then
        return false, (erro1 or erro2)
    end

    if conteudo1 == conteudo2 then
      return true
    else
      return false, "O request e response são diferentes"
    end
end


local function get_error(file, error_text)

  if not error_text[1] then
    local path = dtw.newPath(file)
    local name = path.get_name()
    local dir = path.get_dir()

    local sucess
    if name == "comp.sh" then
      sucess = os.execute("cd " .. dir .. " && sh comp.sh > /dev/null 2>&1")
      if not sucess then
        error_text[1] = "Erro ao compilar;"
        return NOT_OK
      end
    end
    if name == "response.txt" or name == "request.txt" then
      local bool_value, error_value = comparar_arquivos(dir .. "response.txt", dir .. "request.txt")
      if not bool_value then
        error_text[1] = error_value
        return NOT_OK
      end
    end

    return OK
  end

  return NOT_OK
end

local function get_dirs()

  local itens = dtw.list_dirs_recursively("example", true)

  for i = 1, #itens do
    local currents = itens[i]
    local bool_path = OK

    local files = dtw.list_files(currents, true)

    local error_text
    for y = 1, #files do
      error_text = {}
      local files_current = files[y]

      bool_path = get_error(files_current, error_text)

    end

    print("\n", currents, bool_path)
    if bool_path == NOT_OK then
      print("\t" .. error_text[1])
    end

  end

end


get_dirs()
