dir=$(cd $(dirname $0); pwd)
mkdir ${dir}/build > /dev/null 2>&1
g++ ${dir}/source/orita.cpp -o ${dir}/build/orita -std=c++14 -O2 -I ${dir}/include -w
g++ ${dir}/source/run.cpp -o ${dir}/build/run -std=c++14 -O2 -I ${dir}/include -w
g++ ${dir}/source/check.cpp -o ${dir}/build/check -std=c++14 -O2 -I ${dir}/include -w
g++ ${dir}/source/judge.cpp -o ${dir}/build/judge -std=c++14 -O2 -I ${dir}/include -w
g++ ${dir}/source/chdata.cpp -o ${dir}/build/chdata -std=c++14 -O2 -I ${dir}/include -w
g++ ${dir}/source/compile.cpp -o ${dir}/build/compile -std=c++14 -O2 -I ${dir}/include -w
g++ ${dir}/source/changna.cpp -o ${dir}/build/changna -std=c++14 -O2 -I ${dir}/include -w
g++ ${dir}/source/cmp.cpp -o ${dir}/build/cmp -std=c++14 -O2 -I ${dir}/include -w
g++ ${dir}/source/setfile.cpp -o ${dir}/build/setfile -std=c++14 -O2 -I ${dir}/include -w
g++ ${dir}/source/reset_Orita.cpp -o ${dir}/build/reset_Orita -std=c++14 -O2 -I ${dir}/include -w