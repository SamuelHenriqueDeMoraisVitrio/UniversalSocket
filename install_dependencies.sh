

#src:

rm -rf SilverChain
rm -f CAmalgamator.out

base64 -d build_conf > conf.zip
unzip conf.zip
rm conf.zip

if [ ! -d "build_config" ]; then
    echo "Erro: Pasta 'build_config' não encontrada."
    exit 1
fi

rm -f build_conf

curl -L https://github.com/OUIsolutions/CAmalgamator/releases/download/0.001/CAmalgamator.c  -o CAmalgamator.c
gcc CAmalgamator.c -o CAmalgamator.out
rm -f UniversalSocket.h exempla_test/UniversalSocket.h
echo "
rm -f CAmalgamator.c
./CAmalgamator.out --file src/imports/imports.def.h  -o UniversalSocket.h
cp UniversalSocket.h exempla_test/
cp UniversalSocket.h example/
./darwin build
./build.out
" > build.sh
sh build.sh

git clone -b v0.06 https://github.com/OUIsolutions/SilverChain.git
gcc  SilverChain/src/main.c -o silver.out
echo "./silver.out --src src --tags imp mac types dep const globals dec def  #--watch " > silver_run.sh


#build:

rm -f darwin
curl -L https://github.com/OUIsolutions/Darwin/releases/download/0.011/darwin011.c -o darwin.c
gcc darwin.c -o darwin
rm -f darwin.c

