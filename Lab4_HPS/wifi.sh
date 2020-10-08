#!/bin/bash
echo '#!/bin/bash
case "$1" in
start)
    printf "Setting ip: "
    ifconfig eth0 down
    ifconfig eth0 up
    udhcpc eth0
    [ $? = 0 ] && echo "OK" || echo "FAIL"
    ;;
*)
    exit 1
    ;;

esac' > /etc/init.d/S60MAC.sh
chmod +x /etc/init.d/S60MAC.sh
systemctl enable S60MAC.sh