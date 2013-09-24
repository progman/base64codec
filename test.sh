#!/bin/bash
#-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------#
APP='./bin/base64codec';
#-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------#
# run app
function run_app()
{
	STDIN=$(cat);


	if [ "${FLAG_VALGRIND}" != "1" ];
	then
		if [ "${STDIN}" != "" ];
		then
			STDOUT=$(echo "${STDIN}" | ${APP} "${@}");
		else
			STDOUT=$(${APP} "${@}");
		fi
	else
		VAL="valgrind --tool=memcheck --leak-check=yes --leak-check=full --show-reachable=yes --log-file=valgrind.log";

		STDOUT=$(echo "${STDIN}" | ${VAL} ${APP} "${@}");

		echo '--------------------------' >> valgrind.all.log;
		cat valgrind.log >> valgrind.all.log;
		rm -rf valgrind.log;
	fi


	if [ "${STDOUT}" != "" ];
	then
		echo "${STDOUT}";
	fi
}
#-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------#
# test1
function test1()
{
	TMP1="$(mktemp)";
	TMP2="$(mktemp)";
	TMP3="$(mktemp)";


	echo "${MSG}" > "${TMP1}";
	run_app -e "${TMP1}" > "${TMP2}" < /dev/null;
	run_app -d "${TMP2}" > "${TMP3}" < /dev/null;


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
# check depends
function check_prog()
{
	for i in ${1};
	do
		if [ "$(which ${i})" == "" ];
		then
			echo "FATAL: you must install \"${i}\"...";
			return 1;
		fi
	done

	return 0;
}
#-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------#
if [ ! -e "${APP}" ];
then
	echo "ERROR: make it";
	exit 1;
fi


check_prog "awk cat echo md5sum mktemp rm";
if [ "${?}" != "0" ];
then
	exit 1;
fi


MSG='hello world!';
test1;
MSG='hello world!!';
test1;
MSG='hello world!!!';
test1;
MSG='hello world!!!!';
test1;
MSG='hello world!!!!!';
test1;


echo "ok, test passed";
exit 0;
#-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------#
