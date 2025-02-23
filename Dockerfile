FROM janvik/oatpp:latest

WORKDIR /
ADD . /selene
WORKDIR ./selene

RUN make testServer
RUN ./testServer

EXPOSE 8200 8200

RUN make seleneServer
ENTRYPOINT ["./seleneServer"]

# Used to allow for connection to container so can use commandline
#ENTRYPOINT ["sleep", "infinity"]