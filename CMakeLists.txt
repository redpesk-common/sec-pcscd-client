CMAKE_MINIMUM_REQUIRED(VERSION 3.6)
set (gcc_minimal_version 4.9)

project(pcscs-client
    VERSION 1.0
    DESCRIPTION "Provide pcsc-lite integration with AFB"
    HOMEPAGE_URL "https://github.com/Tux-EVSE/lib-pcscs-client"
    LANGUAGES C)

set(PROJECT_PRETTY_NAME "pcscd-client sharelib for pcscd readers")
set(PROJECT_ICON "icon.jpg")
set(PROJECT_AUTHOR "Iot-Team")
set(PROJECT_AUTHOR_MAIL "secretariat@iot.bzh")
set(PROJECT_LICENSE "Apache-2")
# Where are stored default templates files from submodule or subtree app-templates in your project tree
set(PROJECT_CMAKE_CONF_DIR "conf.d")

include(GNUInstallDirs)
include(FindPkgConfig)
include(CheckIncludeFile)

set(CLOSING_MESSAGE "Debug: ./src/pcscd-client --verbose --config=../etc/simple-scard.json")

add_subdirectory(src)
