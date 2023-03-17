%a=();
for(1...<>){ ($code, $chr)=split" ",<>; $a{$code} = chr$chr };

$bin = <>;
$idx = 0;
$result = "";
while( length($bin) )
{
    $failed = 1;
    for(keys %a)
    {
        $key = $_;
        $bin=~/^$key/;
        next if !length($&);

        $failed = 0;
        $len = length($&);
        $bin = substr$bin,$len;
        $result = $result.$a{$key};
        $idx += $len;
        last;
    }
    

    if ($failed)
    {
        print "DECODE FAIL AT INDEX $idx";
        exit;
    }
}
print $result;
