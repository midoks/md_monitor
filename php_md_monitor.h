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

/* $Id$ */

#ifndef PHP_MD_MONITOR_H
#define PHP_MD_MONITOR_H

#include "include/md_monitor.h"

extern zend_module_entry md_monitor_module_entry;
#define phpext_md_monitor_ptr &md_monitor_module_entry

#ifdef PHP_WIN32
#	define PHP_MD_MONITOR_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_MD_MONITOR_API __attribute__ ((visibility("default")))
#else
#	define PHP_MD_MONITOR_API
#endif


#ifdef ZTS
#include "TSRM.h"
#endif


ZEND_BEGIN_MODULE_GLOBALS(md_monitor)
  int  type;
	char *remote_host;
	char *remote_port;
  char *save_dir;
  char *save_filename;
  int  request_showlog_timeout;

  zend_bool throw_exception;
  zend_bool ignore_warning;
  zend_bool intercept_error;
ZEND_END_MODULE_GLOBALS(md_monitor)

/* Always refer to the globals in your function as MD_MONITOR_G(variable).
   You are encouraged to rename these macros something shorter, see
   examples in any other php module directory.
*/
#define MDM_G(v) ZEND_MODULE_GLOBALS_ACCESSOR(md_monitor, v)

#if defined(ZTS) && defined(COMPILE_DL_MD_MONITOR)
ZEND_TSRMLS_CACHE_EXTERN()
#endif

PHP_MINIT_FUNCTION(md_monitor);
PHP_MSHUTDOWN_FUNCTION(md_monitor);
PHP_RINIT_FUNCTION(md_monitor);
PHP_RSHUTDOWN_FUNCTION(md_monitor);
PHP_MINFO_FUNCTION(md_monitor);

#endif	/* PHP_MD_MONITOR_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */