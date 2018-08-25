#!/bin/sh
QT_VERSION=0.3.0
export QT_VERSION
QT_VER=0.3
export QT_VER
QT_VERSION_TAG=030
export QT_VERSION_TAG
QT_INSTALL_DOCS=C:/Qt/Qt5.9.3/Docs/Qt-5.9.3
export QT_INSTALL_DOCS
BUILDDIR=E:/Qt/QtTestCase/SendMail/vender/QtXlsxWriter/src/xlsx
export BUILDDIR
exec 'C:\Qt\Qt5.9.3\5.9.3\mingw53_32\bin\qdoc.exe' "$@"
