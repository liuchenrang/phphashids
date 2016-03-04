    dnl $Id$
dnl config.m4 for extension phphashids

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(phphashids, for phphashids support,
dnl Make sure that the comment is aligned:
dnl [  --with-phphashids             Include phphashids support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(phphashids, whether to enable phphashids support,
Make sure that the comment is aligned:
[  --enable-phphashids           Enable phphashids support])

if test "$PHP_PHPHASHIDS" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-phphashids -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/phphashids.h"  # you most likely want to change this
  dnl if test -r $PHP_PHPHASHIDS/$SEARCH_FOR; then # path given as parameter
  dnl   PHPHASHIDS_DIR=$PHP_PHPHASHIDS
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for phphashids files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       PHPHASHIDS_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$PHPHASHIDS_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the phphashids distribution])
  dnl fi

  dnl # --with-phphashids -> add include path
  PHP_ADD_INCLUDE($PHPHASHIDS_DIR/include)

  dnl # --with-phphashids -> check for lib and symbol presence
  dnl LIBNAME=phphashids # you may want to change this
  dnl LIBSYMBOL=phphashids # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $PHPHASHIDS_DIR/lib, PHPHASHIDS_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_PHPHASHIDSLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong phphashids lib version or lib not found])
  dnl ],[
  dnl   -L$PHPHASHIDS_DIR/lib -lm
  dnl ])
  dnl
  dnl PHP_SUBST(PHPHASHIDS_SHARED_LIBADD)

  PHP_NEW_EXTENSION(phphashids, phphashids.c,include/hashids/hashids,include/hashids/hashids.c, $ext_shared)
fi

if test -z "$PHP_DEBUG"; then
    AC_ARG_ENABLE(debug,
    [   --enable-debug          compile with debugging symbols],[
        PHP_DEBUG=$enableval
    ],[ PHP_DEBUG=no
    ])
fi