FROM i386/ubuntu:precise
ARG DEBIAN_FRONTEND=noninteractive

RUN \
  apt-get update; \
  apt-get install -y autoconf bison bzip2 flex g++ gawk gettext git libncurses-dev make python subversion unzip wget zlib1g-dev; \
  echo "dash dash/sh boolean false" | debconf-set-selections; \
  dpkg-reconfigure dash; \
  locale-gen en_US.UTF-8
