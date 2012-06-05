while [ 1 == 1 ]
do
	bash <<HAHA
		sleep 10
		bash <<HOHO
			sleep 10
HOHO
HAHA
done
