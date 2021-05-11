#!/usr/bin/env sh

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

usage() {
  echo "Usage: $0 [-m] file"
  exit 1
}

multiline=false
while getopts ":m" options; do
  case $options in
    m)
      multiline=true
      ;;
    \?)
      echo 'Error: Only the option m is allowed'
      usage
      ;;
  esac
done
shift $((OPTIND-1))

if [ $# -ne 1 ]
then
  echo "Error: Provide exactly one file ($# were supplied)"
  usage
fi

if [ "$multiline" = true ]
then
  reuse addheader -l GPL-3.0-or-later --copyright-style string \
    -c 'Simon Marynissen <marynissen.simon@gmail.com>' \
    -t header --multi-line "$1"
else
  reuse addheader -l GPL-3.0-or-later --copyright-style string \
    -c 'Simon Marynissen <marynissen.simon@gmail.com>' \
    -t header "$1"
fi
