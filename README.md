# phphashids
php -r 'echo hashid_decode("加密id","salt",最小长度,"字符集");'

php -r 'echo hashid_encode("数字id","salt",最小长度,"字符集");'

php -r 'echo hashid_encode("549195210","123123123",0,"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");'
php -r 'echo hashid_decode("BDMdbDp","123123123",0,"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");'
