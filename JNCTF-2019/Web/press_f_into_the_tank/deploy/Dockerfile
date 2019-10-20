FROM ubuntu:14.04

RUN apt-get update --fix-missing
RUN apt-get install -y apache2
RUN rm /var/www/html/index.html

COPY src/* /var/www/html/
COPY src/run.sh /run.sh
 
RUN chmod +x /run.sh
RUN chmod 777 /var/www/html

EXPOSE 80

CMD ["/run.sh"]
