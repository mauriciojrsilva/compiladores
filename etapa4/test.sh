clear
rm main
cmake CMakeLists.txt
make
rm input/saida*
rm input/final*

if [ $# == 1 ]; then

./main input/certo$1.txt input/saida$1.txt
#./main input/saida$1.txt input/final$1.txt

#echo "======Diff======"
#echo ""
#sdiff input/certo$1.txt input/saida$1.txt
#sdiff input/saida$1.txt input/final$1.txt
#echo ""

else

echo "======test01======"
./main input/certo01.txt input/saida01.txt
./main input/saida01.txt input/final01.txt

echo "======test02======"
./main input/certo02.txt input/saida02.txt
./main input/saida02.txt input/final02.txt

echo "======test03======"
./main input/certo03.txt input/saida03.txt
./main input/saida03.txt input/final03.txt

echo "======test04======"
./main inputex/certo04.txt input/saida04.txt
./main input/saida04.txt input/final04.txt

echo "======test05======"
./main input/certo05.txt input/saida05.txt
./main input/saida05.txt input/final05.txt

echo "======test06======"
./main input/certo06.txt input/saida06.txt
./main input/saida06.txt input/final06.txt

echo "======test07======"
./main input/certo07.txt input/saida07.txt
./main input/saida07.txt input/final07.txt

echo "======test08======"
./main input/certo08.txt input/saida08.txt
./main input/saida08.txt input/final08.txt

echo "======test09======"
./main input/certo09.txt input/saida09.txt
./main input/saida09.txt input/final09.txt

echo "======test10======"
./main input/certo10.txt input/saida10.txt
./main input/saida10.txt input/final10.txt

echo "======test11======"
./main input/certo11.txt input/saida11.txt
./main input/saida11.txt input/final11.txt

echo "======test12======"
./main input/certo12.txt input/saida12.txt
./main input/saida12.txt input/final12.txt

echo "======test13======"
./main input/certo13.txt input/saida13.txt
./main input/saida13.txt input/final13.txt

echo "======test14======"
./main input/certo14.txt input/saida14.txt
./main input/saida14.txt input/final14.txt

echo "======test15======"
./main input/certo15.txt input/saida15.txt
./main input/saida15.txt input/final15.txt

echo "======test16======"
./main input/certo16.txt input/saida16.txt
./main input/saida16.txt input/final16.txt

echo "======test17======"
./main input/certo17.txt input/saida17.txt
./main input/saida17.txt input/final17.txt

echo "======test18======"
./main input/certo18.txt input/saida18.txt
./main input/saida18.txt input/final18.txt

echo "======test19======"
./main input/certo19.txt input/saida19.txt
./main input/saida19.txt input/final19.txt

echo "======test20======"
./main input/certo20.txt input/saida20.txt
./main input/saida20.txt input/final20.txt

echo "======Diffs======"
echo "\n1\n"
sdiff input/saida01.txt input/final01.txt
echo "\n2\n"
sdiff input/saida02.txt input/final02.txt
echo "\n3\n"
sdiff input/saida03.txt input/final03.txt
echo "\n4\n"
sdiff input/saida04.txt input/final04.txt
echo "\n5\n"
sdiff input/saida05.txt input/final05.txt
echo "\n6\n"
sdiff input/saida06.txt input/final06.txt
echo "\n7\n"
sdiff input/saida07.txt input/final07.txt
echo "\n8\n"
sdiff input/saida08.txt input/final08.txt
echo "\n9\n"
sdiff input/saida09.txt input/final09.txt
echo "\n10\n"
sdiff input/saida10.txt input/final10.txt
echo "\n11\n"
sdiff input/saida11.txt input/final11.txt
echo "\n12\n"
sdiff input/saida12.txt input/final12.txt
echo "\n13\n"
sdiff input/saida13.txt input/final13.txt
echo "\n14\n"
sdiff input/saida14.txt input/final14.txt
echo "\n15\n"
sdiff input/saida15.txt input/final15.txt
echo "\n16\n"
sdiff input/saida16.txt input/final16.txt
echo "\n17\n"
sdiff input/saida17.txt input/final17.txt
echo "\n18\n"
sdiff input/saida18.txt input/final18.txt
echo "\n19\n"
sdiff input/saida19.txt input/final19.txt
echo "\n20\n"
sdiff input/saida20.txt input/final20.txt

fi
