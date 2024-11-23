

rm -rf SilverChain
git clone -b v0.06 https://github.com/OUIsolutions/SilverChain.git
gcc  SilverChain/src/main.c -o silverchain.o
echo "./silver.out --src src --tags mac dep const globals dec def #--watch" > silver_run.sh


