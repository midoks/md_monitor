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

static void process_event_exception(int type, char * error_filename, uint error_lineno, char * msg TSRMLS_DC)
{
    char *event_str;
    int event_str_len;

    event_str_len = spprintf(&event_str, 0, "Exception - type:%d - file:%s - line:%d - msg:%s", type, error_filename, error_lineno, msg);

    mdm_real_log_ex(event_str, event_str_len TSRMLS_CC);
    efree(event_str);
}

void mdm_throw_exception_hook(zval *exception TSRMLS_DC)
{
    zval *message, *file, *line, *code;
#if PHP_VERSION_ID >= 70000
    zval rv;
#endif
    zend_class_entry *default_ce;

    if (!exception)
    {
        return;
    }

#if PHP_VERSION_ID >= 70000
    default_ce = Z_OBJCE_P(exception);
#else
    default_ce = zend_exception_get_default(TSRMLS_C);
#endif

#if PHP_VERSION_ID >= 70000
    message = zend_read_property(default_ce, exception, "message", sizeof("message")-1, 0, &rv);
    file = zend_read_property(default_ce, exception, "file", sizeof("file")-1, 0, &rv);
    line = zend_read_property(default_ce, exception, "line", sizeof("line")-1, 0, &rv);
    code = zend_read_property(default_ce, exception, "code", sizeof("code")-1, 0, &rv);
#else
    message = zend_read_property(default_ce, exception, "message", sizeof("message")-1, 0 TSRMLS_CC);
    file = zend_read_property(default_ce, exception, "file", sizeof("file")-1, 0 TSRMLS_CC);
    line = zend_read_property(default_ce, exception, "line", sizeof("line")-1, 0 TSRMLS_CC);
    code = zend_read_property(default_ce, exception, "code", sizeof("code")-1, 0 TSRMLS_CC);
#endif

    process_event_exception(Z_LVAL_P(code), Z_STRVAL_P(file), Z_LVAL_P(line), Z_STRVAL_P(message) TSRMLS_CC);

    if (old_throw_exception_hook)
    {
        old_throw_exception_hook(exception TSRMLS_CC);
    }
}


static void initExceptionHooks(TSRMLS_D)
{
    if (zend_throw_exception_hook)
    {
        old_throw_exception_hook = zend_throw_exception_hook;
    }

    zend_throw_exception_hook = mdm_throw_exception_hook;
}

static void recoveryExceptionHooks(TSRMLS_D)
{
    if (old_throw_exception_hook)
    {
        zend_throw_exception_hook = old_throw_exception_hook;
    }
}
