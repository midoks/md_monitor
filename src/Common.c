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
    int first_create_file = 0;
    mdm_long reslen;
    char *res = NULL;

    switch(MDM_G(type)){

        case MDM_TYPE_TCP:

          reslen = spprintf(&res, 0, "tcp://%s:%d", MDM_G(remote_host), MDM_G(remote_port));
          stream = php_stream_xport_create(res, reslen, REPORT_ERRORS, STREAM_XPORT_CLIENT | STREAM_XPORT_CONNECT, 0, 0, NULL, NULL, NULL);

          if (stream == NULL)
          {
              mdm_throw_exception(MDM_EXCEPTION_LOGGER_ERROR TSRMLS_CC, "MDM Can Not Create TCP Connect - %s", res);
              efree(res);
              return NULL;
          }

          efree(res);
          break;
        case MDM_TYPE_UDP:
          reslen = spprintf(&res, 0, "udp://%s:%d", MDM_G(remote_host), MDM_G(remote_port));
          stream = php_stream_xport_create(res, reslen, REPORT_ERRORS, STREAM_XPORT_CLIENT | STREAM_XPORT_CONNECT, 0, 0, NULL, NULL, NULL);

          if (stream == NULL)
          {
              mdm_throw_exception(MDM_EXCEPTION_LOGGER_ERROR TSRMLS_CC, "MDM Can Not Create UDP Connect - %s", res);
              efree(res);
              return NULL;
          }

          efree(res);
          break;
        case MDM_TYPE_FILE:
        break;
        default:
          if (access(opt,F_OK) != 0)
          {
              first_create_file = 1;
          }

          stream = php_stream_open_wrapper(opt, "a", IGNORE_URL_WIN, NULL);

          if (stream == NULL)
          {
              mdm_throw_exception(MDM_EXCEPTION_LOGGER_ERROR TSRMLS_CC, "MDM Invalid Log File - %s", opt);
              return NULL;
          }
          else
          {
              if (first_create_file == 1)
              {
                  VCWD_CHMOD(opt, MDM_FILE_MODE);
              }
          }
    }
    
    return stream;
}


static int mdm_real_log_ex(char *message, int message_len TSRMLS_DC)
{
    php_stream *stream = NULL;
    char *log_file_path;

    spprintf(&log_file_path, 0, "%s/%s.log", MDM_G(save_dir), "t");

    stream = mdm_stream_open_wrapper(log_file_path);

    if (!stream)
    {
        return FAILURE;
    }

    php_stream_write(stream, message, message_len);
    return SUCCESS;
}


