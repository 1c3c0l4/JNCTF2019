#!/bin/sh
sed -i 's/AllowOverride None/AllowOverride All/g' /etc/apache2/apache2.conf
/etc/init.d/apache2 start && echo "Servers running :)"
sleep infinity
