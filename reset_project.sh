

if [ ! -d "build_config" ]; then
    echo "Erro: Pasta 'build_config' não encontrada."
    exit 1
fi

[ -f "conf.zip" ] && rm "conf.zip"
zip -r conf.zip build_config

ARQUIVO_CODIFICADO=$(base64 "conf.zip")

echo "$ARQUIVO_CODIFICADO" > build_conf

rm -rf silver.out \
  silver_run.sh \
  build.sh \
  CAmalgamator* \
  SilverChain \
  UniversalSocket.h \
  LuaDoTheWorld \
  darwin \
  conf.zip \
  build_config



