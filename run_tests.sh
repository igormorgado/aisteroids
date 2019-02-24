#!/bin/bash

make clean || exit
make tests || exit

TEST_DIR="tests/bin"
pushd "${TEST_DIR}" || exit

PS3="Pick a test to run: "

select TEST in ALL test_* QUIT
do
	[ "${TEST}" == "ALL" ] && break
	[ "${TEST}" == "QUIT" ] && exit
 	if [ -x "${TEST}" ]
 	then
 		./"${TEST}"
 	fi
done

for TEST in test_*
do
 	if [ -x "${TEST}" ]
 	then
 		./"${TEST}" || exit
 	fi
done

echo "##################################################################"
echo "##################################################################"
echo "###                                                            ###"
echo "###     ALL TESTS COMPLETED WITH NICE SUCCESS :-) SMILE!       ###"
echo "###                                                            ###"
echo "##################################################################"
echo "##################################################################"
popd || exit
