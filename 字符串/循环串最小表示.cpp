int pos = 0 ;
for ( int i = 1 , k = 0 ; i < l && k < l ;  ) {
    if ( str[(pos + k) % l] == str[(i + k) % l] ) {
        ++k ;
        continue ;
    }
    else if ( str[(pos + k) % l] > str[(i + k) % l] ) pos += k + 1 ;
    else i += k + 1 ;
    if ( i == pos ) ++i ;
    if ( pos > i ) swap( i , pos ) ;
    k = 0 ;
}
