/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
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

#include "php_md_monitor.h"
ZEND_DECLARE_MODULE_GLOBALS(md_monitor)

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"

#include "src/Common.c"
#include "src/ErrorHook.c"
#include "src/ExceptionHook.c"

/* True global resources - no need for thread safety here */
static int le_md_monitor;

/* {{{ PHP_INI
 */
PHP_INI_BEGIN()

STD_PHP_INI_ENTRY("md_monitor.type", "0", PHP_INI_ALL, OnUpdateLongGEZero, type, zend_md_monitor_globals, md_monitor_globals)

STD_PHP_INI_ENTRY("md_monitor.save_dir", "/var/log/www", PHP_INI_ALL, OnUpdateString, save_dir, zend_md_monitor_globals, md_monitor_globals)
STD_PHP_INI_ENTRY("md_monitor.save_filename", "default", PHP_INI_ALL, OnUpdateString, save_filename, zend_md_monitor_globals, md_monitor_globals)


STD_PHP_INI_ENTRY("md_monitor.remote_host", "127.0.0.1", PHP_INI_ALL, OnUpdateString, remote_host, zend_md_monitor_globals, md_monitor_globals)
STD_PHP_INI_ENTRY("md_monitor.remote_port", "1024", PHP_INI_ALL, OnUpdateString, remote_port, zend_md_monitor_globals, md_monitor_globals)

STD_PHP_INI_ENTRY("md_monitor.request_showlog_timeout", "3", PHP_INI_ALL, OnUpdateLongGEZero, request_showlog_timeout, zend_md_monitor_globals, md_monitor_globals)


STD_PHP_INI_BOOLEAN("md_monitor.throw_exception", "1", PHP_INI_ALL, OnUpdateBool, throw_exception, zend_md_monitor_globals, md_monitor_globals)
STD_PHP_INI_BOOLEAN("md_monitor.ignore_warning", "1", PHP_INI_ALL, OnUpdateBool, ignore_warning, zend_md_monitor_globals, md_monitor_globals)

PHP_INI_END()
/* }}} */


/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(md_monitor)
{
	initErrorHooks(TSRMLS_C);

	REGISTER_INI_ENTRIES();	
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(md_monitor)
{
	recoveryErrorHooks(TSRMLS_C);

	UNREGISTER_INI_ENTRIES();
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(md_monitor)
{

#if defined(COMPILE_DL_MD_MONITOR) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif

	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(md_monitor)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(md_monitor)
{

	php_info_print_table_start();
	php_info_print_table_header(2, "md_monitor support", "enabled");
	php_info_print_table_row(2, "md_monitor version", PHP_MD_MONITOR_VERSION);
	php_info_print_table_row(2, "md_monitor author", PHP_MD_MONITOR_AUTHOR);
	php_info_print_table_row(2, "md_monitor supports", PHP_MD_MONITOR_WEB);
	php_info_print_table_end();

	DISPLAY_INI_ENTRIES();
}
/* }}} */

/* {{{ md_monitor_functions[]
 *
 * Every user visible function must have an entry in md_monitor_functions[].
 */
const zend_function_entry md_monitor_functions[] = {
	//PHP_FE(confirm_md_monitor_compiled,	NULL)		/* For testing, remove later. */
	PHP_FE_END	/* Must be the last line in md_monitor_functions[] */
};
/* }}} */

/* {{{ md_monitor_module_entry
 */
zend_module_entry md_monitor_module_entry = {
	STANDARD_MODULE_HEADER,
	"md_monitor",
	md_monitor_functions,
	PHP_MINIT(md_monitor),
	PHP_MSHUTDOWN(md_monitor),
	PHP_RINIT(md_monitor),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(md_monitor),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(md_monitor),
	PHP_MD_MONITOR_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_MD_MONITOR
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(md_monitor)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */