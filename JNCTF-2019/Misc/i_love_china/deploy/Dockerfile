FROM ubuntu:16.04

#RUN sed -i "s/http:\/\/archive.ubuntu.com/http:\/\/mirror.yandex.ru/g" /etc/apt/sources.list
RUN apt-get update && apt-get -y dist-upgrade
RUN apt-get install -y lib32z1 
RUN apt-get update
RUN apt-get install -y python3 
RUN apt-get install -y python3-pip
RUN pip install --user primefac
COPY ./bin/ /
EXPOSE 20000
CMD  python3 /server.py 
