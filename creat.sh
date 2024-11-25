#!/bin/bash

# Lista de diretórios principais
directories=("example/functions" "example/macros" "example/structs")

# Loop para cada diretório principal
for dir in "${directories[@]}"; do
    # Criar a estrutura de diretórios e arquivos
    for subdir in "$dir"/*/; do
        if [ -d "$subdir" ]; then
            # Criar os arquivos dentro de cada subdiretório
            echo "Criando arquivos em $subdir"
            
            # Criação do arquivo main.c
            echo "// Código C principal" > "$subdir/main.c"
            
            # Criação do arquivo request.txt
            echo "Solicitação de exemplo" > "$subdir/request.txt"
            
            # Criação do arquivo response.txt
            echo "Resposta de exemplo" > "$subdir/response.txt"
            
            # Criação do arquivo comp.sh
            cat << EOF > "$subdir/comp.sh"
#!/bin/bash
gcc main.c --static > /dev/null 2>&1
x86_64-w64-mingw32-gcc main.c -static -lws2_32 > /dev/null 2>&1
./a.out
wine a.exe
EOF

            # Tornar o comp.sh executável
            chmod +x "$subdir/comp.sh"
        fi
    done
done

echo "Arquivos criados com sucesso!"
