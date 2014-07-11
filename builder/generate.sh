
_file=$(cd $(dirname $0); pwd -LP)/calc.so
_out=$(cd $(dirname $0); pwd -LP)/prog.f95.in
_start=$(objdump -h calc.so | grep \\s.text\\s | awk '{ print $6 }')
_size=$(expr $(objdump -h calc.so | grep \\s.rodata\\s | awk '{ print $3 }') \+ $(objdump -h calc.so | grep \\s.rodata\\s | awk '{ print $6 }') \- $_start)
_ep=$(nm calc.so | grep \\sep$ | awk '{ print $1 }')

cd ../generator
sbt "run \"$_file\" $_start $_size $_ep \"$_out\""

