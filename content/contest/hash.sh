# Hashes a file, ignoring all whitespace and comments. Use for
# verifying that code was correctly typed.
cpp -dD -P | tr -d '[:space:]'| md5 | cut -c-6
