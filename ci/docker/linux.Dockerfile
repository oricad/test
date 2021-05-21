# syntax=docker/dockerfile:1.2

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

FROM ubuntu:16.04 AS environment

ENV PATH=/usr/local/bin:$PATH

RUN apt-get update -q \
&& DEBIAN_FRONTEND=noninteractive apt-get install -yq --no-install-recommends \
wget ca-certificates unzip git build-essential software-properties-common \
&& apt-get clean \
&& rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*

RUN add-apt-repository -y ppa:ubuntu-toolchain-r/test \
&& apt-get update -q \
&& DEBIAN_FRONTEND=noninteractive apt-get install -yq --no-install-recommends \
gcc-9 g++-9 \
&& update-alternatives --install /usr/bin/gcc gcc /usr/bin/g++-9 60 --slave /usr/bin/g++ g++ /usr/bin/g++-9 \
&& apt-get clean \
&& rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*

RUN wget "https://github.com/ninja-build/ninja/releases/download/v1.10.2/ninja-linux.zip" \
&& unzip ninja-linux.zip -d /usr/local/bin \
&& rm ninja-linux.zip

RUN wget "https://cmake.org/files/v3.20/cmake-3.20.2-linux-x86_64.sh" \
&& chmod a+x cmake-3.20.2-linux-x86_64.sh \
&& ./cmake-3.20.2-linux-x86_64.sh --prefix=/usr/local/ --skip-license \
&& rm cmake-3.20.2-linux-x86_64.sh

RUN apt-get update -q \
&& DEBIAN_FRONTEND=noninteractive apt-get install -yq --no-install-recommends \
libxcomposite-dev libxcb-glx0 libx11-xcb-dev libxrender1 libxkbcommon-x11-0 \
libfontconfig1 libdbus-1-3 libwayland-cursor0 libgl1-mesa-glx mesa-common-dev \
libglu1-mesa-dev \
&& apt-get clean \
&& rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*


FROM environment AS development

RUN wget "https://download.qt.io/official_releases/online_installers/qt-unified-linux-x64-online.run" \
&& chmod +x qt-unified-linux-x64-online.run

RUN --mount=type=secret,id=qt-account-password,required --mount=type=secret,id=qt-account-email,required ./qt-unified-linux-x64-online.run --accept-licenses --accept-obligations --auto-answer telemetry-question=No --confirm-command --reset-qtaccount  --password $(cat /run/secrets/qt-account-password) --email $(cat /run/secrets/qt-account-email) --no-default-installations --no-force-installations install qt.qt5.5152.gcc_64 qt.qt5.5152.qtquick3d \
&& rm qt-unified-linux-x64-online.run

RUN git clone https://github.com/catchorg/Catch2.git -b 'v3.0.0-preview3' --depth 1 \
&& cmake -GNinja -SCatch2 -BCatch2/build -DBUILD_TESTING=false -DCMAKE_BUILD_TYPE=Release \
&& cmake --build Catch2/build --target install \
&& rm -rf Catch2

RUN git clone https://github.com/microsoft/GSL.git -b 'v3.1.0' --depth 1 \
&& cmake -GNinja -SGSL -BGSL/build -DGSL_TEST:bool=false \
&& cmake --build GSL/build --target install \
&& rm -rf GSL

RUN apt-get update -q \
&& DEBIAN_FRONTEND=noninteractive apt-get install -yq --no-install-recommends \
libgmp-dev libmpfr-dev \
&& apt-get clean \
&& rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*

# only headers are needed
RUN wget https://boostorg.jfrog.io/artifactory/main/release/1.76.0/source/boost_1_76_0.tar.gz \
&& tar xzvf boost_1_76_0.tar.gz \
&& cp -R boost_1_76_0/boost /usr/include/ \
&& rm boost_1_76_0.tar.gz \
&& rm -rf boost_1_76_0

RUN git clone https://github.com/CGAL/cgal.git -b 'v5.2.1' --depth 1 \
&& cmake -GNinja -Scgal -Bcgal/build -DCMAKE_BUILD_TYPE=Release \
&& cmake --build cgal/build --target install \
&& rm -rf cgal

RUN git clone https://github.com/arximboldi/zug.git --depth 1 \
# add -b 'v...'
&& cmake -GNinja -Szug -Bzug/build -Dzug_BUILD_TESTS:bool=false \
-Dzug_BUILD_DOCS:bool=false -Dzug_BUILD_EXAMPLES:bool=false \
&& cmake --build zug/build --target install \
&& rm -rf zug

RUN git clone https://github.com/arximboldi/immer.git --depth 1 \
# add -b 'v...'
&& cmake -GNinja -Simmer -Bimmer/build -Dimmer_BUILD_TESTS:bool=false \
-Dimmer_BUILD_EXAMPLES:bool=false -Dimmer_BUILD_DOCS:bool=false \
&& cmake --build immer/build --target install \
&& rm -rf immer

RUN git clone https://github.com/arximboldi/lager.git --depth 1 \
# add -b 'v...'
&& cmake -GNinja -Slager -Blager/build -Dlager_BUILD_TESTS:bool=false \
-Dlager_BUILD_EXAMPLES:bool=false -Dlager_BUILD_DOCS:bool=false \
&& cmake --build lager/build --target install \
&& rm -rf lager

RUN git clone https://github.com/KDAB/KDDockWidgets.git -b 'v1.3.0' --depth 1 \
&& cmake -GNinja -SKDDockWidgets -BKDDockWidgets/build \
-DKDDockWidgets_EXAMPLES:bool=false -DCMAKE_INSTALL_PREFIX=/usr/local -DCMAKE_PREFIX_PATH=/opt/Qt/5.15.2/gcc_64 \
# -DKDDockWidgets_QTQUICK:bool=true
&& cmake --build KDDockWidgets/build --target install \
&& rm -rf KDDockWidgets

VOLUME "/oricad"
WORKDIR "/oricad"

ENTRYPOINT ["/bin/sh", "-c"]
