FROM i386/ubuntu:precise
ARG DEBIAN_FRONTEND=noninteractive

RUN \
  apt-get update; \
  apt-get install -y g++ flex bison gawk make autoconf zlib1g-dev libncurses-dev git subversion gettext unzip bzip2 wget; \
  echo "dash dash/sh boolean false" | debconf-set-selections; \
  dpkg-reconfigure dash