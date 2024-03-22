FROM ubuntu:22.04

RUN apt-get update && apt-get install -y gcc-arm-none-eabi stlink-tools build-essential

WORKDIR /obc
COPY . /obc/src
