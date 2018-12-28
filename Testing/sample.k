uint16 : type -
char : type -
file : type -
twelve : const 12

putchar: procedure( c:char, f:file ) -

putstring: procedure( s:array uint16 of char, f:file )
    -- put the string s to file f
    for i in s.min .. s.max
        -- putchar( s(i), output )
    end
end