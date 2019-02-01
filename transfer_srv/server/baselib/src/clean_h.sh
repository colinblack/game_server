#/sh/bin

for each in `ls *.h`
do
	rm -f ../../baselib/include/$each
done
