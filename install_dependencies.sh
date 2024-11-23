

rm -rf SilverChain
curl -L https://github.com/OUIsolutions/CAmalgamator/releases/download/0.001/CAmalgamator.c  -o CAmalgamator.c
gcc CAmalgamator.c -o CAmalgamator.o

git clone -b v0.06 https://github.com/OUIsolutions/SilverChain.git
gcc  SilverChain/src/main.c -o silver.out
echo "./silver.out --src src --tags imp mac types dep const globals dec def  #--watch " > silver_run.sh
echo "./CAmalgamator.o --file src/imports/imports.def.h  -o  UniversalSocket.h" > build.sh
