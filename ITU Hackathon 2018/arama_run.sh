#!/bin/bash
for((A=1;A<10;A++)){
	for((B=A;B<10;B++)){
		for((N=B;N<10;N++)){
			echo $N $A $B | ./arama
		}
	}
}
exit 0
