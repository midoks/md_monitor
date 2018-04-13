dnl $Id$
dnl config.m4 for extension md_monitor

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

PHP_ARG_WITH(md_monitor, for md_monitor support,
Make sure that the comment is aligned:
[  --with-md_monitor             Include md_monitor support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(md_monitor, whether to enable md_monitor support,
Make sure that the comment is aligned:
[  --enable-md_monitor           Enable md_monitor support])

if test "$PHP_MD_MONITOR" != "no"; then

  dnl # --with-md_monitor -> add include path
  dnl PHP_ADD_INCLUDE($MD_MONITOR_DIR/include)

  dnl # --with-md_monitor -> check for lib and symbol presence
  dnl LIBNAME=md_monitor # you may want to change this
  dnl LIBSYMBOL=md_monitor # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $MD_MONITOR_DIR/$PHP_LIBDIR, MD_MONITOR_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_MD_MONITORLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong md_monitor lib version or lib not found])
  dnl ],[
  dnl   -L$MD_MONITOR_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(MD_MONITOR_SHARED_LIBADD)

  PHP_NEW_EXTENSION(md_monitor, md_monitor.c, $ext_shared)
fi
