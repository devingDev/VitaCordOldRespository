cmake_minimum_required(VERSION 2.8)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  if(DEFINED ENV{VITASDK})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain file")
  else()
    message(FATAL_ERROR "Please define VITASDK to point to your SDK path!")
  endif()
endif()

set(SHORT_NAME vita_cord)
project(${SHORT_NAME})
include("${VITASDK}/share/vita.cmake" REQUIRED)

set(VITA_APP_NAME "VitaCord")
set(VITA_TITLEID  "VTCD00001")
set(VITA_VERSION  "01.05")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -fpermissive -std=gnu11 -Wall ")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -fpermissive -std=c++11 -Wall ")


find_package(CURL REQUIRED)
find_package(OpenSSL REQUIRED)

include_directories(
  ../common
)

add_executable(${SHORT_NAME}.elf
  src/easyencryptor.cpp
  src/DiscordApp.cpp
  src/VitaNet.cpp
  src/Discord.cpp
  src/VitaGUI.cpp
  src/main.cpp
  src/log.cpp
  src/VitaIME.cpp
  src/VitaPad.cpp
  src/VitaTouch.cpp
)

target_link_libraries(${SHORT_NAME}.elf


  debugnet
  vita2d
  SceNet_stub
  ScePgf_stub
  ScePvf_stub
  SceGxm_stub
  SceHttp_stub
  SceCtrl_stub
  SceTouch_stub
  SceNetCtl_stub
  SceAppUtil_stub
  SceDisplay_stub
  SceLibKernel_stub
  SceSysmodule_stub
  SceCommonDialog_stub
  ${CURL_LIBRARIES}
  ${OPENSSL_LIBRARIES}
  c
  m
  z
  png
  jpeg
  pthread
  freetype
)

vita_create_self(${SHORT_NAME}.self ${SHORT_NAME}.elf)
vita_create_vpk(${SHORT_NAME}.vpk ${VITA_TITLEID} ${SHORT_NAME}.self
  VERSION ${VITA_VERSION}
  NAME ${VITA_APP_NAME}
  FILE assets/font/symbola.ttf assets/font/symbola.ttf
  FILE assets/font/symbolahint.ttf assets/font/symbolahint.ttf
  FILE assets/font/lastresort.ttf assets/font/lastresort.ttf
  FILE assets/font/opensansemoji.ttf assets/font/opensansemoji.ttf
  FILE assets/font/seguiemj.pgf assets/font/seguiemj.pgf
  FILE assets/font/seguiemj.ttf assets/font/seguiemj.ttf
  FILE assets/images/Vitacord-Background-8BIT.png assets/images/Vitacord-Background-8BIT.png
  FILE assets/images/Vitacord-LoginForm-8BIT.png assets/images/Vitacord-LoginForm-8BIT.png
  FILE assets/images/Vitacord-Loading-8BIT.png assets/images/Vitacord-Loading-8BIT.png
  FILE assets/images/Vitacord-GuildsBG-8BIT.png assets/images/Vitacord-GuildsBG-8BIT.png
  FILE sce_sys/icon0.png sce_sys/icon0.png
  FILE sce_sys/pic0.png sce_sys/pic0.png
  FILE sce_sys/livearea/contents/bg.png sce_sys/livearea/contents/bg.png
  FILE sce_sys/livearea/contents/startup.png sce_sys/livearea/contents/startup.png
  FILE sce_sys/livearea/contents/template.xml sce_sys/livearea/contents/template.xml
)

