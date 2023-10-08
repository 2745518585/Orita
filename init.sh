mkdir $HOME/.Orita
echo $(cd $(dirname $0); pwd) > $HOME/.Orita/path.txt
mkdir bin
g++ orita.cpp -o bin/orita -std=c++20 -O2 -I ${dir}/include -w;