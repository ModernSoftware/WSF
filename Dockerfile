FROM ubuntu:bionic

LABEL maintainer="Chris Cates <hello@chriscates.ca>"

RUN apt-get update
RUN apt-get install cmake libssl-dev libboost-all-dev libcpprest-dev -y

WORKDIR /app
COPY . .

RUN mkdir docker_build
RUN cmake -Bdocker_build -H. -DEXAMPLE=ON
RUN cd docker_build && make

CMD ["./docker_build/example"]
