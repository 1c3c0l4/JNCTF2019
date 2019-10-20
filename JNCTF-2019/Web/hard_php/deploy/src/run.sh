#!/bin/sh
sed -i 's/allow_url_include = Off/allow_url_include = On/g' /etc/php5/apache2/php.ini
/etc/init.d/apache2 start && echo "Servers running :)"
sleep infinity
