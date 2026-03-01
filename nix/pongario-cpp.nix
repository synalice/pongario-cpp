# SPDX-FileCopyrightText: © 2026 Nikita Krasnov <nikita.nikita.krasnov@gmail.com>
#
# SPDX-License-Identifier: MIT

{
  lib,
  stdenv,
  meson,
  ninja,
  doxygen,
  pkg-config,
  sfml,
}:
stdenv.mkDerivation {
  pname = "pongario-cpp";
  version = "0.1.0";
  src = ../.;

  doCheck = true;

  outputs = [
    "out"
    "dev"
  ];

  nativeBuildInputs = [
    meson
    ninja
    doxygen
    pkg-config
    sfml
  ];

  meta = {
    homepage = "https://github.com/synalice/pongario-cpp";
    license = [ lib.licenses.mit ];
    mainProgram = "pongario-cpp";
  };
}
