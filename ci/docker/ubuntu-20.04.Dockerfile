# SPDX-License-Identifier: GPL-3.0-or-later
#
# Copyright 2021 Simon Marynissen <marynissen.simon@gmail.com>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

FROM ubuntu:20.04 AS environment
ENV PATH=/usr/local/bin:$PATH
RUN apt-get update -q \
&& DEBIAN_FRONTEND=noninteractive apt-get install -yq --no-install-recommends \
git build-essential ninja-build wget ca-certificates\
&& apt-get clean \
&& rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*

RUN wget "https://cmake.org/files/v3.20/cmake-3.20.2-linux-x86_64.sh" \
&& chmod a+x cmake-3.20.2-linux-x86_64.sh \
&& ./cmake-3.20.2-linux-x86_64.sh --prefix=/usr/local/ --skip-license \
&& rm cmake-3.20.2-linux-x86_64.sh


FROM environment AS development
RUN git clone https://github.com/catchorg/Catch2.git \
# && git --git-dir=Catch2/.git checkout -f version
&& cmake -GNinja -SCatch2 -BCatch2/build \
&& cmake --build Catch2/build --target all \
&& cmake --build Catch2/build --target install \
&& rm -rf Catch2

RUN apt-get update -q \
&& DEBIAN_FRONTEND=noninteractive apt-get install -yq --no-install-recommends \
qtdeclarative5-dev qtquickcontrols2-5-dev libqt5x11extras5-dev \
&& apt-get clean \
&& rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*

RUN apt-get update -q \
&& DEBIAN_FRONTEND=noninteractive apt-get install -yq --no-install-recommends \
libcgal-dev \
&& apt-get clean \
&& rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*

RUN git clone https://github.com/microsoft/GSL.git \
&& git --git-dir=GSL/.git checkout -f v3.1.0 \
&& cmake -GNinja -SGSL -BGSL/build -DGSL_TEST:bool=false \
&& cmake --build GSL/build --target all \
&& cmake --build GSL/build --target install \
&& rm -rf GSL

RUN git clone https://github.com/arximboldi/immer.git \
# && git --git-dir=immer/.git checkout -f version
&& cmake -GNinja -Simmer -Bimmer/build -Dimmer_BUILD_TESTS:bool=false \
-Dimmer_BUILD_EXAMPLES:bool=false -Dimmer_BUILD_DOCS:bool=false \
&& cmake --build immer/build --target all \
&& cmake --build immer/build --target install \
&& rm -rf immer

RUN git clone https://github.com/arximboldi/zug.git \
# && git --git-dir=zug/.git checkout -f version
&& cmake -GNinja -Szug -Bzug/build -Dzug_BUILD_TESTS:bool=false \
-Dzug_BUILD_DOCS:bool=false -Dzug_BUILD_EXAMPLES:bool=false \
&& cmake --build zug/build --target all \
&& cmake --build zug/build --target install \
&& rm -rf zug

RUN git clone https://github.com/arximboldi/lager.git \
# && git --git-dir=lager/.git checkout -f version
&& cmake -GNinja -Slager -Blager/build -Dlager_BUILD_TESTS:bool=false \
-Dlager_BUILD_EXAMPLES:bool=false -Dlager_BUILD_DOCS:bool=false \
&& cmake --build lager/build --target all \
&& cmake --build lager/build --target install \
&& rm -rf lager

RUN git clone https://github.com/KDAB/KDDockWidgets.git \
&& git --git-dir=KDDockWidgets/.git checkout -f v1.3.0 \
&& cmake -GNinja -SKDDockWidgets -BKDDockWidgets/build \
-DKDDockWidgets_EXAMPLES:bool=false -DCMAKE_INSTALL_PREFIX=/usr/local \
# -DKDDockWidgets_QTQUICK:bool=true
&& cmake --build KDDockWidgets/build --target all \
&& cmake --build KDDockWidgets/build --target install \
&& rm -rf KDDockWidgets

VOLUME "/oricad"
WORKDIR "/oricad"

ENTRYPOINT ["/bin/sh", "-c"]


#FROM dependencies AS development
#WORKDIR /home/oricad
#COPY . .
#
#FROM development AS build
#RUN cmake -version
#RUN cmake -S. -Bbuild
#RUN cmake --build build --target all


#FROM build AS test
#RUN ctest
