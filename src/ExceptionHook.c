/*
  +----------------------------------------------------------------------+
  | md_monitor                                                           |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2018 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: midoks@163.com                                               |
  +----------------------------------------------------------------------+
*/


static void mdm_throw_exception(int type TSRMLS_DC, const char *format, ...)
{
    va_list args;
    char *message = NULL;

    va_start(args, format);
    vspprintf(&message, 0, format, args);

    if (!MDM_G(ignore_warning))
    {
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "[ md_monitor ] %s", message);
    }

    if (MDM_G(throw_exception) )
    {

#if PHP_VERSION_ID >= 70000
        zend_throw_exception_ex(NULL, type, "%s", message);
#else
        zend_throw_exception_ex(NULL, type TSRMLS_CC, "%s", message);
#endif

    }

    efree(message);
    va_end(args);
}
