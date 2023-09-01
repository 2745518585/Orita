mkdir $HOME/.Orita
echo $(cd $(dirname $0); pwd)/build > $HOME/.Orita/path.txt
g++ bin/orita.cpp -o bin/orita -std=c++20 -O2 -I ${dir}/include -w;