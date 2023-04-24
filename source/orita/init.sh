dir=$(cd $(dirname $0); pwd)
mkdir ${dir}/../../build > /dev/null 2>&1
mkdir ${dir}/../../build/build_orita > /dev/null 2>&1
g++ ${dir}/orita.cpp -o ${dir}/../../build/build_orita/orita -std=c++14 -O2 -I ${dir}/include -w;