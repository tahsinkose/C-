#!/bin/bash
counter=1
N=100

array=()
while [ $counter -le $N ]
	do
		
 		array+=($(( ( RANDOM % 4 )  + 2 )))
		((counter++))
done

echo $N
echo ${array[@]}
./ex < inp
echo $foo
