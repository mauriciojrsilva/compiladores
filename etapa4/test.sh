clear
sudo rm main
sudo cmake CMakeLists.txt
sudo make
sudo rm input/saida*
sudo rm input/final*

if [ $# = 1 ]; then

sudo ./main input/certo$1.txt input/saida$1.txt
#./main input/saida$1.txt input/final$1.txt

#echo "======Diff======"
#echo ""
#sdiff input/certo$1.txt input/saida$1.txt
#sdiff input/saida$1.txt input/final$1.txt
#echo ""

else

echo "======test01======"
sudo ./main input/certo01.txt input/saida01.txt
sudo ./main input/saida01.txt input/final01.txt

echo "======test02======"
sudo ./main input/certo02.txt input/saida02.txt
sudo ./main input/saida02.txt input/final02.txt

echo "======test03======"
sudo ./main input/certo03.txt input/saida03.txt
sudo ./main input/saida03.txt input/final03.txt

echo "======test04======"
sudo ./main input/certo04.txt input/saida04.txt
sudo ./main input/saida04.txt input/final04.txt

echo "======test05======"
sudo ./main input/certo05.txt input/saida05.txt
sudo ./main input/saida05.txt input/final05.txt

echo "======test06======"
sudo ./main input/certo06.txt input/saida06.txt
sudo ./main input/saida06.txt input/final06.txt

echo "======test07======"
sudo ./main input/certo07.txt input/saida07.txt
sudo ./main input/saida07.txt input/final07.txt

echo "======test08======"
sudo ./main input/certo08.txt input/saida08.txt
sudo ./main input/saida08.txt input/final08.txt

echo "======test09======"
sudo ./main input/certo09.txt input/saida09.txt
sudo ./main input/saida09.txt input/final09.txt

echo "======test10======"
sudo ./main input/certo10.txt input/saida10.txt
sudo ./main input/saida10.txt input/final10.txt

echo "======test11======"
sudo ./main input/certo11.txt input/saida11.txt
sudo ./main input/saida11.txt input/final11.txt

echo "======test12======"
sudo ./main input/certo12.txt input/saida12.txt
sudo ./main input/saida12.txt input/final12.txt

echo "======test13======"
sudo ./main input/certo13.txt input/saida13.txt
sudo ./main input/saida13.txt input/final13.txt

echo "======test14======"
sudo ./main input/certo14.txt input/saida14.txt
sudo ./main input/saida14.txt input/final14.txt

echo "======test15======"
sudo ./main input/certo15.txt input/saida15.txt
sudo ./main input/saida15.txt input/final15.txt

echo "======test16======"
sudo ./main input/certo16.txt input/saida16.txt
sudo ./main input/saida16.txt input/final16.txt

echo "======test17======"
sudo ./main input/certo17.txt input/saida17.txt
sudo ./main input/saida17.txt input/final17.txt

echo "======test18======"
sudo ./main input/certo18.txt input/saida18.txt
sudo ./main input/saida18.txt input/final18.txt

echo "======test19======"
sudo ./main input/certo19.txt input/saida19.txt
sudo ./main input/saida19.txt input/final19.txt

echo "======test20======"
sudo ./main input/certo20.txt input/saida20.txt
sudo ./main input/saida20.txt input/final20.txt

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
