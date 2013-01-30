#!/bin/bash
#-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------#
function encdec()
{
	TMP1="$(mktemp)";
	TMP2="$(mktemp)";
	TMP3="$(mktemp)";


	echo -n "${MSG}" > "${TMP1}";
	./bin/base64codec -e "${TMP1}" > "${TMP2}";
	./bin/base64codec -d "${TMP2}" > "${TMP3}";


	HASH1="$(md5sum ${TMP1} | awk '{print $1}')";
	HASH2="$(md5sum ${TMP3} | awk '{print $1}')";


	if [ "${FLAG_DEBUG}" != "" ];
	then
		echo "-------------------------------";
		echo -n "data1(${TMP1}): "; cat "${TMP1}"; echo;
		echo -n "data2(${TMP2}): "; cat "${TMP2}"; echo;
		echo -n "data3(${TMP3}): "; cat "${TMP3}"; echo;
	fi


	if [ "${HASH1}" != "${HASH2}" ];
	then
		echo "ERROR: result different...";

		echo -n "data1(${TMP1}): "; cat "${TMP1}"; echo;
		echo -n "data2(${TMP2}): "; cat "${TMP2}"; echo;
		echo -n "data3(${TMP3}): "; cat "${TMP3}"; echo;
		exit 1;
	fi


	rm "${TMP1}";
	rm "${TMP2}";
	rm "${TMP3}";
}
#-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------#
if [ ! -e ./bin/base64codec ];
then
	echo "ERROR: make it";
	exit 1;
fi


MSG='hello world!';
encdec;
MSG='hello world!!';
encdec;
MSG='hello world!!!';
encdec;
MSG='hello world!!!!';
encdec;
MSG='hello world!!!!!';
encdec;


echo "ok, test passed";

exit 0;
#-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------#
