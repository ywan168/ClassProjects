

#!/bin/bash

echo "input_dir = $1";
echo "output_dir = $2";

# copy inputdir to outputdir
copy_and_compress()
{
   # copy the inputdir to outputdir, files exclusive.
   rsync -a -f"+ */" -f"- *" $1* $2
   # compress the files to the output dir
   TOTAL_ORIG_NUM=0
   TOTAL_ORIG_SIZE=0
   TOTAL_COMP_NUM=0
   TOTAL_COMP_SIZE=0
   for i in $1* $1**/*
   do
	#echo "$i"
	if [[ -d "$i" ]]
	then 
		echo "It is a directory"
	elif [[ -f "$i" ]]
	then
		echo "**************It is a file**********************"
		ORIGINAL_FILE_NAME=$(echo "$i" | cut -d '.' -f 1)
		TOTAL_ORIG_NUM=$((TOTAL_ORIG_NUM+1))
		echo "Original file name is $i"
		ORIGINAL_FILE_SIZE=$(stat -c%s "$i")
		TOTAL_ORIG_SIZE=$(($ORIGINAL_FILE_SIZE+$TOTAL_ORIG_SIZE))
		echo "Size of $i = $ORIGINAL_FILE_SIZE bytes."
		COMPRESSED_FILE_NAME=${ORIGINAL_FILE_NAME//$1/$2}
		#tar -zcvf $COMPRESSED_FILE_NAME.tgz $i
		tar -zcf $COMPRESSED_FILE_NAME.tgz $i # change -zcvf to zcf becuase no processing info needed
         	TOTAL_COMP_NUM=$((TOTAL_COMP_NUM+1))
         	echo "Compressed file name is $COMPRESSED_FILE_NAME.tgz"
       	        COMPRESSED_FILE_SIZE=$(stat -c%s "$COMPRESSED_FILE_NAME.tgz")
        	TOTAL_COMP_SIZE=$(($COMPRESSED_FILE_SIZE+$TOTAL_COMP_SIZE))
		echo "Size of $COMPRESSED_FILE_NAME.tgz = $COMPRESSED_FILE_SIZE bytes."
	else
		echo "It is not valid"
	fi
   done
   echo "#################  Final statistic information: #########################"
   echo "Total number of original files being processed is $TOTAL_ORIG_NUM"
   echo "Total size of original files is $TOTAL_ORIG_SIZE"
   echo "Total number of tar files is $TOTAL_COMP_NUM"
   echo "Total size of tar files is $TOTAL_COMP_SIZE"
}

#### Main Body of the Script##########

echo "Start of Script"
copy_and_compress $1 $2
echo "End of Script"
