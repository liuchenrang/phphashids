/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2014 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_phphashids.h"
#include "hashids.h"
/* If you declare any globals in php_phphashids.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(phphashids)
*/

/* True global resources - no need for thread safety here */
static int le_phphashids;

/* {{{ phphashids_functions[]
 *
 * Every user visible function must have an entry in phphashids_functions[].
 */
const zend_function_entry phphashids_functions[] = {
        PHP_FE(confirm_phphashids_compiled, NULL)        /* For testing, remove later. */
        PHP_FE(hashid_encode, NULL)
        PHP_FE(hashid_decode, NULL)
        PHP_FE_END    /* Must be the last line in phphashids_functions[] */
};
/* }}} */

/* {{{ phphashids_module_entry
 */
zend_module_entry phphashids_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
        STANDARD_MODULE_HEADER,
#endif
        "phphashids",
        phphashids_functions,
        PHP_MINIT(phphashids),
        PHP_MSHUTDOWN(phphashids),
        PHP_RINIT(phphashids),        /* Replace with NULL if there's nothing to do at request start */
        PHP_RSHUTDOWN(phphashids),    /* Replace with NULL if there's nothing to do at request end */
        PHP_MINFO(phphashids),
#if ZEND_MODULE_API_NO >= 20010901
        PHP_PHPHASHIDS_VERSION,
#endif
        STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_PHPHASHIDS
ZEND_GET_MODULE(phphashids)
#endif

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("phphashids.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_phphashids_globals, phphashids_globals)
    STD_PHP_INI_ENTRY("phphashids.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_phphashids_globals, phphashids_globals)
PHP_INI_END()
*/
/* }}} */

/* {{{ php_phphashids_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_phphashids_init_globals(zend_phphashids_globals *phphashids_globals)
{
	phphashids_globals->global_value = 0;
	phphashids_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(phphashids)
        {
                /* If you have INI entries, uncomment these lines
                REGISTER_INI_ENTRIES();
                */
                return SUCCESS;
        }
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(phphashids)
        {
                /* uncomment this line if you have INI entries
                UNREGISTER_INI_ENTRIES();
                */
                return SUCCESS;
        }
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(phphashids)
        {
                return SUCCESS;
        }
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(phphashids)
        {
                return SUCCESS;
        }
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(phphashids)
        {
                php_info_print_table_start();
        php_info_print_table_header(2, "phphashids support", "enabled");
        php_info_print_table_end();

                /* Remove comments if you have entries in php.ini
                DISPLAY_INI_ENTRIES();
                */
        }
/* }}} */


/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_phphashids_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_phphashids_compiled){
        char * arg = NULL;
        int arg_len, len;
        char *strg;

        if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
            return;
        }

        len = spprintf(&strg, 0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "phphashids", arg);
        RETURN_STRINGL(strg, len, 0);
        }
PHP_FUNCTION(hashid_encode){
        struct hashids_t *hashids;
//        char *salt = HASHIDS_DEFAULT_SALT, *alphabet = HASHIDS_DEFAULT_ALPHABET;
        char *salt, *alphabet;
        char *buffer, *encode_id;
//		unsigned int min_hash_length = HASHIDS_DEFAULT_MIN_HASH_LENGTH;
        unsigned int min_hash_length;
        unsigned long long auto_id, number, numbers_count, *numbers, encode_id_len, salt_len, alphabet_len;
        /**
         * long salt min
         */
        if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lsls", &auto_id, &salt, &salt_len, &min_hash_length, &alphabet, &alphabet_len) == FAILURE) {
            return;
        }
        hashids = hashids_init3(salt, min_hash_length, alphabet);
        php_printf("File: %s\n", "hashids_init3 ");


        php_printf("File: %d\n", min_hash_length);
        php_printf("File: %lld\n", auto_id);

        numbers = &auto_id;
        buffer = emalloc(hashids_estimate_encoded_size(hashids, 1, numbers));
//		php_printf("File: %s\n","buf" );

        hashids_encode(hashids, buffer, 1, numbers);

        encode_id_len = spprintf(&encode_id, 0, "%s", buffer);

        efree(buffer);

        hashids_free(hashids);

        RETURN_STRINGL(encode_id, encode_id_len, 0);

}
PHP_FUNCTION(hashid_decode){
        struct hashids_t *hashids;
//        char *salt = HASHIDS_DEFAULT_SALT, *alphabet = HASHIDS_DEFAULT_ALPHABET;
        char *salt, *alphabet, *secret;
        char *buffer, *encode_id;
//		unsigned int min_hash_length = HASHIDS_DEFAULT_MIN_HASH_LENGTH;
        unsigned long min_hash_length, result;
        unsigned long long salt_len, alphabet_len, secret_len, *numbers, number;
        /**
         * long salt min
         */
        if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ssls", &secret, &secret_len, &salt, &salt_len, &min_hash_length, &alphabet, &alphabet_len) == FAILURE) {
            return;
        }
        hashids = hashids_init3(salt, min_hash_length, alphabet);
        numbers = emalloc(sizeof(unsigned long long));
        result = hashids_decode(hashids, secret, numbers);
        number = *numbers;
        efree(numbers);
        hashids_free(hashids);
        RETURN_LONG(number);

}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and 
   unfold functions in source code. See the corresponding marks just before 
   function definition, where the functions purpose is also documented. Please 
   follow this convention for the convenience of others editing your code.
*/


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
