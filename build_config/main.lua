

NOT_OK = "\27[31mNot ok\27[0m"
OK = "\27[32mok\27[0m"

MAIN = "main.c"
COMP = "comp.sh"
RUN = "run.sh"
REQUEST = "request.txt"
RESPONSE = "response.txt"

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

local function verify_file(name, file, error_text)
  if not dtw.isfile(file .. name) then
    error_text[1] = name .. " não existe"
    return false
  end
  return true
end

local function get_error(file, error_text)
  local path_file = dtw.newPath(file)
  --print("\napenas o nome: ", path_file.get_sub_dirs_from_index(path_file.get_total_dirs() - 1, -1))

  local name

  local sucess

  name = COMP
  if not verify_file(name, file, error_text) then
    return NOT_OK
  end

  name = MAIN
  if not verify_file(name, file, error_text) then
    return NOT_OK
  end

  name = RUN
  if not verify_file(name, file, error_text) then
    return NOT_OK
  end

  name = REQUEST
  if not verify_file(name, file, error_text) then
    return NOT_OK
  end

  name = RESPONSE
  if not verify_file(name, file, error_text) then
    return NOT_OK
  end

  sucess = os.execute("cd " .. file .. " && sh " .. COMP .. " > /dev/null 2>&1")

  if not sucess then
    error_text[1] = "Erro ao executar " .. COMP
    return NOT_OK
  end

  sucess = os.execute("cd " .. file .. " && sh " .. RUN .. " > " .. REQUEST)
  if not sucess then
    error_text[1] = "Erro ao executar " .. RUN
  end

  local bool_value, error_value = comparar_arquivos(file .. RESPONSE, file .. REQUEST)
  if not bool_value then
    error_text[1] = error_value
    return NOT_OK
  end

  return OK

end

local function get_dirs()

  local itens = dtw.list_dirs_recursively("example", true)

  for i = 2, #itens do
    local currents = itens[i]
    local bool_path = OK

    local files = dtw.list_files(currents, true)

    local error_text = {}
    if #files > 0 then
      bool_path = get_error(currents, error_text)
    end


    print("\n", currents, bool_path)
    if error_text[1] then
      print("\t" .. error_text[1])
    end

  end

end


get_dirs()
