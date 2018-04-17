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

//http://php.net/manual/zh/errorfunc.constants.php
static void process_event_error(int type, char * error_filename, uint error_lineno, char * msg TSRMLS_DC)
{
    char *event_str;
    int event_str_len;

    // MDM_G(in_error) = 1;
    // MDM_G(in_error_filename) = (char *)error_filename;
    // MDM_G(in_error_lineno) = (long)error_lineno;
    // ulong t = zend_inline_hash_func("tcp", 4);
    // php_printf("hash:%lu", t);

    event_str_len = spprintf(&event_str, 0, "Error - type:%d - file:%s - line:%d - msg:%s", type, error_filename, error_lineno, msg);
    php_printf("event_str:%s", event_str);

    mdm_real_log_ex(event_str, event_str_len TSRMLS_CC);
    efree(event_str);

    // MDM_G(in_error) = 0;
}

void mdm_error_cb(int type, const char *error_filename, const uint error_lineno, const char *format, va_list args)
{

    char *msg;
    va_list args_copy;
    TSRMLS_FETCH();

    va_copy(args_copy, args);
    vspprintf(&msg, 0, format, args_copy);
    va_end(args_copy);

    process_event_error(type, (char *) error_filename, error_lineno, msg TSRMLS_CC);
    efree(msg);
    
    //error intercept
    old_error_cb(type, error_filename, error_lineno, format, args);
}

static void initErrorHooks(TSRMLS_D)
{
    old_error_cb = zend_error_cb;
    zend_error_cb = mdm_error_cb;
}

static void recoveryErrorHooks(TSRMLS_D)
{   
    if (old_error_cb)
    {
        zend_error_cb = old_error_cb;
    }
}
