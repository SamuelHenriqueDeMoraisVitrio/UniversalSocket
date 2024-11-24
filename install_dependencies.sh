

rm -rf SilverChain
rm -f CAmalgamator.out

curl -L https://github.com/OUIsolutions/CAmalgamator/releases/download/0.001/CAmalgamator.c  -o CAmalgamator.c
gcc CAmalgamator.c -o CAmalgamator.out
rm -f UniversalSocket.h exempla_test/UniversalSocket.h
echo "./CAmalgamator.out --file src/imports/imports.def.h  -o UniversalSocket.h && cp UniversalSocket.h exempla_test/" > build.sh
sh build.sh

git clone -b v0.06 https://github.com/OUIsolutions/SilverChain.git
gcc  SilverChain/src/main.c -o silver.out
echo "./silver.out --src src --tags imp mac types dep const globals dec def  #--watch " > silver_run.sh

