clear
rm main
cmake CMakeLists.txt
make
rm ex/saida*
rm ex/final*

if [ $# == 1 ]; then

./main ex/certo$1.txt ex/saida$1.txt
#./main ex/saida$1.txt ex/final$1.txt

#echo "======Diff======"
#echo ""
#sdiff ex/certo$1.txt ex/saida$1.txt
#sdiff ex/saida$1.txt ex/final$1.txt
#echo ""

else

echo "======test01======"
./main ex/certo01.txt ex/saida01.txt
./main ex/saida01.txt ex/final01.txt

echo "======test02======"
./main ex/certo02.txt ex/saida02.txt
./main ex/saida02.txt ex/final02.txt

echo "======test03======"
./main ex/certo03.txt ex/saida03.txt
./main ex/saida03.txt ex/final03.txt

echo "======test04======"
./main ex/certo04.txt ex/saida04.txt
./main ex/saida04.txt ex/final04.txt

echo "======test05======"
./main ex/certo05.txt ex/saida05.txt
./main ex/saida05.txt ex/final05.txt

echo "======test06======"
./main ex/certo06.txt ex/saida06.txt
./main ex/saida06.txt ex/final06.txt

echo "======test07======"
./main ex/certo07.txt ex/saida07.txt
./main ex/saida07.txt ex/final07.txt

echo "======test08======"
./main ex/certo08.txt ex/saida08.txt
./main ex/saida08.txt ex/final08.txt

echo "======test09======"
./main ex/certo09.txt ex/saida09.txt
./main ex/saida09.txt ex/final09.txt

echo "======test10======"
./main ex/certo10.txt ex/saida10.txt
./main ex/saida10.txt ex/final10.txt

echo "======test11======"
./main ex/certo11.txt ex/saida11.txt
./main ex/saida11.txt ex/final11.txt

echo "======test12======"
./main ex/certo12.txt ex/saida12.txt
./main ex/saida12.txt ex/final12.txt

echo "======test13======"
./main ex/certo13.txt ex/saida13.txt
./main ex/saida13.txt ex/final13.txt

echo "======test14======"
./main ex/certo14.txt ex/saida14.txt
./main ex/saida14.txt ex/final14.txt

echo "======test15======"
./main ex/certo15.txt ex/saida15.txt
./main ex/saida15.txt ex/final15.txt

echo "======test16======"
./main ex/certo16.txt ex/saida16.txt
./main ex/saida16.txt ex/final16.txt

echo "======test17======"
./main ex/certo17.txt ex/saida17.txt
./main ex/saida17.txt ex/final17.txt

echo "======test18======"
./main ex/certo18.txt ex/saida18.txt
./main ex/saida18.txt ex/final18.txt

echo "======test19======"
./main ex/certo19.txt ex/saida19.txt
./main ex/saida19.txt ex/final19.txt

echo "======test20======"
./main ex/certo20.txt ex/saida20.txt
./main ex/saida20.txt ex/final20.txt

echo "======Diffs======"
echo "\n1\n"
sdiff ex/saida01.txt ex/final01.txt
echo "\n2\n"
sdiff ex/saida02.txt ex/final02.txt
echo "\n3\n"
sdiff ex/saida03.txt ex/final03.txt
echo "\n4\n"
sdiff ex/saida04.txt ex/final04.txt
echo "\n5\n"
sdiff ex/saida05.txt ex/final05.txt
echo "\n6\n"
sdiff ex/saida06.txt ex/final06.txt
echo "\n7\n"
sdiff ex/saida07.txt ex/final07.txt
echo "\n8\n"
sdiff ex/saida08.txt ex/final08.txt
echo "\n9\n"
sdiff ex/saida09.txt ex/final09.txt
echo "\n10\n"
sdiff ex/saida10.txt ex/final10.txt
echo "\n11\n"
sdiff ex/saida11.txt ex/final11.txt
echo "\n12\n"
sdiff ex/saida12.txt ex/final12.txt
echo "\n13\n"
sdiff ex/saida13.txt ex/final13.txt
echo "\n14\n"
sdiff ex/saida14.txt ex/final14.txt
echo "\n15\n"
sdiff ex/saida15.txt ex/final15.txt
echo "\n16\n"
sdiff ex/saida16.txt ex/final16.txt
echo "\n17\n"
sdiff ex/saida17.txt ex/final17.txt
echo "\n18\n"
sdiff ex/saida18.txt ex/final18.txt
echo "\n19\n"
sdiff ex/saida19.txt ex/final19.txt
echo "\n20\n"
sdiff ex/saida20.txt ex/final20.txt

fi
