n, *map, str = $<.map &:chomp
map.map!{a,b=_1.split;[a, b.to_i.chr]}
result = ""
idx = 0

while str.size > 0
    failed = true
    map.each do |code, chr|
        str =~ /^#{code}/
        next if !$&

        str = str[$&.size..]
        result += chr
        failed = false
        idx += $&.size
        break
    end

    if failed
        puts "DECODE FAIL AT INDEX #{idx}"
        exit
    end
end

puts result
