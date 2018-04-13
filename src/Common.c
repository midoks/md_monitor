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

//test

static php_stream *mdm_stream_open_wrapper(char *opt TSRMLS_DC)
{
    php_stream *stream = NULL;

    mdm_long reslen;

    switch(MDM_G(type)){

        case MDM_TYPE_TCP:
        break;
        case MDM_TYPE_UDP:
        break;
        case MDM_TYPE_FILE:
        break;
        default:
        break;
    }

    stream = php_stream_open_wrapper(opt, "a", IGNORE_URL_WIN, NULL);
    return stream;
}


static int mdm_real_log_ex(char *message, int message_len TSRMLS_DC)
{
    php_stream *stream = NULL;
    char *log_file_path;

    spprintf(&log_file_path, 0, "%s/%s.log", MDM_G(save_dir),"t");

    stream = mdm_stream_open_wrapper(log_file_path);

    if (!stream)
    {
        return FAILURE;
    }

    php_stream_write(stream, message, message_len);

    return SUCCESS;
}


